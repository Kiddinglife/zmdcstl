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
  switch (_ITERATOR_CONTAINER_TYPE(first2)) {
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
  assert(iterator_same_elem_type(first1, last1) && iterator_same_elem_type(first1, first2));

  switch (_ITERATOR_CONTAINER_TYPE(first1)) {
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

void cstl_move_backward_from_continue_to_any(_byte_t* first, _byte_t* last, bidirectional_iterator_t* dlast)
{
  assert(iterator_is_valid(dlast));

  switch (_ITERATOR_CONTAINER_TYPE(dlast)) {
    case _VECTOR_CONTAINER:
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

void cstl_move_backward(bidirectional_iterator_t* first, bidirectional_iterator_t* last,
    bidirectional_iterator_t* dlast)
{
  assert(iterator_is_valid(first) && iterator_is_valid(last) && iterator_is_valid(dlast));
  assert(iterator_same_elem_type(first, last) && iterator_same_elem_type(last, dlast));

  _byte_t *d, *s;
  iterator_pre_t from_pre = _ITERATOR_META_TYPE(first)->iterator_pre;
  iterator_dref_t from_dref = _ITERATOR_META_TYPE(first)->iterator_dref;
  iterator_equal_t frome_equal = _ITERATOR_META_TYPE(dlast)->iterator_equal;
  iterator_pre_t dest_pre = _ITERATOR_META_TYPE(dlast)->iterator_pre;
  size_t tsize = _ITERATOR_TYPE_INFO_TYPE(dlast)->_t_typesize;

  while (!frome_equal(first, last))
  {
    from_pre(last);
    dest_pre(dlast);
    s = from_dref(first);
    d = from_dref(dlast);
    cstl_memcpy(d, s, tsize);
  }
}

void cstl_move(input_iterator_t* first, input_iterator_t* last, output_iterator_t* dlast)
{
  assert(iterator_is_valid(first) && iterator_is_valid(last) && iterator_is_valid(dlast));
  assert(iterator_same_elem_type(first, last) && iterator_same_elem_type(last, dlast));

  _byte_t *d, *s;
  iterator_next_t from_next = _ITERATOR_META_TYPE(first)->iterator_next;
  iterator_dref_t from_dref = _ITERATOR_META_TYPE(first)->iterator_dref;
  iterator_equal_t frome_equal = _ITERATOR_META_TYPE(dlast)->iterator_equal;
  iterator_next_t dest_next = _ITERATOR_META_TYPE(dlast)->iterator_next;
  size_t tsize = _ITERATOR_TYPE_INFO_TYPE(dlast)->_t_typesize;

  while (!frome_equal(first, last))
  {
    dest_next(dlast);
    from_next(first);
    s = from_dref(first);
    d = from_dref(dlast);
    cstl_memcpy(d, s, tsize);
  }
}

