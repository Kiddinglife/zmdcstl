/*
 * cstl_iterator.c
 *
 *  Created on: 7 Mar. 2018
 *      Author: jackiez
 */

#include "cstl_iterator.h"
#include "cstl_vector.h"

bool iterator_limit_type(iterator_t* it_iter, iteratortype_t t_limittype)
{
  assert(iterator_is_valid(it_iter));
  switch (t_limittype)
  {
  case _INPUT_ITERATOR:
    if (it_iter->hdr->_t_iteratortype >= _INPUT_ITERATOR)
      return true;
    break;
  case _OUTPUT_ITERATOR:
    if (it_iter->hdr->_t_iteratortype >= _OUTPUT_ITERATOR)
      return true;
    break;
  case _FORWARD_ITERATOR:
    if (it_iter->hdr->_t_iteratortype >= _FORWARD_ITERATOR)
      return true;
    break;
  case _BIDIRECTIONAL_ITERATOR:
    if (it_iter->hdr->_t_iteratortype >= _BIDIRECTIONAL_ITERATOR)
      return true;
    break;
  case _RANDOM_ACCESS_ITERATOR:
    if (it_iter->hdr->_t_iteratortype >= _RANDOM_ACCESS_ITERATOR)
      return true;
    break;
  default:
    assert(false);
    break;
  }
  return false;
}

/**
 * Test iterator referenced data is within the vector.
 */
static bool vector_iterator_belong_to_vector(const vector_t* cpvec_vector, iterator_t it_iter)
{
//  assert(cpvec_vector != NULL);
//  assert(vector_is_inited(cpvec_vector));
//  assert(_VECTOR_ITERATOR_ITERATOR_TYPE(it_iter) == _RANDOM_ACCESS_ITERATOR);
//  assert(_VECTOR_ITERATOR_CONTAINER_TYPE(it_iter) == _VECTOR_CONTAINER);
//  assert(_VECTOR_ITERATOR_CONTAINER(it_iter) == cpvec_vector);
//
//  if (_VECTOR_ITERATOR_COREPOS(it_iter) >= cpvec_vector->_pby_start &&
//  _VECTOR_ITERATOR_COREPOS(it_iter) <= cpvec_vector->_pby_finish)
//  {
//    return true;
//  }
//  else
//  {
//    return false;
//  }
  return true;
}

static iterator_t* vector_iterator_get_pointer_ignore_cstr(iterator_t* it_iter)
{
  return NULL;
}

const void* iterator_get_pointer_ignore_cstr(iterator_t* it_iter)
{
  assert(iterator_is_valid(it_iter));
  assert(iterator_limit_type(it_iter, _INPUT_ITERATOR));

  switch (it_iter->hdr->_t_containertype)
  {
  case _VECTOR_CONTAINER:
    return vector_iterator_get_pointer_ignore_cstr(it_iter);
    break;
//  case _LIST_CONTAINER:
//    return list_iterator_get_pointer_ignore_cstr(it_iter);
//    break;
//  case _DEQUE_CONTAINER:
//    return deque_iterator_get_pointer_ignore_cstr(it_iter);
//    break;
//  case _SLIST_CONTAINER:
//    return slist_iterator_get_pointer_ignore_cstr(it_iter);
//    break;
//  case _SET_CONTAINER:
//    return set_iterator_get_pointer_ignore_cstr(it_iter);
//    break;
//  case _MULTISET_CONTAINER:
//    return multiset_iterator_get_pointer_ignore_cstr(it_iter);
//    break;
//  case _MAP_CONTAINER:
//    return map_iterator_get_pointer_ignore_cstr(it_iter);
//    break;
//  case _MULTIMAP_CONTAINER:
//    return multimap_iterator_get_pointer_ignore_cstr(it_iter);
//    break;
//  case _HASH_SET_CONTAINER:
//    return hash_set_iterator_get_pointer_ignore_cstr(it_iter);
//    break;
//  case _HASH_MULTISET_CONTAINER:
//    return hash_multiset_iterator_get_pointer_ignore_cstr(it_iter);
//    break;
//  case _HASH_MAP_CONTAINER:
//    return hash_map_iterator_get_pointer_ignore_cstr(it_iter);
//    break;
//  case _HASH_MULTIMAP_CONTAINER:
//    return hash_multimap_iterator_get_pointer_ignore_cstr(it_iter);
//    break;
//  case _BASIC_STRING_CONTAINER:
//    return basic_string_iterator_get_pointer_ignore_cstr(it_iter);
//    break;
  default:
    assert(false);
    return NULL;
    break;
  }
}

void iterator_next(iterator_t* it_iter)
{
  assert(iterator_is_valid(it_iter));
  switch (it_iter->hdr->_t_containertype)
  {
  case _VECTOR_CONTAINER:
    vector_iterator_next(it_iter);
    break;
  case _LIST_CONTAINER:
    //_list_iterator_next(it_iter);
    break;
  case _DEQUE_CONTAINER:
    //_deque_iterator_next(it_iter);
    break;
  case _SLIST_CONTAINER:
    //_slist_iterator_next(it_iter);
    break;
  case _SET_CONTAINER:
    //_set_iterator_next(it_iter);
    break;
  case _MULTISET_CONTAINER:
    //_multiset_iterator_next(it_iter);
    break;
  case _MAP_CONTAINER:
    //_map_iterator_next(it_iter);
    break;
  case _MULTIMAP_CONTAINER:
    //_multimap_iterator_next(it_iter);
    break;
  case _HASH_SET_CONTAINER:
    //_hash_set_iterator_next(it_iter);
    break;
  case _HASH_MULTISET_CONTAINER:
    //_hash_multiset_iterator_next(it_iter);
    break;
  case _HASH_MAP_CONTAINER:
    //_hash_map_iterator_next(it_iter);
    break;
  case _HASH_MULTIMAP_CONTAINER:
    //_hash_multimap_iterator_next(it_iter);
    break;
  case _BASIC_STRING_CONTAINER:
    //_basic_string_iterator_next(it_iter);
    break;
  default:
    assert(false);
    break;
  }
}
