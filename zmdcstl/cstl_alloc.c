#include "cstl_alloc.h"

void* cstl_alloc(const char* allocname, size_t n, int flags)
{
    return malloc(n);
}

void* cstl_align_alloc(const char* allocname, size_t n, size_t alignment, size_t alignmentOffset, int flags)
{
    if (alignment < EA_PLATFORM_MIN_MALLOC_ALIGNMENT)
        alignment = EA_PLATFORM_MIN_MALLOC_ALIGNMENT;

    size_t adjustedAlignment = (alignment > EA_PLATFORM_PTR_SIZE) ? alignment : EA_PLATFORM_PTR_SIZE;
    void* p = malloc(n + adjustedAlignment + EA_PLATFORM_PTR_SIZE);
    void* pPlusPointerSize = (void*)((uintptr_t)p + EA_PLATFORM_PTR_SIZE);
    void* pAligned = (void*)(((uintptr_t)pPlusPointerSize + adjustedAlignment - 1) & ~(adjustedAlignment - 1));
    void** pStoredPtr = (void**)pAligned - 1;
    assert(pStoredPtr >= p);
    *(pStoredPtr) = p;

    //  if (alignment <= EA_PLATFORM_MIN_MALLOC_ALIGNMENT)
    // Ensure the result is correctly aligned.  An assertion likely indicates a mismatch between EASTL_ALLOCATOR_MIN_ALIGNMENT and the minimum alignment
    // of EASTLAlloc.  If there is a mismatch it may be necessary to define EASTL_ALLOCATOR_MIN_ALIGNMENT to be the minimum alignment of EASTLAlloc, or
    // to increase the alignment of EASTLAlloc to match EASTL_ALLOCATOR_MIN_ALIGNMENT.
    //
    // if (alignment > EA_PLATFORM_MIN_MALLOC_ALIGNMENT)
    // Ensure the result is correctly aligned.  An assertion here may indicate a bug in the allocator.
    assert(((size_t)(pAligned)& ~(alignment - 1)) == (size_t)(pAligned));

    return pAligned;
}

void  cstl_free(const char* allocname, void* p)
{
    free(*((void**)p - 1));
}
