/*
 * CompressedMap.cpp
 *
 *  Created on: 25.12.2009
 *      Author: Gunther
 */

#include "Memory.hpp"
#include "CompressedMap.hpp"

void TiledMap::optimize(int shift)
{
  tileSize = 1;
  tileSize <<= shift;
  bits[0] = shift;

  int *hiMap = compressedMap;
  if (legacy)
  {
    *hiMap++ = shift;
  }

  tiles.clear();
  distinctTiles.clear();

  size_t hiSize = 0;
  for (size_t mapIndex = 0; mapIndex < uncompressedMapSize; mapIndex += tileSize)
  {
    const int *data = uncompressedMap + mapIndex;
    size_t maxSize = uncompressedMapSize - mapIndex;

    if (maxSize < tileSize)
    {
      Tile tile(data, maxSize);
      TileSet::iterator i(tiles.lower_bound(tile));
      if (i == tiles.end() || memcmp(i->data, data, maxSize * sizeof *data) != 0)
      {
        tile.id = (TileId) distinctTiles.size();
        distinctTiles.push_back(tile);
        i = tiles.insert(tile).first;
      }
      hiMap[hiSize++] = i->id;
    }
    else
    {
      Tile tile(data, tileSize);
      std::pair<TileSet::iterator, bool> inserted(tiles.insert(tile));
      if (inserted.second)
      {
        tile.id = (TileId) distinctTiles.size();
        const_cast <Tile &>(*inserted.first).id = tile.id;
        distinctTiles.push_back(tile);
      }
      hiMap[hiSize++] = inserted.first->id;
    }
  }

  overlap = 0;

#if 1 // OVERLAP
  for (size_t matchSize = tileSize - 1; matchSize > 0; --matchSize)
  {
    for (TileVector::iterator h = distinctTiles.begin(); h != distinctTiles.end(); ++h)
    {
      TileId head = h->id;
      if (h->size >= matchSize && h->leftMatch == 0 && h->rightId < 0)
      {
        for (Tile *l = const_cast<Tile *> (&*h); l; )
        {
          Tile &lt(*l);
          l = 0;

          Tile matchTile(lt.data + lt.size - matchSize, matchSize);

          for (TileSet::iterator r(tiles.lower_bound(matchTile));
               r != tiles.end();
               ++r)
          {
            Tile &rt(const_cast<Tile &> (*r));
            if (   matchSize > rt.size
                || memcmp(matchTile.data, rt.data, matchSize * sizeof *rt.data) != 0)
            {
              break;
            }

            TileId rId = rt.id;
            if (rId != head)
            {
#if 0
              printf("match %d to %d\n", lt.id, rId);
#endif
              tiles.erase(r);

              lt.rightId = rId;

              l = &distinctTiles[rId];
              l->leftMatch = matchSize;

              overlap += matchSize;

              if (l->rightId >= 0)
              {
                l = 0;
              }
              break;
            }
          }
        }
      }
    }
  }
#endif
  //

  int *loMap = hiMap + hiSize;
  size_t loSize = 0;
  size_t loCount = 0;

#if 0
  printf("\ntiles: \n");
#endif

  for (TileVector::iterator i = distinctTiles.begin(); i != distinctTiles.end(); ++i)
  {
    Tile *tile(&*i);
    if (tile->leftMatch == 0)
    {
      while (tile)
      {
#if 0
        printf("id %5.5d, leftMatch %d, rightId %d, loSize %d\n", tile->id, tile->leftMatch, tile->rightId, loSize);
#endif

        const int *data(tile->data + tile->leftMatch);
        size_t size = tile->size - tile->leftMatch;
        tile->location = loSize - tile->leftMatch;
        memcpy(loMap + loSize, data, size * sizeof *data);
        loSize += size;
        ++loCount;
        if (tile->rightId < 0)
        {
          tile = 0;
        }
        else
        {
          tile = &distinctTiles[tile->rightId];
        }
      }
    }
  }

  if (loCount != distinctTiles.size())
  {
    printf("\ntile count mismatch: \n");
    for (TileVector::iterator i = distinctTiles.begin(); i != distinctTiles.end(); ++i)
    {
      Tile *tile(&*i);
      printf("id %5.5d, leftMatch %d, rightId %d, loSize %d\n", tile->id, (int) tile->leftMatch, tile->rightId, (int) loSize);
    }

    internalerr();
  }

  //

  for (size_t i = 0; i < hiSize; ++i)
  {
    hiMap[i] = (int) (distinctTiles[hiMap[i]].location + hiSize + (legacy ? nesting + 1 : 0));
  }

  //

  if (nesting + 1 >= maxDepth)
  {
    depth = 1;
  }
  else
  {
    TiledMap compressedHiMap(hiMap, hiSize, maxDepth, nesting + 1, legacy);
    if (compressedHiMap.size() < hiSize)
    {
      hiSize = compressedHiMap.size();
      memcpy(hiMap, compressedHiMap.getRepresentation(), hiSize * sizeof *hiMap);

#if 0
      printf("loMap(%d): ", loSize);
      for (size_t i = 0; i < loSize; ++i)
      {
        if (i != 0) printf(",");
        printf("%d", loMap[i]);
      }
      printf("\n");
#endif

      memmove(hiMap + hiSize, loMap, loSize * sizeof *hiMap);
      loMap = hiMap + hiSize;

#if 0
      printf("hiMap(%d): ", hiSize + loSize);
      for (size_t i = 0; i < hiSize + loSize; ++i)
      {
        if (i != 0) printf(",");
        printf("%d", hiMap[i]);
      }
      printf("\n");
#endif

      depth = compressedHiMap.getDepth();
      memcpy(bits + 1, compressedHiMap.getBits(), depth * sizeof *bits);
      ++depth;
      overlap += compressedHiMap.getOverlap();
    }
    else
    {
      depth = 1;
    }
  }

  compressedMapSize = loMap - compressedMap + loSize;

  //

  if (nesting)
  {
    int relocation = (int) compressedMapSize - (int) uncompressedMapSize;
    for (size_t i = 0; i < loSize; ++i)
    {
      loMap[i] += relocation;
    }
  }

#if 0
  if (nesting == 0 && depth == 2)
    verify2();
  else
    verify();
#endif

#if 0
  if (nesting == 0)
    getCode(stdout, 0, "i", "c", "map");
#endif
}

int TiledMap::lookup(size_t index, size_t level) const
{
  if (depth == 0)
  {
    return uncompressedMap[index];
  }
  else
  {
    size_t s = depth - level;
    size_t hiBase = legacy ? s + 1 : 0;
    int shift = bits[s];
    size_t hi = index >> shift;
    size_t lo = index - (hi << shift);
    int result = (  level > 1
                  ? compressedMap[lookup(hi, level - 1) + lo]
                  : compressedMap[compressedMap[hiBase + hi] - hiOffset + lo]
                 )
               - (int) (nesting && depth == level ? compressedMapSize - uncompressedMapSize : hiOffset);

  #if 0
    printf("lookup: s %d, shift %d, hiOffset %d, depth %d, level %d", s, shift, hiOffset, depth, level);
    printf(", index %d, hi %d, lo %d, result %d\n", index, hi, lo, annotation);
  #endif

    return result;
  }
}

void TiledMap::verify()
{
#if 0
  printf("\nverify: depth %d, hiOffset %d, nesting %d, compressedMapSize %d, uncompressedMapSize %d\n",
         depth, hiOffset, nesting, compressedMapSize, uncompressedMapSize);

  printf("uncompressed(%d): ", uncompressedMapSize);
  for (size_t i = 0; i < uncompressedMapSize; ++i)
  {
    if (i != 0) printf(",");
    printf("%d", uncompressedMap[i]);
  }
  printf("\n");

  printf("compressed(%d): ", compressedMapSize);
  for (size_t i = 0; i < compressedMapSize; ++i)
  {
    if (i != 0) printf(",");
    printf("%d", compressedMap[i]);
  }
  printf("\n");
#endif

  int errs = 0;

  for (size_t i = 0; i < uncompressedMapSize; ++i)
  {
    int u = uncompressedMap[i];
    int c = lookup(i, depth);
    if (u != c)
    {
      printf("verification error: uncompressedMap[%d] %d, lookup(%d, %d) %d\n", (int) i, u, (int) i, (int) depth, c);
      if (++errs > 9)
      {
        internalerr();
      }
    }
  }

  if (errs)
  {
    internalerr();
  }

  if (nesting == 0)
  {
    printf("verified %d\n", (int) uncompressedMapSize);
  }
}

void TiledMap::verify2()
{
#if 0
  printf("\ndepth %d, hiOffset %d\n", depth, hiOffset);

  printf("uncompressed(%d): ", uncompressedMapSize);
  for (size_t i = 0; i < uncompressedMapSize; ++i)
  {
    if (i != 0) printf(",");
    printf("%d", uncompressedMap[i]);
  }
  printf("\n");

  printf("compressed(%d): ", compressedMapSize);
  for (size_t i = 0; i < compressedMapSize; ++i)
  {
    if (i != 0) printf(",");
    printf("%d", compressedMap[i]);
  }
  printf("\n");
#endif

  int errs = 0;

  int s0 = bits[0];
  int s1 = bits[1];
  int a0 = (1 << s0) - 1;
  int a1 = (1 << s1) - 1;

  const int *innerMap = compressedMap + (legacy ? 3 : 0);

  for (size_t i0 = 0; i0 < uncompressedMapSize && errs < 10; ++i0)
  {
    int u = uncompressedMap[i0];

    size_t i1 = i0 >> s0;
    size_t i2 = i1 >> s1;
    int c = compressedMap[compressedMap[innerMap[i2] + (i1 & a1)] + (i0 & a0)];

    if (u != c)
    {
      printf("verification2 error: uncompressedMap[%d] %d, c %d, h0 %d\n", (int) i0, u, c, (int) i1);
      ++errs;
    }
  }

  if (errs)
  {
    internalerr();
  }

  printf("verified2 %d\n", (int) uncompressedMapSize);
}

void TiledMap::init()
{
  bits = ALLOCATE_ARRAY(int, maxDepth + 1);
  memset(bits, 0, (maxDepth + 1) * sizeof *bits);

  if (maxDepth)
  {
    compressedMap = ALLOCATE_ARRAY(int, compressedMapSize + ((compressedMapSize + 1) >> 1) + 1);

    int optShift = 1;
    optimize(optShift);
    size_t optSize = compressedMapSize;

    int inc = 0;
    for (int shift = 2; (uncompressedMapSize >> shift) > 1; ++shift)
    {
      optimize(shift);
      if (optSize >= compressedMapSize)
      {
        inc = 0;
        optShift = shift;
        optSize = compressedMapSize;
      }
      else if (++inc == 1)
      {
        break;
      }
    }

    if (optSize < uncompressedMapSize)
    {
      optimize(optShift);
    }
    else
    {
      depth = 0;
      overlap = 0;
    }
  }
  bits[depth] = 0;
}

// CompressedMap2D

void TiledMap2D::fill(int alignment, bool flipped)
{
  if (map)
  {
    delete map;
    map = 0;
  }

  if (uncompressedMap)
  {
    free(uncompressedMap);
    uncompressedMap = 0;
    uncompressedMapSize = 0;
  }

  cols = maxX + 1;
  rows = maxY + 1;

  if (shiftX)
  {
    cols -= minX;
  }

  if (shiftY)
  {
    rows -= minY;
  }

  if (flipped)
    rows = align(rows, alignment);
  else
    cols = align(cols, alignment);

  uncompressedMapSize = cols * rows;
  uncompressedMap = ALLOCATE_ARRAY(int, uncompressedMapSize);
  memset(uncompressedMap, 0, uncompressedMapSize * sizeof(int));

  for (ValueMap::iterator i = values.begin(); i != values.end(); ++i)
  {
    const Addrezz &a(i->first);
    int v = i->second;

    int x = a.x;
    int y = a.y;

    if (shiftX)
    {
      x -= minX;
    }

    if (shiftY)
    {
      y -= minY;
    }

    if (! flipped)
      uncompressedMap[x + cols * y] = v;
    else
      uncompressedMap[x * rows + y] = v;
  }
}

void TiledMap2D::optimize()
{
  valueCount = (int) values.size();

  if (depth <= 0)
  {
#if 0
    for (ValueMap::iterator i = values.begin(); i != values.end(); ++i)
    {
      const Addrezz &a(i->first);
      int v = i->second;
      int x = a.x;
      int y = a.y;
      printf("x %d y %d v %d\n", x, y, v);
    }
#endif

    printf("minX: %d, maxX: %d, minY: %d, maxY: %d\n", minX, maxX, minY, maxY);

    int alignment[] = {64, 32, 16, 8, 4, 2, 1, 0};

    for (int f = 1; f >= 0; --f)
      for (int d = 3; d >= 1; --d)
    {
      for (size_t a = 0; a < sizeof alignment / sizeof alignment[0]; ++a)
      {
        fill(alignment[a], f != 0);

        map = new TiledMap(uncompressedMap, uncompressedMapSize, d, false);
        printf("align %2d, flip %s, compress %d, values %d, %5d x %5d = %6d, compressedMapSize %d, depth %d, overlap %d, tileSize %d, compressed to %.1f %%\n",
            alignment[a],
            f != 0 ? " true" : "false",
            d, valueCount, cols, rows, uncompressedMapSize, (int) map->size(), (int) map->getDepth(), (int) map->getOverlap(), (int) map->getTileSize(),
            map->size() * 100e0 / ((maxX + 1) * (maxY + 1)));
      }
      printf("\n");
    }
  }

  if (depth)
  {
    fill(tile, flip);
    values.clear();
    map = new TiledMap(uncompressedMap, uncompressedMapSize, abs(depth), false);

    if (depth < 0)
    {
      printf("using:\n");
      printf("align %2d, flip %s, compress %d, values %d, %5d x %5d = %6d, compressedMapSize %d, depth %d, overlap %d, tileSize %d, compressed to %.1f %%\n",
          tile,
          flip ? " true" : "false",
          abs(depth), valueCount, cols, rows, uncompressedMapSize, (int) map->size(), (int) map->getDepth(), (int) map->getOverlap(), (int) map->getTileSize(),
          map->size() * 100e0 / ((maxX + 1) * (maxY + 1)));
    }
  }

//  free(uncompressedMap);  // don't! - because still required when depth == 0
}

class TreeStructuredReversedListNode;

class TreeStructuredReversedListNodeByCode : public std::map<const int, TreeStructuredReversedListNode *, std::less<int>, Alloc<std::pair<const int, TreeStructuredReversedListNode *> > >
{                                           typedef std::map<const int, TreeStructuredReversedListNode *, std::less<int>, Alloc<std::pair<const int, TreeStructuredReversedListNode *> > >
                                                    super;
public:
  TreeStructuredReversedListNodeByCode()
  : super(std::less<int>(), Alloc<std::pair<const int, TreeStructuredReversedListNode *> >(__FILE__, __LINE__))
  {}

  ~TreeStructuredReversedListNodeByCode();
};

class TreeStructuredReversedListNode
{
public:
  TreeStructuredReversedListNode(TreeStructuredReversedListNode *parent, int value)
  : parent(parent), value(value), index(0)
  {}

  TreeStructuredReversedListNode *child(int v)
  {
    TreeStructuredReversedListNode *&child = children[v];
    if (child == 0)
    {
      child = new TreeStructuredReversedListNode(this, v);
    }
    return child;
  }

  void dump(std::vector<int> &vector)
  {
    if (children.empty())
    {
      for (TreeStructuredReversedListNode *node = this; node; node = node->parent)
      {
        if (node->index == 0)
          node->index = (int) vector.size();
        vector.push_back(node->value);
      }
    }
    else
    {
      for (TreeStructuredReversedListNodeByCode::iterator i = children.begin(); i != children.end(); ++i)
      {
        TreeStructuredReversedListNode *child = i->second;
        child->dump(vector);
      }
    }
  }

//private:
  TreeStructuredReversedListNodeByCode children;
  TreeStructuredReversedListNode *parent;
  int value;
  int index;
};

TreeStructuredReversedListNodeByCode::~TreeStructuredReversedListNodeByCode()
{
  for (iterator i = begin(); i != end(); ++i)
  {
    delete i->second;
  }
}

const int *EntryListMap2D::getMap()
{
  int lastY = -1;
  TreeStructuredReversedListNode **yEntries = ALLOCATE_ARRAY(TreeStructuredReversedListNode *, maxY + 1);
  memset(yEntries, 0, (maxY + 1) * sizeof(TreeStructuredReversedListNode *));
  TreeStructuredReversedListNode *root = new TreeStructuredReversedListNode(0, 0);
  TreeStructuredReversedListNode *current = root;
  for (ValueMap::const_iterator i = values.begin(); i != values.end(); ++i)
  {
    const std::pair<const Addrezz, int> value = *i;
    int x = value.first.x;
    int y = value.first.y;
    int v = value.second;

//    fprintf(stderr, "processing %d %d %d\n", x, y, v);

    if (y != lastY)
    {
      if (lastY >= 0)
      {
        yEntries[lastY] = current;
        current = root;
      }
      lastY = y;
    }
    current = current->child(v)->child(x);
  }
  if (lastY >= 0)
  {
    yEntries[lastY] = current;
    current = root;
  }

  std::vector<int> v;
  for (int y = 0; y <= maxY; ++y)
    v.push_back(0);
  root->dump(v);

  for (int y = 0; y <= maxY; ++y)
  {
    TreeStructuredReversedListNode *yEntry = yEntries[y];
    if (yEntry == 0)
      v[y] = root->index;
    else
      v[y] = yEntries[y]->index;
  }
  free(yEntries);
  delete root;

  mapSize = v.size();
  map = ALLOCATE_ARRAY(int, mapSize);
  for (size_t i = 0; i < mapSize; ++i)
  {
    map[i] = v[i];
  }
  return map;
}

