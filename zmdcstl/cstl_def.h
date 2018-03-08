#ifndef _CSTL_DEF_H_
#define _CSTL_DEF_H_

#ifdef __cplusplus
extern "C"
{
#endif

#if __STDC_VERSION__ < 201112L
#error "your compiler does not support c11!"
#endif

/** include section **/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <ctype.h>
#include <float.h>
#include <time.h>
#include <stdbool.h>

#ifndef va_copy
#define va_copy(dest, src) ((dest) = (src))
#endif

/**
 * libcstl version macro.
 */
#define CSTL_VERSION             20300 /* version 2.3.0 */
#define CSTL_MAJOR_VERSION       2
#define CSTL_MINOR_VERSION       3
#define CSTL_REVISION_VERSION    0

/** data type declaration and struct, union, enum section **/
typedef unsigned char _byte_t;

/** exported global variable declaration section **/

/** exported function prototype section **/

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_DEF_H_ */
/** eof **/

