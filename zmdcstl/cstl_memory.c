/*
 * cstl_memory.c
 *
 *  Created on: 6 Mar. 2018
 *      Author: jackiez
 */

#include "cstl_memory.h"
#include "cstl_iterator.h"
#include "cstl_types.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4146)  // unary minus operator applied to unsigned type, result still unsigned
#endif

//TODO call container-specific impl

void* align(size_t alignment, size_t size, void** ptr, size_t* space)
{
  if (*space >= size)
  {
    char* ptrAligned =
        (char*) (((size_t) (*ptr) + (alignment - 1)) & -alignment);
    size_t offset = (size_t) (ptrAligned - (char*) (*ptr));
    if ((*space - size) >= offset) // Have to implement this in terms of subtraction instead of addition in order to handle possible overflow.
    {
      *ptr = ptrAligned;
      *space -= offset;
      return ptrAligned;
    }
  }
  return NULL;
}

void* align_advance(size_t alignment, size_t size, void* ptr, size_t space,
    void** ptrAdvanced /*=null*/, size_t* spaceReduced /*=null*/)
{
  if (space >= size)
  {
    char* ptrAligned = (char*) (((size_t) ptr + (alignment - 1)) & -alignment);
    size_t offset = (size_t) (ptrAligned - (char*) ptr);
    if ((space - size) >= offset) // Have to implement this in terms of subtraction instead of addition in order to handle possible overflow.
    {
      if (ptrAdvanced)
        *ptrAdvanced = (ptrAligned + size);
      if (spaceReduced)
        *spaceReduced = (space - (offset + size));
      return ptrAligned;
    }
  }
  return NULL;
}

void destruct_range(forward_iterator_t* first, forward_iterator_t* last)
{
  assert(iterator_is_valid(first) && iterator_is_valid(last));
  assert(
      iterator_limit_type(first, _FORWARD_ITERATOR)
          && iterator_limit_type(last, _FORWARD_ITERATOR));

  type_t* type = _ITERATOR_TYPE_INFO_TYPE(first);
  if (type->_t_typedestroy != NULL)
  {
    bool ret = false;
    for (; !iterator_equal(first, last); iterator_next(first))
    {
      type->_t_typedestroy(first->_t_pos, &ret);
      assert(ret);
    }
  }
}

void destruct_n(forward_iterator_t* first, int n)
{
  assert(iterator_is_valid(first));
  assert(iterator_limit_type(first, _FORWARD_ITERATOR));
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(first);
  if (type->_t_typedestroy)
  {
    bool ret = false;
    for (; n > 0; n--)
    {
      type->_t_typedestroy(first->_t_pos, &ret);
      iterator_next(first);
      assert(ret);
    }
  }
}

void destruct_at(input_iterator_t* destination)
{
  assert(iterator_is_valid(destination));
  assert(iterator_limit_type(destination, _INPUT_ITERATOR));
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(destination);
  if (type->_t_typedestroy)
  {
    bool ret = false;
    type->_t_typedestroy(destination->_t_pos, &ret);
    assert(ret);
  }
}

void uninitialized_default_fill_n(forward_iterator_t* destination, size_t n)
{
  assert(iterator_is_valid(destination));
  assert(iterator_limit_type(destination, _FORWARD_ITERATOR));
  bool ret = false;
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(destination);
  for (; n > 0; n--)
  {
    if (type->_t_typeinit)
      type->_t_typeinit(destination->_t_pos, &ret);
    else
      memset(destination->_t_pos, 0, type->_t_typesize);
    iterator_next(destination);
  }
}

void uninitialized_default_fill(forward_iterator_t* first,
    forward_iterator_t* last)
{
  assert(iterator_is_valid(first) && iterator_is_valid(last));
  assert(
      iterator_limit_type(first, _FORWARD_ITERATOR)
          && iterator_limit_type(last, _FORWARD_ITERATOR));
  bool ret = false;
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(first);
  for (; !iterator_equal(first, last); iterator_next(first))
  {
    if (type->_t_typeinit)
      type->_t_typeinit(first->_t_pos, &ret);
    else
      memset(first->_t_pos, 0, type->_t_typesize);
  }
}

void uninitialized_fill_n(forward_iterator_t* destination, const void* value,
    int n)
{
  assert(iterator_is_valid(destination));
  assert(iterator_limit_type(destination, _FORWARD_ITERATOR));
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(destination);
  for (; n > 0; n--)
  {
    if (type->_t_typecopy)
    {
      bool ret = false;
      type->_t_typecopy(destination->_t_pos, value, &ret);
      assert(ret);
    } else
    {
      cstl_memcpy(destination->_t_pos, value, type->_t_typesize);
    }
    iterator_next(destination);
  }
}

void uninitialized_fill(forward_iterator_t* first, forward_iterator_t* last,
    const void* value)
{
  assert(iterator_is_valid(first) && iterator_is_valid(last));
  assert(
      iterator_limit_type(first, _FORWARD_ITERATOR)
          && iterator_limit_type(last, _FORWARD_ITERATOR));
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(first);
  for (; !iterator_equal(first, last); iterator_next(first))
  {
    if (type->_t_typecopy)
    {
      bool ret = false;
      type->_t_typecopy(first->_t_pos, value, &ret);
      assert(ret);
    } else
    {
      cstl_memcpy(first->_t_pos, value, type->_t_typesize);
    }
  }
}

void uninitialized_copy(input_iterator_t* first, input_iterator_t* last,
    forward_iterator_t* result)
{
  assert(
      iterator_is_valid(first) && iterator_is_valid(last)
          && iterator_is_valid(result));
  assert(
      iterator_limit_type(first, _INPUT_ITERATOR)
          && iterator_limit_type(last, _INPUT_ITERATOR)
          && iterator_limit_type(result, _FORWARD_ITERATOR));
  assert(
      iterator_same_elem_type(first, last)
          && iterator_same_elem_type(first, result));
//  switch (_ITERATOR_CONTAINER_TYPE(first))
//  {
//    case _VECTOR_CONTAINER:
//      return vector_iterator_prev(bidirectional_iterator);
//      break;
//    case _LIST_CONTAINER:
//      //return _list_iterator_next(it_iter);
//      break;
//    case _DEQUE_CONTAINER:
//      // return _deque_iterator_next(it_iter);
//      break;
//    case _SLIST_CONTAINER:
//      //return _slist_iterator_next(it_iter);
//      break;
//    case _SET_CONTAINER:
//      //return _set_iterator_next(it_iter);
//      break;
//    case _MULTISET_CONTAINER:
//      //return _multiset_iterator_next(it_iter);
//      break;
//    case _MAP_CONTAINER:
//      //return _map_iterator_next(it_iter);
//      break;
//    case _MULTIMAP_CONTAINER:
//      //return _multimap_iterator_next(it_iter);
//      break;
//    case _HASH_SET_CONTAINER:
//      // return _hash_set_iterator_next(it_iter);
//      break;
//    case _HASH_MULTISET_CONTAINER:
//      //return _hash_multiset_iterator_next(it_iter);
//      break;
//    case _HASH_MAP_CONTAINER:
//      //return _hash_map_iterator_next(it_iter);
//      break;
//    case _HASH_MULTIMAP_CONTAINER:
//      //return _hash_multimap_iterator_next(it_iter);
//      break;
//    case _BASIC_STRING_CONTAINER:
//      //return _basic_string_iterator_next(it_iter);
//      break;
//    default:
//      assert(false);
//      break;
//  }

  type_t* type = _ITERATOR_TYPE_INFO_TYPE(first);
  if (_ITERATOR_ITERATOR_TYPE(first) == _RANDOM_ACCESS_ITERATOR&&
  _ITERATOR_ITERATOR_TYPE(last) == _RANDOM_ACCESS_ITERATOR &&
  type->_t_typecopy == NULL)
  {
    int n_step = iterator_distance(first, last);
    cstl_memcpy(result->_t_pos, first->_t_pos, n_step * type->_t_typesize);
    iterator_advance(result, n_step);
  } else
  {
    for (; !iterator_equal(first, last); iterator_next(first))
    {
      if (type->_t_typecopy)
      {
        bool ret = false;
        type->_t_typecopy(result->_t_pos, first->_t_pos, &ret);
        iterator_next(result);
        assert(ret);
      } else
      {
        cstl_memcpy(result->_t_pos, first->_t_pos, type->_t_typesize);
      }
    }
  }
}

void uninitialized_copy_n(input_iterator_t* first, int n_step,
    forward_iterator_t* result)
{
  assert(iterator_is_valid(first) && iterator_is_valid(result));
  assert(
      iterator_limit_type(first, _INPUT_ITERATOR)
          && iterator_limit_type(result, _FORWARD_ITERATOR));
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(first);
  if (_ITERATOR_ITERATOR_TYPE(first) == _RANDOM_ACCESS_ITERATOR
      && _ITERATOR_ITERATOR_TYPE(result) == _RANDOM_ACCESS_ITERATOR)
  {
    if (type->_t_typecopy == NULL)
    {
      cstl_memcpy(result->_t_pos, first->_t_pos, n_step * type->_t_typesize);
      iterator_advance(result, n_step);
    }
  } else
  {
    bool ret = false;
    for (; n_step > 0; --n_step)
    {
      type->_t_typecopy(result->_t_pos, first->_t_pos, &ret);
      iterator_next(result);
      iterator_next(first);
      assert(ret);
    }
  }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
