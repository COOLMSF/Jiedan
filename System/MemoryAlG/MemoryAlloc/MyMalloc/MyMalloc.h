#include <stdio.h>

typedef struct BoundaryTag
{
    // Real size of the object (the last bit is used to
    // check if the object is allocated
    size_t _objectSizeAndAlloc;

    // Real size of the previous contiguous chunk in memory
    size_t _leftObjectSize;
} BoundaryTag;

struct FreeObject;

typedef struct FreeListNode
{
    struct FreeObject * _next;    // Points to the next object in the freelist (if free)
    struct FreeObject * _prev;    // Points to the previous object
} FreeListNode;

// Header used by objects that are free
typedef struct FreeObject
{
    // NOTE: ALLOCATED OBJECTS JUST HAVE A BOUNDARY TAG
    BoundaryTag boundary_tag;
    FreeListNode free_list_node;
} FreeObject;

#define getSize(obj)    (((obj)->_objectSizeAndAlloc) & ~1)
#define setSize(obj, size) \
    ((obj)->_objectSizeAndAlloc = (size) | isAllocated(obj))

#define isAllocated(obj)    (((obj)->_objectSizeAndAlloc) & 1)
#define setAllocated(obj, alloc) \
    ((obj)->_objectSizeAndAlloc = (alloc) | getSize(obj))

// STATE of the allocator
// Size of the heap
size_t _heapSize;

// initial memory pool
void * _memStart;

// True if heap has been initialized
int _initialized;

// # malloc calls
int _mallocCalls;

// # free calls
int _freeCalls;

// # realloc calls
int _reallocCalls;

// # realloc calls
int _callocCalls;

// Free list
FreeObject * _freeList;
FreeObject _freeListSentinel;

//FUNCTIONS
//Prints the heap size and other information about the allocator
void print();
void print_list();

// Rounds to the nearest 8 bytes.
size_t roundupEight(size_t);
void * MyMalloc(size_t size);
void MyFree(void *ptr);
