#include "cstl_alloc.h"

static void* cstl_allocate_ex(const char* allocname, size_t n, size_t alignment, size_t offset, int flags /*= 0*/)
{
   return  _aligned_offset_malloc(n, alignment, offset);
}

static void* cstl_allocate(const char* allocname, size_t n, int flags /*= 0*/)
{
    return  malloc(n);
}

 void* cstl_allocate_memory(const char* allocname, size_t n, size_t alignment, size_t alignmentOffset, int flags)
{
    void *result;
    if (alignment <= EA_PLATFORM_MIN_MALLOC_ALIGNMENT)
    {
        result = cstl_allocate(allocname, n, flags);
        // Ensure the result is correctly aligned.  An assertion likely indicates a mismatch between EASTL_ALLOCATOR_MIN_ALIGNMENT and the minimum alignment
        // of EASTLAlloc.  If there is a mismatch it may be necessary to define EASTL_ALLOCATOR_MIN_ALIGNMENT to be the minimum alignment of EASTLAlloc, or
        // to increase the alignment of EASTLAlloc to match EASTL_ALLOCATOR_MIN_ALIGNMENT.
        assert(((size_t)(result)& ~(alignment - 1)) == (size_t)(result));
    }
    else
    {
        result = cstl_allocate_ex(allocname, n, alignment, alignmentOffset, flags);
        // Ensure the result is correctly aligned.  An assertion here may indicate a bug in the allocator.
        assert(((size_t)(result)& ~(alignment - 1)) == (size_t)(result));
    }
    return result;
}

void  cstl_deallocate_memory(const char* allocname, void* p, size_t n)
 {
    free(p);
 }
