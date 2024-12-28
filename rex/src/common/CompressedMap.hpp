/*
 *
 *  Created on: 05.05.2009
 *      Author: Gunther
 */

#ifndef COMPRESSEDMAP_HPP
#define COMPRESSEDMAP_HPP

#include "Error.hpp"
#include "Math.hpp"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <set>
#include <map>
#include <vector>

class TiledMap
{
public:
  // legacy: header must contain shift only

  TiledMap(const int *map, size_t size, size_t maxDepth, bool legacy)
  : uncompressedMap(map),
    uncompressedMapSize(size),
    compressedMap(0),
    compressedMapSize(size),
    maxDepth(maxDepth),
    depth(0),
    hiOffset(0),
    nesting(0),
    legacy(legacy),
    overlap(0),
    tileSize(0)
  {
    init();
  }

  ~TiledMap()
  {
    free(bits);
    free(compressedMap);
  }

  size_t size() const {return depth ? compressedMapSize : uncompressedMapSize;}
  size_t uncompressedSize() const {return uncompressedMapSize;}
  size_t getDepth() const {return depth;}
  size_t getOverlap() const {return overlap;}
  size_t getTileSize() const {return tileSize;}
  const int *getBits() const {return bits;}

  int nestedLookup(size_t i) const {return lookup(i, depth);}

  //  const int &operator[](size_t i) const
  //  {
  //    if (depth)
  //      return compressedMap[i];
  //    else
  //      return uncompressedMap[i];
  //  }

  const int *getRepresentation() const
  {
    if (depth)
      return compressedMap;
    else
      return uncompressedMap;
  }

private:
  TiledMap(const int *map, size_t size, size_t maxDepth, size_t n, bool legacy)
  : uncompressedMap(map),
    uncompressedMapSize(size),
    compressedMap(0),
    compressedMapSize(size),
    maxDepth(maxDepth),
    depth(0),
    hiOffset(legacy ? n : 0),
    nesting(n),
    legacy(legacy),
    overlap(0),
    tileSize(0)
  {
    init();
  }

  friend class TiledMap2D;

  typedef int TileId;

  class Tile
  {
  public:
    Tile(const int *d, size_t s)
    : data(d),
      size(s),
      id(-1),
      rightId(-1),
      leftMatch(0),
      location(0)
    {}

    bool operator<(const Tile &rhs) const
    {
      const int *l = data;
      const int *r = rhs.data;
      if (size < rhs.size)
      {
        for (const int *end = l + size; l < end; ++l, ++r)
        {
          if (*l != *r) return *l < *r;
        }
        return true;
      }
      else
      {
        for (const int *end = l + rhs.size; l < end; ++l, ++r)
        {
          if (*l != *r) return *l < *r;
        }
        return false;
      }
    }

    const int *data;
    size_t size;
    TileId id;
    TileId rightId;
    size_t leftMatch;
    size_t location;
  };

  class TileSet : public std::set<Tile, std::less<Tile>, Alloc<Tile> >
  {              typedef std::set<Tile, std::less<Tile>, Alloc<Tile> >
                 super;
  public:
    TileSet()
    : super(std::less<Tile>(), Alloc<Tile>(__FILE__, __LINE__))
    {}
  };

  void optimize(int shift);
  int lookup(size_t index, size_t level) const;
  void verify();
  void verify2();
  void init();

  class TileVector : public std::vector<Tile, Alloc<Tile> >
  {                 typedef std::vector<Tile, Alloc<Tile> >
                    super;
  public:
    TileVector()
    : super(Alloc<Tile>(__FILE__, __LINE__))
    {}
  };

  TileVector distinctTiles;

  TileSet tiles;

  const int *uncompressedMap;
  size_t uncompressedMapSize;

  int *compressedMap;
  size_t compressedMapSize;

  int *bits;

  size_t maxDepth;
  size_t depth;

  size_t hiOffset;
  size_t nesting;

  bool legacy;

  size_t overlap;

  size_t tileSize;
};

class Addrezz
{
public:
  Addrezz(int i, int j) : x(i), y(j) {}

  bool operator<(const Addrezz &rhs) const
  {
    return y == rhs.y ? x < rhs.x : y < rhs.y;
  }

  int x;
  int y;
};

class ValueMap : public std::map<Addrezz, int, std::less<Addrezz>, Alloc<std::pair<const Addrezz, int> > >
{               typedef std::map<Addrezz, int, std::less<Addrezz>, Alloc<std::pair<const Addrezz, int> > >
                super;
public:
  ValueMap()
  : super(std::less<Addrezz>(), Alloc<std::pair<const Addrezz, int> >(__FILE__, __LINE__))
  {}

  ~ValueMap()
  {
    clear();
  }
};

class TiledMap2D
{
public:
  TiledMap2D(int d = 0, int t = 16, bool f = false)
  : valueCount(0),
    depth(d), flip(f),
    minX(-1), maxX(-1), shiftX(false),
    minY(-1), maxY(-1), shiftY(false),
    map(0),
    uncompressedMapSize(0),
    uncompressedMap(0),
    rows(0),
    cols(0),
    tile(t)
  {}

  ~TiledMap2D()
  {
    delete map;
    free(uncompressedMap);
  }

  int getMaxX() const {return cols;}
  int getMaxY() const {return rows;}

  void setMaxIndex(int x, int y)
  {
    if (minX < 0)
    {
      minX = x;
      maxX = x;
      minY = y;
      maxY = y;
    }
    else
    {
      if (minX > x) minX = x;
      if (maxX < x) maxX = x;
      if (minY > y) minY = y;
      if (maxY < y) maxY = y;
    }
  }

  int get(int x, int y)
  {
    ValueMap::const_iterator i(values.find(Addrezz(x, y)));
    return i == values.end() ? 0 : i->second;
  }

  void set(int x, int y, int newValue)
  {
    if (newValue == 0)
    {
      internalerr();
    }
    else
    {
      int oldValue = get(x, y);
      if (oldValue == 0)
      {
        setMaxIndex(x, y);
        values.insert(ValueMap::value_type(Addrezz(x, y), newValue));
      }
      else if (oldValue != newValue)
      {
        fprintf(stderr, "setting (%d, %d) to %d conflicts with value already set to %d\n", x, y, newValue, oldValue);
        fflush(stderr);
        internalerr();
      }
    }
  }

  const TiledMap *getMap()
  {
    if (map == 0)
    {
      optimize();
    }
    return map;
  }

  TiledMap *takeMap()
  {
    if (map == 0)
    {
      optimize();
    }
    TiledMap *m = map;
    map = 0;
    return m;
  }

private:
  static int align(int v, int alignment)
  {
    if (alignment == 0)
    {
      return Math::powerof(2, Math::log2(v - 1) + 1);
    }
    else
    {
      return (v + alignment - 1) / alignment * alignment;
    }
  }

#if 0
  int get(int x, int y) const
  {
    Addrezz a(x, y);
    ValueMap::const_iterator i(values.find(a));
    return i == values.end()
         ? 0
         : i->second;
  }
#endif

  void fill(int alignment, bool flipped);
  void optimize();

  ValueMap values;
  int valueCount;
  int depth;
  bool flip;

  int minX;
  int maxX;
  bool shiftX;

  int minY;
  int maxY;
  bool shiftY;

  TiledMap *map;
  int uncompressedMapSize;
  int *uncompressedMap;
  int rows;
  int cols;
  int tile;
};

class EntryListMap2D
{
public:
  EntryListMap2D()
  : minX(-1), maxX(-1),
    minY(-1), maxY(-1),
    map(0),
    mapSize(0)
  {}

  ~EntryListMap2D()
  {
    free(map);
  }

  int getMaxX() const {return maxX;}
  int getMaxY() const {return maxY;}
  size_t size() const {return mapSize;}

  void setMaxIndex(int x, int y)
  {
    if (minX < 0)
    {
      minX = x;
      maxX = x;
      minY = y;
      maxY = y;
    }
    else
    {
      if (minX > x) minX = x;
      if (maxX < x) maxX = x;
      if (minY > y) minY = y;
      if (maxY < y) maxY = y;
    }
  }

  void set(int x, int y, int value)
  {
    Addrezz a(x, y);
    if (value == 0)
    {
      internalerr();
    }
    else
    {
      ValueMap::const_iterator i(values.find(a));
      if (i == values.end())
      {
        setMaxIndex(x, y);
        values.insert(ValueMap::value_type(a, value));
      }
      else if (i->second != value)
      {
        internalerr();
      }
    }
  }

  int get(int x, int y) const
  {
    for (int i = map[y];; i += 2)
    {
      if (map[i] == x) return map[i + 1];
      if (map[i] < x) break;
    }
    return 0;
  }

  const int *getMap();
  const int *getRepresentation() const {return map;}

private:
  ValueMap values;

  int minX;
  int maxX;

  int minY;
  int maxY;

  int *map;
  size_t mapSize;
};

#endif
