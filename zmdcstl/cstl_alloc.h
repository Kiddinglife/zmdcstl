#ifndef MYCSTL_ALLOC_H
#define MYCSTL_ALLOC_H

#include <stddef.h>
#include "cstl_def.h"
#include "eaplatform.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define CSTL_ALLOCATOR_DEFAULT_NAME "default_cstl_allocator"

    /// allocate_memory
    ///
    /// This is a memory allocation dispatching function.
    /// To do: Make aligned and unaligned specializations.
    ///        Note that to do this we will need to use a class with a static
    ///        function instead of a standalone function like below.
    extern void* cstl_allocate_memory(const char* allocname, size_t n, size_t alignment, size_t alignmentOffset, int flags);
    extern void  cstl_deallocate_memory(const char* allocname, void* p, size_t n);

#ifdef __cplusplus
}
#endif

#endif

