#ifndef MYCSTL_ALLOC_H
#define MYCSTL_ALLOC_H

#include <stddef.h>
#include <stdlib.h>

#include "cstl_def.h"
#include "platform.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef CSTL_ALIGN_OF
#if   defined(_MSC_VER) && (_MSC_VER < 1700)
// Workaround for this VS 2010 compiler bug: https://connect.microsoft.com/VisualStudio/feedback/details/682695
#define CSTL_ALIGN_OF(...) ( (sizeof(__VA_ARGS__)*0) + (__alignof(__VA_ARGS__)) )
#elif !defined(__GNUC__) || (__GNUC__ >= 3) // GCC 2.x doesn't do __alignof correctly all the time.
#define CSTL_ALIGN_OF __alignof
#else
#define CSTL_ALIGN_OF(type) ((size_t)offsetof(struct{ char c; type m; }, m))
#endif
#endif

// these two macros are the same except that first one receives type but second one receives value parameters
#ifndef NDEBUG
#define cstl_alloc(type, n) ((type*)cstl_alloc_(__FILE__,__LINE__,sizeof(type)*(n), CSTL_ALIGN_OF(type)))
#define cstl_alloc_ex(sizeoftype,align,n) cstl_alloc_(__FILE__,__LINE__,(n)*(sizeoftype),align)
#define cstl_alloc_ex_totaln(align,n) cstl_alloc_(__FILE__,__LINE__,(n),align)
#else
#define cstl_alloc(type, n) ((type*)cstl_alloc_(0,0,sizeof(type)*(n), CSTL_ALIGN_OF(type)))
#define cstl_alloc_ex(sizeoftype,align,n) ((type*)cstl_alloc_(0,0,(n)*(sizeoftype),align))
#define cstl_alloc_ex_totaln(align,n) cstl_alloc_(0,0,(n),align)
#endif

#define cstl_free(p) if(p) free(*((void**) p - 1))

extern void* cstl_alloc_(const char* file, int line, size_t n, size_t alignment);

#if (defined(__GNUC__) || defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__))
#ifndef cstl_memcpy
#define cstl_memcpy memcpy_fast
#endif
extern void* memcpy_fast(void *destination, const void *source, size_t size);
#else
#ifndef cstl_memcpy
#define cstl_memcpy memcpy
#endif
#endif

#ifdef __cplusplus
}
#endif
#endif

