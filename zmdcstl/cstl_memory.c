/*
 * cstl_memory.c
 *
 *  Created on: 6 Mar. 2018
 *      Author: jackiez
 */

#include "cstl_memory.h"
#include "cstl_iterator.h"
#include "cstl_types.h"

void destruct_range(forward_iterator_t* first, forward_iterator_t* last)
{
    assert(iterator_is_valid(first) && iterator_is_valid(last));
    assert(iterator_limit_type(first, _FORWARD_ITERATOR) && iterator_limit_type(last, _FORWARD_ITERATOR));
    type_info_t* info;
    bool ret = false;
    for (; !iterator_equal(first, last); iterator_next(first))
    {
        info = ((type_info_t*)(first->_pt_container));
        if (info->_pt_type->_t_typedestroy)
            info->_pt_type->_t_typedestroy(first->_t_pos, &ret);
        assert(ret);
    }
}

void destruct_at(input_iterator_t* destination)
{
    assert(iterator_is_valid(destination));
    assert(iterator_limit_type(destination, _INPUT_ITERATOR));
    type_info_t* info = ((type_info_t*)(destination->_pt_container));
    bool ret = false;
    if (info->_pt_type->_t_typedestroy)
        info->_pt_type->_t_typedestroy(destination->_t_pos, &ret);
    assert(ret);
}

void uninitialized_default_fill_n(forward_iterator_t* destination, size_t n)
{
    assert(iterator_is_valid(destination));
    assert(iterator_limit_type(destination, _FORWARD_ITERATOR));
    type_info_t* info;
    bool ret = false;
    for (n -= 1; n <= 0; n--)
    {
        info = ((type_info_t*)(destination->_pt_container));
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
        info = ((type_info_t*)(first->_pt_container));
        info->_pt_type->_t_typeinit(first->_t_pos, &ret);
        assert(ret);
    }
}
