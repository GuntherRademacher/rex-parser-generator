#ifndef MEMORY_HPP_
#define MEMORY_HPP_

#ifdef _MSC_VER
#pragma warning(disable : 4996)
#pragma warning(disable : 6011)
#pragma warning(disable : 26812)
#pragma warning(disable : 28182)
#endif

#include <stdlib.h>

#define REDIRECT 0
#if ! REDIRECT

#include <stddef.h>
#include <string.h>
#include <memory>

template <class T>
class Alloc : public std::allocator<T>
{            typedef std::allocator<T>
               super;
public:
  typedef T                 value_type;
  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef value_type&       reference;
  typedef const value_type& const_reference;
  typedef std::size_t       size_type;
  typedef std::ptrdiff_t    difference_type;

  template <class U> struct rebind { typedef Alloc<U> other; };
  Alloc() {}
  Alloc(const char *f, int l) {}
  Alloc(const Alloc &other) : super(other) {}
  template <class U> Alloc(const Alloc<U> &other) : super(other) {}
};

#else

// see Dr.Dobb's at http://www.ddj.com/cpp/184403759?pgno=1

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <new>

class Malloc
{
public:
  friend class MemoryDescriptor;

  static void *malloc(size_t size, const char *file, int line);
  static void free(void* pointer, const char *file, int line);
  static void *realloc(void* pointer, size_t size, const char *file, int line);
  static void *calloc(size_t nelem, size_t elsize, const char *file, int line);
  static wchar_t *wcsdup(const wchar_t *string, const char *file, int line);
  static char *strdup(const char *string, const char *file, int line);

  static size_t getMallocCountBalance() {return mallocCountBalance;}

private:
  static void exitfunction();
  static bool initializer();

  static size_t mallocCount;
  static size_t mallocSize;
  static size_t mallocCountBalance;
  static size_t mallocSizeBalance;
  static size_t mallocSizeMaxBalance;
  static clock_t mallocElapsedTime;
  static bool mallocInitialized;
};

inline void *Malloc_malloc(size_t size, const char *file, int line) {return Malloc::malloc(size, file, line);}
inline void Malloc_free(void* pointer, const char *file, int line) {Malloc::free(pointer, file, line);}
inline void *Malloc_realloc(void* pointer, size_t size, const char *file, int line) {return Malloc::realloc(pointer, size, file, line);}
inline void *Malloc_calloc(size_t nelem, size_t elsize, const char *file, int line) {return Malloc::calloc(nelem, elsize, file, line);}
inline wchar_t *Malloc_wcsdup(const wchar_t *string, const char *file, int line) {return Malloc::wcsdup(string, file, line);}
inline char *Malloc_strdup(const char *string, const char *file, int line) {return Malloc::strdup(string, file, line);}

template <class T> class Alloc
{
public:
  typedef T                 value_type;
  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef value_type&       reference;
  typedef const value_type& const_reference;
  typedef std::size_t       size_type;
  typedef std::ptrdiff_t    difference_type;

  template <class U>
  struct rebind { typedef Alloc<U> other; };

  Alloc(const char *f, int l) : file(f), line(l) {}
  Alloc(const Alloc &other) : file(other.file), line(other.line) {}
  template <class U>
  Alloc(const Alloc<U> &other) : file(other.file), line(other.line) {}
  ~Alloc() {}

//  pointer address(reference x) const {return &x;}
//  const_pointer address(const_reference x) const {return x;}

  pointer allocate(size_type n, const_pointer = 0)
  {
    void* p = Malloc_malloc(n * sizeof(T), file, line);
    if (p == 0 && n != 0)
    {
      throw std::bad_alloc();
    }
    return static_cast<pointer>(p);
  }

  void deallocate(pointer p, size_type) {Malloc_free(p, file, line);}
  size_type max_size() const {return static_cast<size_type>(-1) / sizeof(T);}
  void construct(pointer p, const value_type& x) {new(p) value_type(x);}
  void destroy(pointer p) {p->~value_type();}

  const char *file;
  int line;

  const Alloc &operator=(const Alloc &rhs)
  {
    file = rhs.file;
    line = rhs.line;
    return *this;
  }
};

template<> class Alloc<void>
{
  typedef void        value_type;
  typedef void*       pointer;
  typedef const void* const_pointer;

  template <class U>
  struct rebind { typedef Alloc<U> other; };
};

template <class T> inline bool operator==(const Alloc<T>&, const Alloc<T>&) {return true;}
template <class T> inline bool operator!=(const Alloc<T>&, const Alloc<T>&) {return false;}

class SourceLocation
{
public:
  SourceLocation(const char *f, int l) : file(f), line(l) {}
  const char *file;
  int line;
};

inline void *operator new(size_t size, SourceLocation sl)
{
  void *pointer = Malloc_malloc(size, sl.file, sl.line);
  if (pointer == 0 && size != 0)
  {
    throw std::bad_alloc();
  }
  return pointer;
}

inline void *operator new(size_t size)
{
  void *pointer = Malloc_malloc(size, __FILE__, __LINE__);
  if (pointer == 0 && size != 0)
  {
    throw std::bad_alloc();
  }
  return pointer;
}

inline void *operator new[](size_t size)
{
  void *pointer = Malloc_malloc(size, __FILE__, __LINE__);
  if (pointer == 0 && size != 0)
  {
    throw std::bad_alloc();
  }
  return pointer;
}

inline void operator delete(void* pointer)
{
  Malloc_free(pointer, __FILE__, __LINE__);
}

inline void operator delete[](void* pointer)
{
  Malloc_free(pointer, __FILE__, __LINE__);
}

inline void *operator new(size_t size, const char *file, int line)
{
  void *pointer = Malloc_malloc(size, file, line);
  if (pointer == 0 && size != 0)
  {
    throw std::bad_alloc();
  }
  else
  {
    return pointer;
  }
}

inline void* operator new[](std::size_t size, const char *file, int line)
{
  void *pointer = Malloc_malloc(size, file, line);
  if (pointer == 0 && size != 0)
  {
    throw std::bad_alloc();
  }
  else
  {
    return pointer;
  }
}

inline void* operator new(std::size_t size, const std::nothrow_t&, const char *file, int line) throw()
{
  void *pointer = Malloc_malloc(size, file, line);
  return pointer;
}

inline void* operator new[](std::size_t size, const std::nothrow_t&, const char *file, int line) throw()
{
  void *pointer = Malloc_malloc(size, file, line);
  return pointer;
}

// Default placement versions of operator new.
inline void* operator new(std::size_t, void* __p, const char *file, int line) throw() { return __p; }
inline void* operator new[](std::size_t, void* __p, const char *file, int line) throw() { return __p; }

#define malloc(size)           Malloc_malloc(size, __FILE__, __LINE__)
#define free(pointer)          Malloc_free(pointer, __FILE__, __LINE__)
#define realloc(pointer, size) Malloc_realloc(pointer, size, __FILE__, __LINE__)
#define calloc(nelem, elsize)  Malloc_calloc(nelem, elsize, __FILE__, __LINE__)
#define wcsdup(string)         Malloc_wcsdup(string, __FILE__, __LINE__)
#define strdup(string)         Malloc_strdup(string, __FILE__, __LINE__)

#ifdef __GNUC__
#define new(...)               new(__VA_ARGS__, __FILE__, __LINE__)
#endif

#endif

inline void* good_alloc(void *pointer, size_t size)
{
  if (pointer || size == 0)
  {
    return pointer;
  }
  else
  {
    throw std::bad_alloc();
  }
}

#define ALLOCATE_ARRAY(TYPE, size) ((TYPE *) good_alloc(malloc((size) * sizeof(TYPE)), size))
#define ALLOCATE(TYPE) ALLOCATE_ARRAY(TYPE, 1)
#define REALLOCATE_ARRAY(TYPE, pointer, size) ((TYPE *) good_alloc(realloc(pointer, (size) * sizeof(TYPE)), size))

#endif
