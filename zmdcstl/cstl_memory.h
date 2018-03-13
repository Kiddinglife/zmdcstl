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
    extern void destruct_n(forward_iterator_t* first, int n);
    extern void destruct_at(input_iterator_t* first);

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

    /// uninitialized_fill
    ///
    /// Copy-constructs the elements in the destination range with the given input value.
    /// Returns void. It wouldn't be useful to return the end of the destination range, 
    /// as that is the same as the 'last' input parameter.
    extern void uninitialized_fill(forward_iterator_t* first, forward_iterator_t* last, const void* value);

    /// uninitialized_fill_n
    ///
    /// Copy-constructs the range of [first, first + n) with the given input value.
    /// Returns void as per the C++ standard, though returning the end input iterator
    /// value may be of use.
    extern void uninitialized_fill_n(forward_iterator_t* destination, const void* value, int n);

    /// uninitialized_copy
    ///
    /// Copies a source range to a destination, copy-constructing the destination with
    /// the source values (and not *assigning* the destination with the source values).
    /// Returns the end of the destination range (i.e. dest + (last - first)).
    ///
    /// Example usage:
    ///    SomeClass* pArray = malloc(10 * sizeof(SomeClass));
    ///    uninitialized_copy(pSourceDataBegin, pSourceDataBegin + 10, pArray);
    ///
    extern void uninitialized_copy(input_iterator_t* first, input_iterator_t* last, forward_iterator_t* result);

    /// uninitialized_copy_n
    ///
    /// Copies count elements from a range beginning at first to an uninitialized memory area 
    /// beginning at dest. The elements in the uninitialized area are constructed using copy constructor.
    /// If an exception is thrown during the initialization, the function has no final effects. 
    ///
    /// first:        Beginning of the range of the elements to copy.
    /// dest:         Beginning of the destination range.
    /// return value: Iterator of dest type to the element past the last element copied.
    ///
    extern void uninitialized_copy_n(input_iterator_t* first, int n_step, forward_iterator_t* result);

#ifdef __cplusplus
}
#endif

#endif /* MYCSTL_CSTL_MEMORY_H_ */
