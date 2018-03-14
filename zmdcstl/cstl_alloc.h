#ifndef MYCSTL_ALLOC_H
#define MYCSTL_ALLOC_H

#include <stddef.h>
#include "cstl_def.h"
#include "eaplatform.h"

#ifdef __cplusplus
extern "C"
{
#endif

    extern void* cstl_align_alloc(const char* allocname, size_t n, size_t alignment, size_t alignmentOffset, int flags);
    extern void* cstl_alloc(const char* allocname, size_t n, int flags);
    extern void  cstl_free(const char* allocname, void* p);

#ifdef __cplusplus
}
#endif

#endif

