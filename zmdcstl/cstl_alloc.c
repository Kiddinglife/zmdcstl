#include "cstl_alloc.h"
#include <stdint.h>

void* cstl_alloc_(const char* file, int line, size_t n, size_t alignment)
{
    assert((alignment & (alignment - 1)) == 0); // must be powers 2
    assert((n % alignment) == 0); // must be multiples of alignment

    size_t adjustedAlignment = (alignment > EA_PLATFORM_PTR_SIZE) ? alignment : EA_PLATFORM_PTR_SIZE;

    // ptr offset plus alignment offset
    void* p = malloc(n + adjustedAlignment + EA_PLATFORM_PTR_SIZE);

    // making sure memory addresses are aligned to the nearest power of two
    void* pAligned = (void*) (((uintptr_t) p + EA_PLATFORM_PTR_SIZE + adjustedAlignment - 1) & ~(adjustedAlignment - 1));

    // store p behind our aligned pointer
    *((void**) pAligned - 1) = p;

    assert((uintptr_t )((void** ) pAligned - 1) >= (uintptr_t )p);

    // Ensure the result is correctly aligned.  An assertion here may indicate a bug in the allocator.
    // An assertion likely indicates a mismatch between EASTL_ALLOCATOR_MIN_ALIGNMENT and the minimum alignment
    // of EASTLAlloc.  If there is a mismatch it may be necessary to define EASTL_ALLOCATOR_MIN_ALIGNMENT to be the minimum alignment of EASTLAlloc, or
    // to increase the alignment of EASTLAlloc to match EASTL_ALLOCATOR_MIN_ALIGNMENT.
    assert(((uintptr_t )(pAligned) & ~(alignment - 1)) == (uintptr_t )(pAligned));

    return pAligned;
}

