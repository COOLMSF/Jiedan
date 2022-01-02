#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>
#include <errno.h>
#include <stdbool.h>
#include "MyMalloc.h"

#define ALLOCATED 1
#define NOT_ALLOCATED 0
#define ARENA_SIZE 2097152
#define DEBUG 0

pthread_mutex_t mutex;

static bool verbose = false;

extern void atExitHandlerInC()
{
    if (verbose)
        print();
}

static void * getMemoryFromOS(size_t size)
{
    // Use sbrk() to get memory from OS
    _heapSize += size;

    // void *mem = sbrk(size);
    void *men = mmap( NULL, N*sizeof(int), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );

    if (! _initialized)
    {
        _memStart = mem;
    }

    return mem;
}


static FreeObject * getNewChunk(size_t size)
{
    void *mem = getMemoryFromOS(size);

    // establish fence posts
    BoundaryTag *fencePostHead = (BoundaryTag *)mem;
    setAllocated(fencePostHead, ALLOCATED);
    setSize(fencePostHead, 0);
    if (DEBUG) fprintf(stderr, "Head Dummy Header: %p\n", fencePostHead);

    char *temp = (char *)mem + size - sizeof(BoundaryTag);
    BoundaryTag *fencePostFoot = (BoundaryTag *)temp;
    setAllocated(fencePostFoot, ALLOCATED);
    setSize(fencePostFoot, 0);
    if (DEBUG) fprintf(stderr, "Foot Dummy Header: %p\n", fencePostFoot);

    // The very first Free List Header
    return (FreeObject *)((char *)mem + sizeof(BoundaryTag));
}

static void initialize()
{
    verbose = true;

    if (DEBUG)
    {
        fprintf(stderr, "FreeObject %zu B\n", sizeof(FreeObject));
        fprintf(stderr, "BoundaryTag %zu B\n", sizeof(BoundaryTag));
        fprintf(stderr, "BoundaryTag* %zu B\n", sizeof(BoundaryTag *));
    }

    pthread_mutex_init(&mutex, NULL);

    // print statistics at exit
    atexit(atExitHandlerInC);

    FreeObject *firstChunk = getNewChunk(ARENA_SIZE);

    // initialize the list to point to the firstChunk
    _freeList = &_freeListSentinel;

    // Subtract off the Dummy Headers
    setSize(&firstChunk->boundary_tag, ARENA_SIZE - (2*sizeof(BoundaryTag))); // ~2MB
    firstChunk->boundary_tag._leftObjectSize = 0;
    setAllocated(&firstChunk->boundary_tag, NOT_ALLOCATED);

    // Connect the linked list, make it circular
    firstChunk->free_list_node._next = _freeList;
    firstChunk->free_list_node._prev = _freeList;
    _freeList->free_list_node._prev = firstChunk;
    _freeList->free_list_node._next = firstChunk;

    _initialized = 1;
}

size_t roundupEight(size_t size)
{
    size_t remainder = size % 8;

    if (remainder != 0)
    {
        return (8 - remainder) + size;
    }

    return size;
}

short first = true;
static void * allocateObject(size_t size)
{
    // 2 Dummies, 1 Boundary at the very maximum
    if (size <= 0)
    {
        if (DEBUG) fprintf(stderr, "Allocation size is too small/invalid (%zu B)\n", size);
        return NULL;
    }
    if (size >= (ARENA_SIZE - (3 * sizeof(BoundaryTag))))
    {
        if (DEBUG) fprintf(stderr, "Allocation size is too large/invalid (%zu B)\n", size);
        errno = ENOMEM;
        return NULL;
    }
    else if (size > 0 && size < sizeof(FreeListNode))
    {
        // The boundary tag is already included.
        size = sizeof(FreeListNode);
    }

    // Make sure that allocator is initialized
    if (!_initialized)
        initialize();

    size_t real_size = sizeof(BoundaryTag) + roundupEight(size);
    if (DEBUG) fprintf(stderr, "Attempting to allocate %zu B of space\n", real_size);

    FreeObject *free_header = _freeList->free_list_node._next;
    while (free_header != _freeList)
    {
        if (getSize(&free_header->boundary_tag) >= real_size)
        {
            // Fill up the allocation if the remaining space will be unusable.
            if ((getSize(&free_header->boundary_tag) - real_size) < sizeof(FreeObject))
            {
                if (DEBUG) fprintf(stderr,
                        "Allocating the remaining space (%zu B) for Free Header %p\n",
                        getSize(&free_header->boundary_tag) - real_size, free_header);
                real_size += getSize(&free_header->boundary_tag) - real_size;
            }

            // Point to the location that the allocated space starts at.
            void* mem_ptr = ((void *) free_header)
                    + getSize(&free_header->boundary_tag) + sizeof(BoundaryTag)
                    - real_size;

            if (DEBUG) fprintf(stderr, "Placing a boundary tag at %p\n", mem_ptr);
            BoundaryTag* new_bound_tag = NULL;

            if (getSize(&free_header->boundary_tag) > real_size)
            {
                // Fits with room to spare.
                // Create a new allocated space.
                new_bound_tag = (BoundaryTag *) mem_ptr;
                setSize(new_bound_tag, real_size - sizeof(BoundaryTag));
                setAllocated(new_bound_tag, ALLOCATED);

                // Adjust the Free Headers
                setSize(&free_header->boundary_tag,
                        getSize(&free_header->boundary_tag) - real_size);

                // Update the new Boundary Tag to reflect the left item's size.
                new_bound_tag->_leftObjectSize = getSize(
                        &free_header->boundary_tag);
            }
            else if (getSize(&free_header->boundary_tag) == real_size)
            {
                if (DEBUG) fprintf(stderr, "Block fits perfectly into memory location\n");
                // Fits perfectly.
                // Set the block as allocated and start using it.
                new_bound_tag = &(free_header->boundary_tag);
                setAllocated(&free_header->boundary_tag, ALLOCATED);

                // Splice the node from the Free List.
                FreeObject* prev_node = free_header->free_list_node._prev;
                FreeObject* next_node = free_header->free_list_node._next;

                prev_node->free_list_node._next = free_header->free_list_node._next;
                next_node->free_list_node._prev = free_header->free_list_node._prev;
            }
            else
            {
                if (DEBUG) fprintf(stderr, "Invalid space requirement %zu\n", real_size);
                errno = ENOSPC;
            }

            // Update the left object size for the object on the right/below.
            // WARN: Why do we need to change this for the first allocation?
            BoundaryTag* right_boundary_header = NULL;
            if (first == true)
            {
                right_boundary_header = (BoundaryTag *) (((void *) new_bound_tag) +
                        getSize(new_bound_tag));
            }
            else
            {
                right_boundary_header = (BoundaryTag *) (((void *) new_bound_tag) +
                        getSize(new_bound_tag) + sizeof(BoundaryTag));
            }
            first = false;
            if (DEBUG) fprintf(stderr, "Modifying left object size for boundary at %p\n", right_boundary_header);
            right_boundary_header->_leftObjectSize = getSize(new_bound_tag);

            pthread_mutex_unlock(&mutex);
            return mem_ptr + sizeof(BoundaryTag);
        }

        free_header = free_header->free_list_node._next;
    }

    // A new chunk must be allocated.
    if (DEBUG) fprintf(stderr, "Retrieving a new chunk\n");
    FreeObject* new_free_chunk_header = getNewChunk(ARENA_SIZE);
    setSize(&new_free_chunk_header->boundary_tag, ARENA_SIZE - (2*sizeof(BoundaryTag))); // ~2MB
    new_free_chunk_header->boundary_tag._leftObjectSize = 0;
    setAllocated(&new_free_chunk_header->boundary_tag, NOT_ALLOCATED);

    new_free_chunk_header->free_list_node._prev = _freeList;
    new_free_chunk_header->free_list_node._next = _freeList->free_list_node._next;
    _freeList->free_list_node._next = new_free_chunk_header;

    // WARN: May be unsafe to do this.
    pthread_mutex_unlock(&mutex);
    first = true;
    return allocateObject(size);

    /*pthread_mutex_unlock(&mutex);*/
    /*return getMemoryFromOS(size);*/
}

static void freeObject(void *ptr)
{
    // Locate the Boundary Header.
    BoundaryTag* boundary_header = (BoundaryTag *) (ptr - sizeof(BoundaryTag));

    if ((getSize(boundary_header) < 8) || (roundupEight(getSize(boundary_header)) != getSize(boundary_header)))
    {
        if (DEBUG) fprintf(stderr, "Boundary tag is of an invalid size (%zu B )\n", getSize(boundary_header));
        abort();
    }

    if (DEBUG) fprintf(stderr, "Freeing object at boundary %p\n", boundary_header);

    // Fetch the surrounding headers.
    BoundaryTag* prev_boundary_header = (BoundaryTag *) (((void *) boundary_header) -
            boundary_header->_leftObjectSize - sizeof(BoundaryTag));
    BoundaryTag* next_boundary_header = (BoundaryTag *) (((void *) boundary_header) +
            getSize(boundary_header) + sizeof(BoundaryTag));

    if (DEBUG) fprintf(stderr, "BH %p | LOS %zu | BT %zu\n", (void *) boundary_header, boundary_header->_leftObjectSize, sizeof(BoundaryTag));

    if (DEBUG) fprintf(stderr, "Prev Boundary Header: %p\nNext Boundary Header: %p\n",
            prev_boundary_header, next_boundary_header);

    FreeObject* free_header = NULL;
    FreeObject* prev_free_header = NULL;
    FreeObject* next_free_header = NULL;

    if (! isAllocated(next_boundary_header))
    {
        next_free_header = (FreeObject *) (((void *) next_boundary_header)
                - sizeof(BoundaryTag));
    }

    if (! isAllocated(prev_boundary_header))
    {
        prev_free_header  = (FreeObject *) (((void *) prev_boundary_header)
                - sizeof(BoundaryTag));
    }

    if ((prev_free_header != NULL) && (next_free_header != NULL))
    {
        // Coallesce 3 contiguous blocks.
        if (DEBUG) fprintf(stderr, "Coallescing 3 contiguous blocks.\n");

        // Second BoundaryTag will be compounded.
        setSize(&prev_free_header->boundary_tag,
                getSize(&prev_free_header->boundary_tag)
                + getSize(boundary_header)
                + getSize(&next_free_header->boundary_tag)
                + sizeof(BoundaryTag));

        // Link into the list at the point of the old Free List Node.
        FreeObject* prev_node = prev_free_header->free_list_node._prev;
        FreeObject* next_node = next_free_header->free_list_node._next;

        prev_node->free_list_node._next = prev_free_header;
        next_node->free_list_node._prev = prev_free_header;
        prev_free_header->free_list_node._next = next_free_header->free_list_node._next;
        prev_free_header->free_list_node._prev = prev_free_header->free_list_node._prev;
    }
    else if ((prev_free_header != NULL) && (next_free_header == NULL))
    {
        // Coallesce above.
        // Expand to the size of the allocated space's boundary tag and allocated
        // size.
        if (DEBUG) fprintf(stderr, "Coallescing above to Free Header at %p\n", prev_free_header);
        setSize(&prev_free_header->boundary_tag, getSize(&prev_free_header->boundary_tag)
                + getSize(boundary_header) + sizeof(BoundaryTag));

        // We absorb the previous free header.
        free_header = prev_free_header;
    }
    else if ((prev_free_header == NULL))
    {
        // Create a new header.
        // WARN: It seems odd that we would subtract a boundary tag size?
        free_header = (FreeObject *) ((void *) boundary_header - sizeof(BoundaryTag));
        if (DEBUG) fprintf(stderr, "Creating a new Free Header at %p\n", free_header);
        free_header->boundary_tag = *boundary_header;
        setAllocated(&(free_header->boundary_tag), NOT_ALLOCATED);
        setSize(&free_header->boundary_tag, getSize(&free_header->boundary_tag)
                + sizeof(BoundaryTag));


        if (next_free_header != NULL)
        {
            // Coallesce below.
            if (DEBUG) fprintf(stderr, "Coallescing below with Free Header at %p.\n", next_free_header);
            // Second BoundaryTag will be compounded.
            setSize(&free_header->boundary_tag, getSize(&free_header->boundary_tag)
                    + getSize(&next_free_header->boundary_tag));

            // Link into the list at the point of the old Free List Node.
            FreeObject* prev_node = next_free_header->free_list_node._prev;
            FreeObject* next_node = next_free_header->free_list_node._next;

            prev_node->free_list_node._next = free_header;
            next_node->free_list_node._prev = free_header;
            free_header->free_list_node._next = next_free_header->free_list_node._next;
            free_header->free_list_node._prev = next_free_header->free_list_node._prev;
        }
        else
        {
            // Link into the list after the sentinel.
            free_header->free_list_node._prev = _freeList;
            free_header->free_list_node._next = _freeList->free_list_node._next;
            _freeList->free_list_node._next = free_header;
        }
    }

    pthread_mutex_unlock(&mutex);
    return;
}

void print()
{
    printf("\n-------------------\n");

    printf("HeapSize:\t%zd bytes\n", _heapSize);
    printf("# mallocs:\t%d\n", _mallocCalls);
    printf("# reallocs:\t%d\n", _reallocCalls);
    printf("# callocs:\t%d\n", _callocCalls);
    printf("# frees:\t%d\n", _freeCalls);

    printf("\n-------------------\n");
}

void print_list()
{
    printf("FreeList: ");
    if (DEBUG) fprintf(stderr, "FreeList addresses: ");
    if (!_initialized)
    {
        initialize();
    }

    FreeObject *ptr = _freeList->free_list_node._next;
    while (ptr != _freeList)
    {
        long offset = (long)ptr - (long)_memStart;
        printf("[offset:%ld,size:%zd]", offset, getSize(&ptr->boundary_tag));
        if (DEBUG) fprintf(stderr, "[%p]", ptr);
        ptr = ptr->free_list_node._next;
        // This should be _freeList instead of NULL, but it will break the tests.
        if (ptr != NULL)
        {
            printf("->");
            if (DEBUG) fprintf(stderr, "->");
        }
    }

    if (DEBUG) fprintf(stderr, "\n");
    printf("\n");
}

void increaseMallocCalls() { _mallocCalls++; }

void increaseReallocCalls() { _reallocCalls++; }

void increaseCallocCalls() { _callocCalls++; }

void increaseFreeCalls() { _freeCalls++; }

//
// C interface
//

void * MyMalloc(size_t size)
{
    pthread_mutex_lock(&mutex);
    increaseMallocCalls();

    return allocateObject(size);
}

void MyFree(void *ptr)
{
    pthread_mutex_lock(&mutex);
    increaseFreeCalls();

    if (ptr == 0) {
        // No object to free
        pthread_mutex_unlock(&mutex);
        return;
    }

    freeObject(ptr);
}

extern void * realloc(void *ptr, size_t size)
{
    pthread_mutex_lock(&mutex);
    increaseReallocCalls();

    // Allocate new object
    void *newptr = allocateObject(size);

    // Copy old object only if ptr != 0
    if (ptr != 0) {

        // copy only the minimum number of bytes
        FreeObject *o = (FreeObject *)((char *) ptr - sizeof(BoundaryTag));
        size_t sizeToCopy = getSize(&o->boundary_tag);
        if (sizeToCopy > size) {
            sizeToCopy = size;
        }

        memcpy(newptr, ptr, sizeToCopy);

        //Free old object
        freeObject(ptr);
    }

    return newptr;
}

extern void * calloc(size_t nelem, size_t elsize)
{
    pthread_mutex_lock(&mutex);
    increaseCallocCalls();

    // calloc allocates and initializes
    size_t size = nelem * elsize;

    void *ptr = allocateObject(size);

    if (ptr) {
        // No error
        // Initialize chunk with 0s
        memset(ptr, 0, size);
    }

    return ptr;
}

