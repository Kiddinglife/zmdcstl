#include "cstl_algorithm.h"
#include "cstl_iterator.h"

#define  equal_from_continus_aux(next)\
for (; first1 != last1; first1 += tsize)\
{\
  type->_t_typeless(first1, first2, &ret);\
  if (ret != 0)\
    return false;\
  next;\
}

bool equal_from_continus(_byte_t* first1, _byte_t* last1, input_iterator_t* first2)
{
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(first2);
  size_t tsize = type->_t_typesize;
  typeid_t tid = type->_t_typeid;
  char ret;
  switch (_ITERATOR_CONTAINER_TYPE(first2))
  {
  case _VECTOR_CONTAINER:
  case _DEQUE_CONTAINER:
  case _BASIC_STRING_CONTAINER:
    //equal_from_continus_aux(first2->_t_pos += tsize)
    for (; first1 != last1; first1 += tsize)
    {
      type->_t_typeless(first1, first2->_t_pos, &ret);
      if (ret != 0)
        return false;
      first2->_t_pos += tsize;
    }
    break;
  case _LIST_CONTAINER:
    equal_from_continus_aux(/*list_next*/)
    break;
  case _SLIST_CONTAINER:
    equal_from_continus_aux(/*list_next*/)
    break;
  case _SET_CONTAINER:
    equal_from_continus_aux(/*list_next*/)
    break;
  case _MULTISET_CONTAINER:
    equal_from_continus_aux(/*list_next*/)
    break;
  case _MAP_CONTAINER:
    equal_from_continus_aux(/*list_next*/)
    break;
  case _MULTIMAP_CONTAINER:
    equal_from_continus_aux(/*list_next*/)
    break;
  case _HASH_SET_CONTAINER:
    equal_from_continus_aux(/*list_next*/)
    break;
  case _HASH_MULTISET_CONTAINER:
    equal_from_continus_aux(/*list_next*/)
    break;
  case _HASH_MAP_CONTAINER:
    equal_from_continus_aux(/*list_next*/)
    break;
  case _HASH_MULTIMAP_CONTAINER:
    equal_from_continus_aux(/*list_next*/)
    break;
  default:
    break;
  }
  return true;
}

bool equal(input_iterator_t* first1, input_iterator_t* last1, input_iterator_t* first2)
{
  assert(iterator_is_valid(first1) && iterator_is_valid(last1) && iterator_is_valid(first2));
  assert(
      iterator_limit_type(first1, _INPUT_ITERATOR) && iterator_limit_type(last1, _INPUT_ITERATOR)
          && iterator_limit_type(first2, _FORWARD_ITERATOR));
  assert(iterator_same_elem_type(first1, last1) && iterator_same_elem_type(first1, first2));

  switch (_ITERATOR_CONTAINER_TYPE(first1))
  {
  case _VECTOR_CONTAINER:
  case _DEQUE_CONTAINER:
  case _BASIC_STRING_CONTAINER:
    equal_from_continus(first1->_t_pos, last1->_t_pos, first2);
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

  return true;
}

