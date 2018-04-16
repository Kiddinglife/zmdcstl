#ifndef MYCSTL_ALLOC_H
#define MYCSTL_ALLOC_H

#include <stddef.h>
#include <stdlib.h>

#include "cstl_def.h"
#include "platform.h"

/**
 zmdcstlvec:0.000225ms, stdvec:4.9e-05ms, ratio: 4.59184
PASS benchmark_vector_ctor:  (17 ticks, 0.000 sec)

zmdcstlvec:857.225ms, stdvec:871.541ms, ratio: 0.983575
PASS benchmark_vector_ctor_n:  (2355771 ticks, 2.356 sec)

vec_ctor_n_v_non_pod:895.892ms, stdvec_n_v_non_pod:761.489ms, ratio: 1.1765
vec_ctor_n_v_pod:66.1894ms, stdvec_n_v_pod:62.2285ms, ratio: 1.06365
vec_ctor_n_v_ctype:5.83099ms, stdvec_n_v_ctype:4.84063ms, ratio: 1.20459
PASS benchmark_vector_ctor_n_v:  (2348910 ticks, 2.349 sec)

zmdcstlvec:865.683ms, stdvec:1017.74ms, ratio: 0.85059
PASS benchmark_vector_ctor_range:  (4005129 ticks, 4.005 sec)

zmdcstlvec:927.352ms, stdvec:934.37ms, ratio: 0.992489
PASS benchmark_vector_ctor_range_n:  (3594008 ticks, 3.594 sec)

cstl_vector_ctor_vector:934.768ms, std_vector_ctor_vector:945.215ms, ratio: 0.988948
PASS benchmark_vector_ctor_vector:  (3633350 ticks, 3.633 sec)

 * @param file
 * @param line
 * @param n
 * @param alignment
 */

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

#ifndef cstl_free(p)
#define cstl_free(p) if(p) free(*((void**) p - 1))
#endif

#ifndef cstl_memcpy
#define cstl_memcpy memcpy
#endif

extern void* cstl_alloc_(const char* file, int line, size_t n, size_t alignment);

#ifdef __cplusplus
}
#endif
#endif

