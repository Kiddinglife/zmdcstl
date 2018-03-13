/*
 * cstl_memory.c
 *
 *  Created on: 6 Mar. 2018
 *      Author: jackiez
 */

#include "cstl_memory.h"
#include "cstl_iterator.h"
#include "cstl_types.h"

#define cstl_memcpy memcpy

void destruct_range(forward_iterator_t* first, forward_iterator_t* last)
{
    assert(iterator_is_valid(first) && iterator_is_valid(last));
    assert(iterator_limit_type(first, _FORWARD_ITERATOR) && iterator_limit_type(last, _FORWARD_ITERATOR));
    type_info_t* info;
    bool ret = false;
    for (; !iterator_equal(first, last); iterator_next(first))
    {
        info = ((type_info_t*) (first->_pt_container));
        info->_pt_type->_t_typedestroy(first->_t_pos, &ret);
        assert(ret);
    }
}

void destruct_n(forward_iterator_t* first, int n)
{
    assert(iterator_is_valid(first));
    assert(iterator_limit_type(first, _FORWARD_ITERATOR));
    type_info_t* info;
    bool ret = false;
    for (; n > 0; n--)
    {
        info = ((type_info_t*) (first->_pt_container));
        info->_pt_type->_t_typeinit(first->_t_pos, &ret);
        iterator_next(first);
        assert(ret);
    }
}

void destruct_at(input_iterator_t* destination)
{
    assert(iterator_is_valid(destination));
    assert(iterator_limit_type(destination, _INPUT_ITERATOR));
    type_info_t* info = ((type_info_t*) (destination->_pt_container));
    bool ret = false;
    info->_pt_type->_t_typedestroy(destination->_t_pos, &ret);
    assert(ret);
}

void uninitialized_default_fill_n(forward_iterator_t* destination, size_t n)
{
    assert(iterator_is_valid(destination));
    assert(iterator_limit_type(destination, _FORWARD_ITERATOR));
    type_info_t* info;
    bool ret = false;
    for (; n > 0; n--)
    {
        info = ((type_info_t*) (destination->_pt_container));
        info->_pt_type->_t_typeinit(destination->_t_pos, &ret);
        iterator_next(destination);
        assert(ret);
    }
}

void uninitialized_default_fill(forward_iterator_t* first, forward_iterator_t* last)
{
    assert(iterator_is_valid(first) && iterator_is_valid(last));
    assert(iterator_limit_type(first, _FORWARD_ITERATOR) && iterator_limit_type(last, _FORWARD_ITERATOR));
    type_info_t* info;
    bool ret = false;
    for (; !iterator_equal(first, last); iterator_next(first))
    {
        info = ((type_info_t*) (first->_pt_container));
        info->_pt_type->_t_typeinit(first->_t_pos, &ret);
        assert(ret);
    }
}

void uninitialized_fill_n(forward_iterator_t* destination, const void* value, int n)
{
    assert(iterator_is_valid(destination));
    assert(iterator_limit_type(destination, _FORWARD_ITERATOR));
    type_info_t* info;
    bool ret = false;
    for (; n > 0; n--)
    {
        info = ((type_info_t*) (destination->_pt_container));
        info->_pt_type->_t_typecopy(destination->_t_pos, value, &ret);
        iterator_next(destination);
        assert(ret);
    }
}

void uninitialized_fill(forward_iterator_t* first, forward_iterator_t* last, const void* value)
{
    assert(iterator_is_valid(first) && iterator_is_valid(last));
    assert(iterator_limit_type(first, _FORWARD_ITERATOR) && iterator_limit_type(last, _FORWARD_ITERATOR));
    type_info_t* info;
    bool ret = false;
    for (; !iterator_equal(first, last); iterator_next(first))
    {
        info = ((type_info_t*) (first->_pt_container));
        info->_pt_type->_t_typecopy(first->_t_pos, value, &ret);
        assert(ret);
    }
}

void uninitialized_copy(input_iterator_t* first, input_iterator_t* last, forward_iterator_t* result)
{
    assert(iterator_is_valid(first) && iterator_is_valid(last) && iterator_is_valid(result));
    assert(
            iterator_limit_type(first, _INPUT_ITERATOR) && iterator_limit_type(last, _INPUT_ITERATOR)
                    && iterator_limit_type(result, _FORWARD_ITERATOR));
    assert(iterator_same_elem_type(first, last) && iterator_same_elem_type(first, result));

    type_info_t* info;
    bool ret = false;

    if (first->_t_iteratortype == _RANDOM_ACCESS_ITERATOR && result->_t_iteratortype == _RANDOM_ACCESS_ITERATOR
            && info->_pt_type == ctype)
    {
        int n_step = iterator_distance(first, last);
        cstl_memcpy(result->_t_pos, first->_t_pos,
                n_step * ((type_info_t*) (first->_pt_container))->_pt_type->_t_typesize);
        iterator_advance(result, n_step);
    }
    else
    {
        for (; !iterator_equal(first, last); iterator_next(first))
        {
            info = ((type_info_t*) (first->_pt_container));
            info->_pt_type->_t_typecopy(result->_t_pos, first->_t_pos, &ret);
            iterator_next(result);
            assert(ret);
        }
    }
}

void uninitialized_copy_n(input_iterator_t* first, int n_step, forward_iterator_t* result)
{
    assert(iterator_is_valid(first) && iterator_is_valid(result));
    assert(iterator_limit_type(first, _INPUT_ITERATOR) && iterator_limit_type(result, _FORWARD_ITERATOR));

    type_info_t* info;
    bool ret = false;

    if (first->_t_iteratortype == _RANDOM_ACCESS_ITERATOR && result->_t_iteratortype == _RANDOM_ACCESS_ITERATOR)
    {
        info = ((type_info_t*) (first->_pt_container));
        if()
        {

        }

        cstl_memcpy(result->_t_pos, first->_t_pos,
                n_step * ((type_info_t*) (first->_pt_container))->_pt_type->_t_typesize);
        iterator_advance(result, n_step);
    }
    else
    {
        for (; n_step > 0; --n_step)
        {
            info = ((type_info_t*) (first->_pt_container));
            info->_pt_type->_t_typecopy(result->_t_pos, first->_t_pos, &ret);
            iterator_next(result);
            iterator_next(first);
            assert(ret);
        }
    }

}
