/*
 * cstl_memory.h
 *
 *  Created on: 6 Mar. 2018
 *      Author: jackiez
 */

#ifndef MYCSTL_CSTL_MEMORY_H_
#define MYCSTL_CSTL_MEMORY_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include "cstl_iterator.h"

/// uninitialized_default_fill_n
///
/// Default-constructs the range of [first, first + n).
/// Returns void as per the C++ standard, though returning the end input iterator
/// value may be of use.
extern void uninitialized_default_fill_n(forward_iterator_t* destination, size_t n);

/// uninitialized_default_fill
///
/// Default-constructs the elements in the destination range.
/// Returns void. It wouldn't be useful to return the end of the destination range,
/// as that is the same as the 'last' input parameter.
extern void uninitialized_default_fill(forward_iterator_t* first, forward_iterator_t* last);

#ifdef __cplusplus
}
#endif

#endif /* MYCSTL_CSTL_MEMORY_H_ */
