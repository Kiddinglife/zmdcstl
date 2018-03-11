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

    typedef struct _tagalloc_ret
    {
        void* tr;
        size_t n;
    }alloc_pair;

    /// destruct
    ///
    /// Calls the destructor on a range of objects.
    ///
    /// We have a specialization for objects with trivial destructors, such as
    /// PODs. In this specialization the destruction of the range is a no-op.
    extern void destruct_range(forward_iterator_t* first, forward_iterator_t* last);
    extern void destruct_at(input_iterator_t* first);

    /**
    * Initialize an element according to the type of iterator pointed data.
    * @param it_iter      iterator.
    * @return initilaized element.
    * @remarks iterator must be valid, otherwise behavior is undefined.
    */
    extern void* allocate_init_elem(const iterator_t* it_iter);

    /**
    * Destroy and deallocate element allocated and initialized by _iterator_allocate_init_elem().
    * @param it_iter      iterator.
    * @return void.
    * @remarks iterator must be valid and pv_value must be not NULL, otherwise behavior is undefined.
    */
    extern void deallocate_destroy_elem(iterator_t* it_iter, void* pv_value);

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
