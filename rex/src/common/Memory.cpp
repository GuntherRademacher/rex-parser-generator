#include "Memory.hpp"
#include "Platforms.hpp"

#if REDIRECT

#undef malloc
#undef free
#undef realloc
#undef calloc
#undef wcsdup
#undef strdup

#include <limits.h>
#include <map>

size_t Malloc::mallocCount = 0;
size_t Malloc::mallocSize = 0;
size_t Malloc::mallocCountBalance = 0;
size_t Malloc::mallocSizeBalance = 0;
size_t Malloc::mallocSizeMaxBalance = 0;
clock_t Malloc::mallocElapsedTime;
bool Malloc::mallocInitialized = Malloc::initializer();

class MemoryAllocationEvent
{
public:
  bool operator<(const MemoryAllocationEvent &rhs) const
  {
    int c = strcmp(file, rhs.file);
    if (c != 0) return c < 0;
    if (line < rhs.line) return true;
    if (line > rhs.line) return false;
    return size < rhs.size;
  }

  size_t size;
  const char *file;
  int line;
};

static size_t breakpoint = 0;

class MemoryDescriptor : public MemoryAllocationEvent
{
public:
  void *link(size_t s, const char *f, int l)
  {
    size = s;
    negativeSize = - (int) s;

    if (heap.forward == 0)
    {
      heap.size = 0;
      heap.file = 0;
      heap.line = 0;
      heap.negativeSize = -1;
      heap.forward = &heap;
      heap.reverse = &heap;
      heap.seqNo = 0;
    }

    forward = heap.forward;
    reverse = &heap;
    reverse->forward = this;
    forward->reverse = this;
    seqNo = Malloc::mallocCount;
    file = f;
    line = l;

    if (seqNo == breakpoint)
    {
      seqNo = Malloc::mallocCount;
      if (seqNo != 0)
      {
        *(int *) 0 = -1;
      }
    }

    ++Malloc::mallocCount;
    ++Malloc::mallocCountBalance;
    Malloc::mallocSize += s;
    Malloc::mallocSizeBalance += s;
    if (Malloc::mallocSizeMaxBalance < Malloc::mallocSizeBalance)
    {
      Malloc::mallocSizeMaxBalance = Malloc::mallocSizeBalance;
    }

    return this + 1;
  }

  void unlink(const char *file, int line)
  {
    if (size == 0 || (int) size != - negativeSize)
    {
      fprintf(stderr, "invalid block, size %zd, stamp %d, caller %s:%d\n", size, negativeSize, file, line);
      fflush(stderr);
      exit(1);
    }

    --Malloc::mallocCountBalance;
    Malloc::mallocSizeBalance -= size;
    forward->reverse = reverse;
    reverse->forward = forward;

    const int iPattern = 0xa55a5aa5;
    const size_t sPattern = 0xa55a5aa5;
    const void *pPattern = (const char *) 0 + sPattern;

    size = sPattern;
    file = (const char *) pPattern;
    line = iPattern;
    negativeSize = iPattern;
    forward = (MemoryDescriptor *) pPattern;
    reverse = (MemoryDescriptor *) pPattern;
    seqNo = sPattern;
  }

  int negativeSize;
  MemoryDescriptor *forward;
  MemoryDescriptor *reverse;
  size_t seqNo;

  static MemoryDescriptor heap;
};

MemoryDescriptor MemoryDescriptor::heap;

class MemoryCount
{
public:
  MemoryCount() : count(0), firstSeqNo(0), lastSeqNo(0) {}
  MemoryCount(size_t c, size_t f, size_t l) : count(c), firstSeqNo(f), lastSeqNo(l) {}

  size_t count;
  size_t firstSeqNo;
  size_t lastSeqNo;
};

typedef std::map<MemoryAllocationEvent, MemoryCount> CountByMemoryAllocationEvent;

static bool flagM = false;
static bool flagF = false;

bool Malloc::initializer()
{
  if (atexit(exitfunction))
  {
    fprintf(stderr, "atexit failed\n");
    fflush(stderr);
    exit(1);
  }

  const char *brk = getenv("BREAKPOINT");
  if (brk)
  {
    breakpoint = atoi(brk);
  }

  const char *flags = getenv("FLAGS");
  if (flags)
  {
    flagM = flags && strchr(flags, 'M');
    flagF = flags && strchr(flags, 'F');
  }

  mallocElapsedTime = clock();

  return true;
}

void Malloc::exitfunction()
{
  mallocElapsedTime = clock() - mallocElapsedTime;

  if (   flagM
      || mallocCountBalance != 0
      || mallocSizeBalance != 0)
  {
    fprintf(stderr, "mallocElapsedTime: %.0f msec\n", ((double) mallocElapsedTime / CLOCKS_PER_SEC) * 1000);
    fwprintf(stderr, L"mallocMax: %zd (%zd MB)\n", mallocSizeMaxBalance, ((mallocSizeMaxBalance + 512) / 1024 + 512) / 1024);
    fwprintf(stderr, L"mallocSize: %zd (%zd MB)\n", mallocSize, ((mallocSize + 512) / 1024 + 512) / 1024);
    fprintf(stderr, "mallocCount: %zd\n", mallocCount);
  }

  if (   mallocCountBalance != 0
      || mallocSizeBalance != 0)
  {
    size_t currentSeqNo = Malloc::mallocCount;

    fprintf(stderr, "mallocCountBalance: %zd\n", mallocCountBalance);
    fprintf(stderr, "mallocSizeBalance: %zd\n", mallocSizeBalance);

    CountByMemoryAllocationEvent cbm;

    for (MemoryDescriptor *m = MemoryDescriptor::heap.forward;
        m != &MemoryDescriptor::heap;
        m = m->forward)
    {
      if (m->seqNo < currentSeqNo)
      {
        CountByMemoryAllocationEvent::iterator i = cbm.find(*(MemoryAllocationEvent *) m);
        if (i != cbm.end())
        {
          i->second.count++;
          if (i->second.firstSeqNo > m->seqNo) i->second.firstSeqNo = m->seqNo;
          if (i->second.lastSeqNo  < m->seqNo) i->second.lastSeqNo  = m->seqNo;
        }
        else
        {
          cbm.insert(CountByMemoryAllocationEvent::value_type(*(MemoryAllocationEvent *) m, MemoryCount(1, m->seqNo, m->seqNo)));
        }
      }
    }

    size_t totalCount = 0;
    size_t totalSize = 0;
    size_t firstSeqNo = UINT_MAX;
    size_t lastSeqNo  = 0;
    fprintf(stderr, "\n");
    fprintf(stderr, "       Total   Count    Size   First#    Last#  Line File\n");
    fprintf(stderr, "    -------- ------- ------- -------- -------- ----- ----\n");
    int commonPrefix = -1;
    const char *file = 0;
    for (CountByMemoryAllocationEvent::iterator i = cbm.begin(); i != cbm.end(); ++i)
    {
      const MemoryAllocationEvent &m = i->first;
      MemoryCount &mc = i->second;
      size_t eventCount = mc.count;
      size_t eventSize = eventCount * m.size;
      fprintf(stderr, "    %8zd %7zd %7zd %8zd %8zd %5d %s\n", eventSize, eventCount, m.size, mc.firstSeqNo, mc.lastSeqNo, m.line, m.file);
      if (commonPrefix < 0)
      {
        file = m.file;
        commonPrefix = (int) strlen(file);
      }
      else
      {
        for (int j = 1; j < commonPrefix; ++j)
        {
          if (strncasecmp(file, m.file, j))
          {
            commonPrefix = j - 1;
            break;
          }
        }
      }
      totalCount += eventCount;
      totalSize += eventSize;
      if (mc.firstSeqNo < firstSeqNo) firstSeqNo = mc.firstSeqNo;
      if (mc.lastSeqNo  > lastSeqNo ) lastSeqNo  = mc.lastSeqNo;
    }
    fprintf(stderr, "    -------- -------         -------- --------");
    if (commonPrefix > 0)
    {
      fprintf(stderr, "       ");
      for (int j = 0; j < commonPrefix; ++j)
      {
        fprintf(stderr, "-");
      }
    }
    else if (commonPrefix < 0)

    {
      commonPrefix = 0;
    }
    fprintf(stderr, "\n");
    fprintf(stderr, "    %8zd %7zd         %8zd %8zd       %.*s\n\n", totalSize, totalCount, firstSeqNo, lastSeqNo, commonPrefix, file);

    cbm.clear();
  }

  fflush(stderr);
}

void *Malloc::malloc
(size_t size, const char *file, int line)
{
  if (size == 0)
  {
    return 0;
  }
  else
  {
    MemoryDescriptor *p1 = (MemoryDescriptor *) ::malloc(sizeof(MemoryDescriptor) + size);
    return p1 ? p1->link(size, file, line) : 0;
  }
}

void Malloc::free(void* pointer, const char *file, int line)
{
  if (pointer)
  {
    MemoryDescriptor *p0 = (MemoryDescriptor *) pointer - 1;
    p0->unlink(file, line);
    if (! flagF)
    {
      ::free(p0);
    }
  }
}

void *Malloc::realloc(void* pointer, size_t size, const char *file, int line)
{
  if (size == 0)
  {
    free(pointer, file, line);
    return 0;
  }
  else if (pointer == 0)
  {
    return malloc(size, file, line);
  }
  else
  {
    MemoryDescriptor *p0 = (MemoryDescriptor *) pointer - 1;
    p0->unlink(file, line);
    MemoryDescriptor *p1 = (MemoryDescriptor *) ::realloc(p0, sizeof(MemoryDescriptor) + size);
    return p1 ? p1->link(size, file, line) : 0;
  }
}

void *Malloc::calloc(size_t nelem, size_t elsize, const char *file, int line)
{
  void *pointer = malloc(nelem * elsize, file, line);
  if (pointer) memset(pointer, 0, nelem * elsize);
  return pointer;
}

wchar_t *Malloc::wcsdup(const wchar_t *string, const char *file, int line)
{
  wchar_t *copy = static_cast <wchar_t *> (malloc((1 + wcslen(string)) * sizeof(wchar_t), file, line));
  if (copy) wcscpy(copy, string);
  return copy;
}

char *Malloc::strdup(const char *string, const char *file, int line)
{
  char *copy = static_cast <char *> (malloc((1 + strlen(string)) * sizeof(char), file, line));
  if (copy) strcpy(copy, string);
  return copy;
}

#endif
