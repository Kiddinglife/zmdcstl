/*
 * cstl_memory.c
 *
 *  Created on: 6 Mar. 2018
 *      Author: jackiez
 */

#include "cstl_memory.h"
#include "cstl_types.h"
#include "cstl_iterator.h"

#include "cstl_vector.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4146)  // unary minus operator applied to unsigned type, result still unsigned
#endif

//TODO call container-specific impl

void* align(size_t alignment, size_t size, void** ptr, size_t* space)
{
  if (*space >= size)
  {
    char* ptrAligned = (char*) (((size_t) (*ptr) + (alignment - 1)) & -alignment);
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

void* align_advance(size_t alignment, size_t size, void* ptr, size_t space, void** ptrAdvanced /*=null*/,
    size_t* spaceReduced /*=null*/)
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

void destruct(forward_iterator_t* first, forward_iterator_t* last)
{
  assert(iterator_is_valid(first) && iterator_is_valid(last));

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
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(destination);
  if (type->_t_typedestroy)
  {
    bool ret;
    type->_t_typedestroy(destination->_t_pos, &ret);
  }
}
void destruct_at_vec(type_t* type, _byte_t* destination)
{
  if (type->_t_typedestroy)
  {
    bool ret;
    type->_t_typedestroy(destination, &ret);
  }
}
void destruct_vec(type_t* type, _byte_t* first, _byte_t* end)
{
  ufun_t dtor = type->_t_typedestroy;
  if (dtor)
  {
    bool ret;
    size_t tsize = type->_t_typesize;
    for (; first != end; first += tsize)
      dtor(first, &ret);
  }
}
void destruct_n_vec(type_t* type, _byte_t* first, size_t totalbytes)
{
  ufun_t dtor = type->_t_typedestroy;
  if (dtor)
  {
    bool ret;
    _byte_t* end = first + totalbytes;
    size_t tsize = type->_t_typesize;
    for (; first != end; first += tsize)
    {
      // free elment
      dtor(first, &ret);
    }
  }
}

void uninitialized_default_fill_n(forward_iterator_t* destination, size_t n)
{
  assert(iterator_is_valid(destination));
  bool ret = false;
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(destination);
  ufun_t dctor = type->_t_typeinit;
  if (dctor)
  {
    for (; n > 0; n--)
    {
      dctor(destination->_t_pos, &ret);
      iterator_next(destination);
    }
  }
  else
  {
    for (; n > 0; n--, iterator_next(destination))
      memset(destination->_t_pos, 0, type->_t_typesize);
  }
}

void uninitialized_fill_n(forward_iterator_t* destination, const void* value, int n)
{
  assert(iterator_is_valid(destination));
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(destination);
  for (; n > 0; n--)
  {
    if (type->_t_typecopy)
    {
      bool ret = false;
      type->_t_typecopy(destination->_t_pos, value, &ret);
      assert(ret);
    }
    else
    {
      cstl_memcpy(destination->_t_pos, value, type->_t_typesize);
    }
    iterator_next(destination);
  }
}
_byte_t* uninitialized_default_fill_n_continue(type_t* type, _byte_t* destination, size_t totalbytes)
{
  ufun_t init = type->_t_typeinit;
  _byte_t* end = destination + totalbytes;
  if (init)
  {
    bool ret;
    totalbytes = type->_t_typesize;
    for (; destination != end; destination += totalbytes)
      init(destination, &ret);
  }
  else
  {
    memset(destination, 0, totalbytes);
  }
  return end;
}

void uninitialized_fill_continue(type_t* type, _byte_t* first, _byte_t* e, void* val)
{
  bfun_t cpyctor = type->_t_typecopy;
  switch (type->_t_typeid) {
    case cstl_int8:
      fill_char((char*) first, e, *(char*) val);
      break;
    case cstl_uint8:
      fill_uchar((unsigned char*) first, e, *(unsigned char*) val);
      break;
    case cstl_int16:
      fill_int16((int16_t*) first, e, *(int16_t*) val);
      break;
    case cstl_uint16:
      fill_uint16((uint16_t*) first, e, *(uint16_t*) val);
      break;
    case cstl_int32:
      fill_int32((int32_t*) first, e, *(int32_t*) val);
      break;
    case cstl_uint32:
      fill_uint32((uint32_t*) first, e, *(uint32_t*) val);
      break;
    case cstl_int64:
      fill_int64((int64_t*) first, e, *(int64_t*) val);
      break;
    case cstl_uint64:
      fill_uint64((uint64_t*) first, e, *(uint64_t*) val);
      break;
    case cstl_void_pt:
      fill_uint64((uint64_t*) first, e, *(uint64_t*) val);
      break;
    default:
      if (cpyctor)
      { // heap-allocation inside this struct
        bool is_copy_assign = false;
        size_t tsize = type->_t_typesize;
        for (; first != e; first += tsize)
          cpyctor(first, val, &is_copy_assign);
      }
      else
      { // pod struct
        size_t tsize = type->_t_typesize;
        for (; first != e; first += tsize)
          cstl_memcpy(first, val, tsize);
      }
      break;
  }
}
_byte_t* uninitialized_fill_n_continue(type_t* type, _byte_t* destPosition, size_t totalbytes, const void* val)
{
  bfun_t cpyctor = type->_t_typecopy;
  _byte_t* end = destPosition + totalbytes;
  switch (type->_t_typeid) {
    case cstl_int8:
      fill_char((char*) destPosition, end, *(char*) val);
      break;
    case cstl_uint8:
      fill_uchar((unsigned char*) destPosition, end, *(unsigned char*) val);
      break;
    case cstl_int16:
      fill_int16((int16_t*) destPosition, end, *(int16_t*) val);
      break;
    case cstl_uint16:
      fill_uint16((uint16_t*) destPosition, end, *(uint16_t*) val);
      break;
    case cstl_int32:
      fill_int32((int32_t*) destPosition, end, *(int32_t*) val);
      break;
    case cstl_uint32:
      fill_uint32((uint32_t*) destPosition, end, *(uint32_t*) val);
      break;
    case cstl_int64:
      fill_int64((int64_t*) destPosition, end, *(int64_t*) val);
      break;
    case cstl_uint64:
      fill_uint64((uint64_t*) destPosition, end, *(uint64_t*) val);
      break;
    case cstl_void_pt:
      fill_uint64((uint64_t*) destPosition, end, *(uint64_t*) val);
      break;
    default:
      if (cpyctor)
      {
        bool is_copy_assign = false;
        size_t size = type->_t_typesize;
        for (; destPosition != end; destPosition += size)
          cpyctor(destPosition, val, &is_copy_assign);
      }
      else
      {
        size_t size = type->_t_typesize;
        for (; destPosition != end; destPosition += size)
          cstl_memcpy(destPosition, val, size);
      }
      break;
  }
  return end;
}
void uninitialized_default_fill(forward_iterator_t* first, forward_iterator_t* last)
{
  assert(iterator_is_valid(first) && iterator_is_valid(last));
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
void uninitialized_fill(forward_iterator_t* first, forward_iterator_t* last, const void* value)
{
  assert(iterator_is_valid(first) && iterator_is_valid(last));
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(first);
  for (; !iterator_equal(first, last); iterator_next(first))
  {
    if (type->_t_typecopy)
    {
      bool ret = false;
      type->_t_typecopy(first->_t_pos, value, &ret);
      assert(ret);
    }
    else
    {
      cstl_memcpy(first->_t_pos, value, type->_t_typesize);
    }
  }
}

void uninitialized_copy(input_iterator_t* first, input_iterator_t* last, forward_iterator_t* result)
{
  assert(iterator_is_valid(first) && iterator_is_valid(last) && iterator_is_valid(result));
  assert(iterator_same_elem_type(first, last) && iterator_same_elem_type(first, result));

  switch (_ITERATOR_CONTAINER_TYPE(first)) {
    case _VECTOR_CONTAINER:
    case _DEQUE_CONTAINER:
    case _BASIC_STRING_CONTAINER:
      uninitialized_copy_from_continueous_to_any(first->_t_pos, last->_t_pos, result);
      break;
    case _LIST_CONTAINER:
      break;
    case _SLIST_CONTAINER:
      break;
    case _SET_CONTAINER:
      break;
    case _MULTISET_CONTAINER:
      break;
    case _MAP_CONTAINER:
      break;
    case _MULTIMAP_CONTAINER:
      break;
    case _HASH_SET_CONTAINER:
      break;
    case _HASH_MULTISET_CONTAINER:
      break;
    case _HASH_MAP_CONTAINER:
      break;
    case _HASH_MULTIMAP_CONTAINER:
      break;
    default:
      break;
  }
}
_byte_t* uninitialized_copy_from_any_to_continue(forward_iterator_t* from, forward_iterator_t* end, _byte_t* result)
{
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(from);
  size_t tsize = type->_t_typesize;
  switch (_ITERATOR_CONTAINER_TYPE(from)) {
    case _VECTOR_CONTAINER:
      if (type->_t_typecopy)
      {
        // this is the case uninitialized_copy_from_continoues_to_continoues,
        // but _t_typecopy not null, so have to copy on by one
        bool ret;
        _byte_t* bfrom = from->_t_pos;
        _byte_t* bend = end->_t_pos;
        for (; bfrom != bend; bfrom += tsize)
        {
          type->_t_typecopy(result, bfrom, &ret);
          result += tsize;
        }
      }
      else
      {
        // this is the case uninitialized_copy_from_continoues_to_continoues
        // and _t_typecopy null, so use memcpy
        cstl_memcpy(result, from->_t_pos, end->_t_pos - from->_t_pos);
        result += end->_t_pos - from->_t_pos;
      }
      break;
    case _DEQUE_CONTAINER:
      break;
    case _BASIC_STRING_CONTAINER:
      break;
    case _LIST_CONTAINER:
      break;
    case _SLIST_CONTAINER:
      break;
    case _SET_CONTAINER:
      break;
    case _MULTISET_CONTAINER:
      break;
    case _MAP_CONTAINER:
      break;
    case _MULTIMAP_CONTAINER:
      break;
    case _HASH_SET_CONTAINER:
      break;
    case _HASH_MULTISET_CONTAINER:
      break;
    case _HASH_MAP_CONTAINER:
      break;
    case _HASH_MULTIMAP_CONTAINER:
      break;
    default:
      break;
  }
  return result;
}
void uninitialized_copy_from_continueous_to_any(_byte_t* from, _byte_t* end, forward_iterator_t* result)
{
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(result);
  size_t tsize = type->_t_typesize;
  switch (_ITERATOR_CONTAINER_TYPE(result)) {
    case _VECTOR_CONTAINER:
      if (type->_t_typecopy)
      {
        // this is the case uninitialized_copy_from_continoues_to_continoues,
        // but _t_typecopy not null, so have to copy on by one
        bool ret = false;
        for (; from != end; from += tsize)
        {
          type->_t_typecopy(result->_t_pos, from, &ret);
          result->_t_pos += tsize;
        }
      }
      else
      {
        // this is the case uninitialized_copy_from_continoues_to_continoues
        // and _t_typecopy null, so use memcpy
        cstl_memcpy(result->_t_pos, from, end - from);
        result->_t_pos += end - from;
      }
      break;
    case _DEQUE_CONTAINER:
      break;
    case _BASIC_STRING_CONTAINER:
      break;
    case _LIST_CONTAINER:
      break;
    case _SLIST_CONTAINER:
      break;
    case _SET_CONTAINER:
      break;
    case _MULTISET_CONTAINER:
      break;
    case _MAP_CONTAINER:
      break;
    case _MULTIMAP_CONTAINER:
      break;
    case _HASH_SET_CONTAINER:
      break;
    case _HASH_MULTISET_CONTAINER:
      break;
    case _HASH_MAP_CONTAINER:
      break;
    case _HASH_MULTIMAP_CONTAINER:
      break;
    default:
      break;
  }
}
_byte_t* uninitialized_copy_from_continue_to_continue(type_t* type, _byte_t* from, _byte_t* end, _byte_t* result)
{
  size_t tsize = type->_t_typesize;
  bfun_t cpy = type->_t_typecopy;
  if (cpy)
  {
    // this is the case uninitialized_copy_from_continoues_to_continoues,
    // but _t_typecopy not null, so have to copy on by one
    bool is_opt_assign = false;
    for (; from != end; from += tsize)
    {
      cpy(result, from, &is_opt_assign);
      result += tsize;
    }
  }
  else
  {
    // this is the case uninitialized_copy_from_continoues_to_continoues
    // and _t_typecopy null, so use memcpy
    cstl_memcpy(result, from, end - from);
    result += end - from;
  }
  return result;
}
_byte_t* copy_from_continue_to_continue(type_t* type, _byte_t* from, _byte_t* end, _byte_t* result)
{
  size_t tsize = type->_t_typesize;
  bfun_t cpy = type->_t_typecopy;
  if (cpy)
  {
    // this is the case uninitialized_copy_from_continoues_to_continoues,
    // but _t_typecopy not null, so have to copy on by one
    bool is_opt_assign = true;
    for (; from != end; from += tsize)
    {
      cpy(result, from, &is_opt_assign);
      result += tsize;
    }
  }
  else
  {
    // this is the case uninitialized_copy_from_continoues_to_continoues
    // and _t_typecopy null, so use memcpy
    cstl_memcpy(result, from, end - from);
    result += end - from;
  }
  return result;
}
_byte_t* uninitialized_copy_from_continue_to_continue_destruct(type_t* type, _byte_t* from, _byte_t* end,
    _byte_t* result)
{
  size_t tsize = type->_t_typesize;
  bfun_t cpy = type->_t_typecopy;
  ufun_t dtor = type->_t_typedestroy;
  if (cpy)
  {
    // this is the case uninitialized_copy_from_continoues_to_continoues,
    // but _t_typecopy not null, so have to copy on by one
    bool is_copy_assign = false;
    if (dtor)
    {
      for (; from != end; from += tsize)
      {
        cpy(result, from, &is_copy_assign);
        dtor(from, &is_copy_assign);
        result += tsize;
      }
    }
    else
    {
      for (; from != end; from += tsize)
      {
        cpy(result, from, &is_copy_assign);
        result += tsize;
      }
    }
  }
  else
  {
    // this is the case uninitialized_copy_from_continoues_to_continoues
    // and _t_typecopy null, so use memcpy
    cstl_memcpy(result, from, end - from);
    result += end - from;
  }
  return result;
}
void uninitialized_copy_n(input_iterator_t* first, int n_step, forward_iterator_t* result)
{
  assert(iterator_is_valid(first) && iterator_is_valid(result));

  switch (_ITERATOR_CONTAINER_TYPE(first)) {
    case _VECTOR_CONTAINER:
    case _DEQUE_CONTAINER:
    case _BASIC_STRING_CONTAINER:
      uninitialized_copy_n_from_continoues_to_any(first->_t_pos, n_step, result);
      break;
    case _LIST_CONTAINER:
      break;
    case _SLIST_CONTAINER:
      break;
    case _SET_CONTAINER:
      break;
    case _MULTISET_CONTAINER:
      break;
    case _MAP_CONTAINER:
      break;
    case _MULTIMAP_CONTAINER:
      break;
    case _HASH_SET_CONTAINER:
      break;
    case _HASH_MULTISET_CONTAINER:
      break;
    case _HASH_MAP_CONTAINER:
      break;
    case _HASH_MULTIMAP_CONTAINER:
      break;
    default:
      break;
  }
}
void uninitialized_copy_n_from_continoues_to_any(_byte_t* from, size_t nstep, forward_iterator_t* result)
{
  // if result in [vec,deque,string], use memcpy for all element
  // else if no copyfunc, use memcpy for each element
  // else use copyfunc for each element
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(result);
  size_t tsize = type->_t_typesize;
  switch (_ITERATOR_CONTAINER_TYPE(result)) {
    case _VECTOR_CONTAINER:
      // if result in [vec,deque,string], use memcpy for all element
      if (type->_t_typecopy)
      {
        // this is the case uninitialized_copy_from_continoues_to_continoues,
        // but _t_typecopy not null, so have to copy on by one
        bool ret = false;
        _byte_t* end = from + nstep * tsize;
        for (; from != end; from += tsize)
        {
          type->_t_typecopy(result->_t_pos, from, &ret);
          result->_t_pos += tsize;
        }
      }
      else
      {
        // this is the case uninitialized_copy_from_continoues_to_continoues
        // and _t_typecopy null, so use memcpy
        nstep *= tsize;
        cstl_memcpy(result->_t_pos, from, nstep);
        result->_t_pos += nstep;
      }
      break;
    case _DEQUE_CONTAINER:
      break;
    case _BASIC_STRING_CONTAINER:
      break;
    case _LIST_CONTAINER:
      break;
    case _SLIST_CONTAINER:
      break;
    case _SET_CONTAINER:
      break;
    case _MULTISET_CONTAINER:
      break;
    case _MAP_CONTAINER:
      break;
    case _MULTIMAP_CONTAINER:
      break;
    case _HASH_SET_CONTAINER:
      break;
    case _HASH_MULTISET_CONTAINER:
      break;
    case _HASH_MAP_CONTAINER:
      break;
    case _HASH_MULTIMAP_CONTAINER:
      break;
    default:
      break;
  }
}

_byte_t* copy_from_any_to_continue(input_iterator_t* first, input_iterator_t* last, _byte_t* start, _byte_t* finish,
    _byte_t* end)
{
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(first);
  size_t tsize = type->_t_typesize;
  switch (_ITERATOR_CONTAINER_TYPE(first)) {
    case _VECTOR_CONTAINER:
    {
      copy_from_continue_to_continue(type, first->_t_pos, last->_t_pos, result);
    }
      break;
    case _DEQUE_CONTAINER:
      break;
    case _BASIC_STRING_CONTAINER:
      break;
    case _LIST_CONTAINER:
      break;
    case _SLIST_CONTAINER:
      break;
    case _SET_CONTAINER:
      break;
    case _MULTISET_CONTAINER:
      break;
    case _MAP_CONTAINER:
      break;
    case _MULTIMAP_CONTAINER:
      break;
    case _HASH_SET_CONTAINER:
      break;
    case _HASH_MULTISET_CONTAINER:
      break;
    case _HASH_MAP_CONTAINER:
      break;
    case _HASH_MULTIMAP_CONTAINER:
      break;
    default:
      break;
  }
  return dest;
}

_byte_t* uninitialized_copy_n_from_any_to_continue(forward_iterator_t* from, size_t elesize, _byte_t* result)
{
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(from);
  size_t tsize = type->_t_typesize;
  switch (_ITERATOR_CONTAINER_TYPE(from)) {
    case _VECTOR_CONTAINER:
      result = copy_n_from_continue_to_continue(type, from, elesize, result);
      break;
    case _DEQUE_CONTAINER:
      break;
    case _BASIC_STRING_CONTAINER:
      break;
    case _LIST_CONTAINER:
      break;
    case _SLIST_CONTAINER:
      break;
    case _SET_CONTAINER:
      break;
    case _MULTISET_CONTAINER:
      break;
    case _MAP_CONTAINER:
      break;
    case _MULTIMAP_CONTAINER:
      break;
    case _HASH_SET_CONTAINER:
      break;
    case _HASH_MULTISET_CONTAINER:
      break;
    case _HASH_MAP_CONTAINER:
      break;
    case _HASH_MULTIMAP_CONTAINER:
      break;
    default:
      break;
  }
  return result;
}
_byte_t* copy_n_from_continue_to_continue(type_t* type, _byte_t* from, size_t elesize, _byte_t* result)
{

  size_t tsize = type->_t_typesize;
  bfun_t cpy = type->_t_typecopy;
  _byte_t* end = from + tsize * elesize;
  if (cpy)
  {
    // this is the case uninitialized_copy_from_continoues_to_continoues,
    // but _t_typecopy not null, so have to copy on by one
    bool is_opt_assign = true;
    for (; from != end; from += tsize)
    {
      cpy(result, from, &is_opt_assign);
      result += tsize;
    }
  }
  else
  {
    // this is the case uninitialized_copy_from_continoues_to_continoues
    // and _t_typecopy null, so use memcpy
    cstl_memcpy(result, from, end - from);
    result += end - from;
  }
  return result;
}
void fill_n(output_iterator_t* from, size_t n, void* val)
{
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(from);
  switch (_ITERATOR_CONTAINER_TYPE(from)) {
    case _VECTOR_CONTAINER:
      from->_t_pos = fill_n_continue(type, from->_t_pos, n, val);
      break;
    case _DEQUE_CONTAINER:
      break;
    case _BASIC_STRING_CONTAINER:
      break;
    case _LIST_CONTAINER:
      break;
    case _SLIST_CONTAINER:
      break;
    case _SET_CONTAINER:
      break;
    case _MULTISET_CONTAINER:
      break;
    case _MAP_CONTAINER:
      break;
    case _MULTIMAP_CONTAINER:
      break;
    case _HASH_SET_CONTAINER:
      break;
    case _HASH_MULTISET_CONTAINER:
      break;
    case _HASH_MAP_CONTAINER:
      break;
    case _HASH_MULTIMAP_CONTAINER:
      break;
    default:
      break;
  }
}

_byte_t* fill_n_continue(type_t* type, _byte_t* destPosition, size_t n, void* val)
{
  bfun_t cpyctor = type->_t_typecopy;
  _byte_t* e = destPosition + type->_t_typesize * n;
  switch (type->_t_typeid) {
    case cstl_int8:
      fill_n_char((char*) destPosition, n, *(char*) val);
      break;
    case cstl_uint8:
      fill_n_uchar((unsigned char*) destPosition, n, *(unsigned char*) val);
      break;
    case cstl_int16:
      fill_n_int16((int16_t*) destPosition, n, *(int16_t*) val);
      break;
    case cstl_uint16:
      fill_n_uint16((uint16_t*) destPosition, n, *(uint16_t*) val);
      break;
    case cstl_int32:
      fill_n_int32((int32_t*) destPosition, n, *(int32_t*) val);
      break;
    case cstl_uint32:
      fill_n_uint32((uint32_t*) destPosition, n, *(uint32_t*) val);
      break;
    case cstl_int64:
      fill_n_int64((int64_t*) destPosition, n, *(int64_t*) val);
      break;
    case cstl_uint64:
      fill_n_uint64((uint64_t*) destPosition, n, *(uint64_t*) val);
      break;
    case cstl_void_pt:
      fill_n_uint64((uint64_t*) destPosition, n, *(uint64_t*) val);
      break;
    default:
      if (cpyctor)
      { // heap-allocation inside this struct
        bool is_copy_assign = true;
        size_t tsize = type->_t_typesize;
        for (; destPosition != e; destPosition += tsize)
          cpyctor(destPosition, val, &is_copy_assign);
      }
      else
      { // pod struct
        size_t tsize = type->_t_typesize;
        for (; destPosition != e; destPosition += tsize)
          cstl_memcpy(destPosition, val, tsize);
      }
      break;
  }
  return e;
}
char* fill_n_char(char* first, size_t n, char c)
{
  return (char*) memset(first, (char) c, n) + n;
}

unsigned char* fill_n_uchar(unsigned char* first, size_t n, unsigned char c)
{
  return (unsigned char*) memset(first, (unsigned char) c, n) + n;
}

#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__ICL) // ICL = Intel compiler
bool* fill_n_bool(bool* first, size_t n, bool b)
{
  return (bool*)memset(first, (char)b, n) + n;
}
#endif

#if(defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG)) && (defined(EA_PROCESSOR_X86) || defined(EA_PROCESSOR_X86_64))
#if defined(EA_PROCESSOR_X86_64)
uint64_t* fill_n_uint64(uint64_t* first, size_t n, uint64_t c)
{
  uintptr_t count = (uintptr_t) (n);
  uint64_t value = (uint64_t) (c);
  __asm__ __volatile__ ("cld\n\t"
      "rep stosq\n\t"
      : "+c" (count), "+D" (first), "=m" (first)
      : "a" (value)
      : "cc" );
  return first; // first is updated by the code above.
}
int64_t* fill_n_int64(int64_t* first, size_t n, int64_t c)
{
  uintptr_t count = (uintptr_t) (n);
  int64_t value = (int64_t) (c);
  __asm__ __volatile__ ("cld\n\t"
      "rep stosq\n\t"
      : "+c" (count), "+D" (first), "=m" (first)
      : "a" (value)
      : "cc" );
  return first; // first is updated by the code above.
}
#endif  // #if defined(EA_PROCESSOR_X86_64)
uint32_t* fill_n_uint32(uint32_t* first, size_t n, uint32_t c)
{
  uintptr_t count = (uintptr_t) (n);
  uint32_t value = (uint32_t) (c);
  __asm__ __volatile__ ("cld\n\t"
      "rep stosl\n\t"
      : "+c" (count), "+D" (first), "=m" (first)
      : "a" (value)
      : "cc" );
  return first; // first is updated by the code above.
}
int32_t* fill_n_int32(int32_t* first, size_t n, int32_t c)
{
  uintptr_t count = (uintptr_t) (n);
  int32_t value = (int32_t) (c);
  __asm__ __volatile__ ("cld\n\t"
      "rep stosl\n\t"
      : "+c" (count), "+D" (first), "=m" (first)
      : "a" (value)
      : "cc" );
  return first; // first is updated by the code above.
}
uint16_t* fill_n_uint16(uint16_t* first, size_t n, uint16_t c)
{
  uintptr_t count = (uintptr_t) (n);
  uint16_t value = (uint16_t) (c);
  __asm__ __volatile__ ("cld\n\t"
      "rep stosw\n\t"
      : "+c" (count), "+D" (first), "=m" (first)
      : "a" (value)
      : "cc" );
  return first; // first is updated by the code above.
}
int16_t* fill_n_int16(int16_t* first, size_t n, int16_t c)
{
  uintptr_t count = (uintptr_t) (n);
  int16_t value = (int16_t) (c);
  __asm__ __volatile__ ("cld\n\t"
      "rep stosw\n\t"
      : "+c" (count), "+D" (first), "=m" (first)
      : "a" (value)
      : "cc" );
  return first; // first is updated by the code above.
}
#elif defined(EA_COMPILER_MICROSOFT) && (defined(EA_PROCESSOR_X86) || defined(EA_PROCESSOR_X86_64))
#if defined(EA_PROCESSOR_X86_64)
uint64_t* fill_n_uint64(uint64_t* first, size_t n, uint64_t c)
{
  __stosq(first, (uint64_t)c, n);
  return first + n;
}
int64_t* fill_n_int64(int64_t* first, size_t n, int64_t c)
{
  __stosq((uint64_t*)first, (uint64_t)c, n);
  return first + n;
}
#endif
uint32_t* fill_n_uint32(uint32_t* first, size_t n, uint32_t c)
{
  __stosd((unsigned long*)first, (unsigned long)c, (size_t)n);
  return first + n;
}
int32_t* fill_int32(int32_t* first, size_t n, int32_t c)
{
  __stosd((unsigned long*)first, (unsigned long)c, (size_t)n);
  return first + n;
}
uint16_t* fill_n_uint16(uint16_t* first, size_t n, uint16_t c)
{
  __stosw(first, (uint16_t)c, (size_t)n);
  return first + n;
}
int16_t* fill_n_int16(int16_t* first, size_t n, int16_t c)
{
  __stosw((uint16_t*)first, (uint16_t)c, (size_t)n);
  return first + n;
}
#endif

void fill_continue(type_t* type, _byte_t* first, _byte_t* e, void* val)
{
  bfun_t cpyctor = type->_t_typecopy;
  switch (type->_t_typeid) {
    case cstl_int8:
      fill_char((char*) first, e, *(char*) val);
      break;
    case cstl_uint8:
      fill_uchar((unsigned char*) first, e, *(unsigned char*) val);
      break;
    case cstl_int16:
      fill_int16((int16_t*) first, e, *(int16_t*) val);
      break;
    case cstl_uint16:
      fill_n_uint16((uint16_t*) first, e, *(uint16_t*) val);
      break;
    case cstl_int32:
      fill_n_int32((int32_t*) first, e, *(int32_t*) val);
      break;
    case cstl_uint32:
      fill_n_uint32((uint32_t*) first, e, *(uint32_t*) val);
      break;
    case cstl_int64:
      fill_n_int64((int64_t*) first, e, *(int64_t*) val);
      break;
    case cstl_uint64:
      fill_n_uint64((uint64_t*) first, e, *(uint64_t*) val);
      break;
    case cstl_void_pt:
      fill_n_uint64((uint64_t*) first, e, *(uint64_t*) val);
      break;
    default:
      if (cpyctor)
      { // heap-allocation inside this struct
        bool is_copy_assign = true;
        size_t tsize = type->_t_typesize;
        for (; first != e; first += tsize)
          cpyctor(first, val, &is_copy_assign);
      }
      else
      { // pod struct
        size_t tsize = type->_t_typesize;
        for (; first != e; first += tsize)
          cstl_memcpy(first, val, tsize);
      }
      break;
  }
}
void fill_char(char* first, char* last, char c) // It's debateable whether we should use 'char& c' or 'char c' here.
{
  memset(first, (unsigned char) c, last - first);
}
void fill_uchar(unsigned char* first, unsigned char* last, unsigned char c)
{
  memset(first, (unsigned char) c, last - first);
}
#if(defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG)) && (defined(EA_PROCESSOR_X86) || defined(EA_PROCESSOR_X86_64))
#if defined(EA_PROCESSOR_X86_64)
void fill_uint64(uint64_t* first, uint64_t* last, uint64_t c)
{
  uintptr_t count = (uintptr_t) (last - first);
  uint64_t value = (uint64_t) (c);
  __asm__ __volatile__ ("cld\n\t"
      "rep stosq\n\t"
      : "+c" (count), "+D" (first), "=m" (first)
      : "a" (value)
      : "cc" );
}
void fill_int64(int64_t* first, int64_t* last, int64_t c)
{
  uintptr_t count = (uintptr_t) (last - first);
  int64_t value = (int64_t) (c);
  __asm__ __volatile__ ("cld\n\t"
      "rep stosq\n\t"
      : "+c" (count), "+D" (first), "=m" (first)
      : "a" (value)
      : "cc" );
}
#endif
void fill_uint32(uint32_t* first, uint32_t* last, uint32_t c)
{
  uintptr_t count = (uintptr_t) (last - first);
  uint32_t value = (uint32_t) (c);
  __asm__ __volatile__ ("cld\n\t"
      "rep stosl\n\t"
      : "+c" (count), "+D" (first), "=m" (first)
      : "a" (value)
      : "cc" );
}
void fill_int32(int32_t* first, int32_t* last, int32_t c)
{
  uintptr_t count = (uintptr_t) (last - first);
  int32_t value = (int32_t) (c);
  __asm__ __volatile__ ("cld\n\t"
      "rep stosl\n\t"
      : "+c" (count), "+D" (first), "=m" (first)
      : "a" (value)
      : "cc" );
}
void fill_uint16(uint16_t* first, uint16_t* last, uint16_t c)
{
  uintptr_t count = (uintptr_t) (last - first);
  uint16_t value = (uint16_t) (c);
  __asm__ __volatile__ ("cld\n\t"
      "rep stosw\n\t"
      : "+c" (count), "+D" (first), "=m" (first)
      : "a" (value)
      : "cc" );
}
void fill_int16(int16_t* first, int16_t* last, int16_t c)
{
  uintptr_t count = (uintptr_t) (last - first);
  int16_t value = (int16_t) (c);
  __asm__ __volatile__ ("cld\n\t"
      "rep stosw\n\t"
      : "+c" (count), "+D" (first), "=m" (first)
      : "a" (value)
      : "cc" );
}
#elif defined(EA_COMPILER_MICROSOFT) && (defined(EA_PROCESSOR_X86) || defined(EA_PROCESSOR_X86_64))
#if defined(EA_PROCESSOR_X86_64)
void fill_uint64(uint64_t* first, uint64_t* last, uint64_t c)
{
  __stosq(first, (uint64_t)c, (size_t)(last - first));
}
oid fill_int64(int64_t* first, int64_t* last, int64_t c)
{
  __stosq((uint64_t*)first, (uint64_t)c, (size_t)(last - first));
}
#endif
void fill_uint32(uint32_t* first, uint32_t* last, uint32_t c)
{
  __stosd((unsigned long*)first, (unsigned long)c, (size_t)(last - first));
}
void fill_int32(int32_t* first, int32_t* last, int32_t c)
{
  __stosd((unsigned long*)first, (unsigned long)c, (size_t)(last - first));
}
void fill_uint16(uint16_t* first, uint16_t* last, uint16_t c)
{
  __stosw(first, (uint16_t)c, (size_t)(last - first));
}
void fill_int16(int16_t* first, int16_t* last, int16_t c)
{
  __stosw((uint16_t*)first, (uint16_t)c, (size_t)(last - first));
}
#endif

#ifdef _MSC_VER
#pragma warning(pop)
#endif
