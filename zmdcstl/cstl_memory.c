/*
 * cstl_memory.c
 *
 *  Created on: 6 Mar. 2018
 *      Author: jackiez
 */

#include "cstl_memory.h"
#include "cstl_iterator.h"
#include "cstl_types.h"

void uninitialized_default_fill_n(forward_iterator_t* destination, size_t n)
{
  assert(iterator_is_valid(destination));
  assert(iterator_limit_type(destination, _FORWARD_ITERATOR));
  type_info_t* info = ((type_info_t*) (destination->hdr->_pt_container));
  bool ret = false;
  switch (info->_t_typeids[0])
  {
  case ctype:
    memset(destination->_t_pos, 0, info->_pt_type->_t_typesize * n);
    break;
  case cstltype:
  case userdefined:
    info->_pt_type->_t_typeinit(destination->_t_pos, &ret);
    assert(ret);
    break;
  default:
    perror("uninitialized_default_fill_n()::no such type id (%d)\n");
    break;
  }
}

void uninitialized_default_fill(forward_iterator_t* first, forward_iterator_t* last)
{
  assert(iterator_is_valid(first) && iterator_is_valid(last));
  assert(iterator_limit_type(first, _FORWARD_ITERATOR) && iterator_limit_type(last, _FORWARD_ITERATOR));
  //bool ret = false;
}
