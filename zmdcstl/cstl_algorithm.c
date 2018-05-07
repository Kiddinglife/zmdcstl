#include "cstl_algorithm.h"
#include "cstl_iterator.h"

bool cstl_equal(input_iterator_t* first1, input_iterator_t* last1, input_iterator_t* first2)
{
  assert(iterator_is_valid(first1) && iterator_is_valid(last1) && iterator_is_valid(first2));
  assert(iterator_same_elem_type(first1, last1) && iterator_same_elem_type(first1, first2));
  _byte_t *d, *s;
  char ret;
  iterator_pre_t from_next = _ITERATOR_META_TYPE(first1)->_t_iterator_funs->iterator_next;
  iterator_dref_t from_dref = _ITERATOR_META_TYPE(first1)->_t_iterator_funs->iterator_dref;
  iterator_equal_t frome_equal = _ITERATOR_META_TYPE(first1)->_t_iterator_funs->iterator_equal;
  iterator_pre_t dest_next = _ITERATOR_META_TYPE(first2)->_t_iterator_funs->iterator_next;
  iterator_dref_t dest_dref = _ITERATOR_META_TYPE(first2)->_t_iterator_funs->iterator_dref;
  bfun_t less = _ITERATOR_TYPE_INFO_TYPE(first2)->_t_typeless;
  for (; !frome_equal(first1, last1); from_next(first1), dest_next(first2))
  {
    s = from_dref(first1);
    d = dest_dref(first2);
    less(s, d, &ret);
    if (ret != 0)
      return false;
  }
  return true;
}

void cstl_move_backward(bidirectional_iterator_t* first, bidirectional_iterator_t* last,
    bidirectional_iterator_t* dlast)
{
  assert(iterator_is_valid(first) && iterator_is_valid(last) && iterator_is_valid(dlast));
  assert(iterator_same_elem_type(first, last) && iterator_same_elem_type(last, dlast));
  _byte_t *d, *s;
  iterator_pre_t from_pre = _ITERATOR_META_TYPE(first)->_t_iterator_funs->iterator_pre;
  iterator_dref_t from_dref = _ITERATOR_META_TYPE(first)->_t_iterator_funs->iterator_dref;
  iterator_equal_t frome_equal = _ITERATOR_META_TYPE(dlast)->_t_iterator_funs->iterator_equal;
  iterator_pre_t dest_pre = _ITERATOR_META_TYPE(dlast)->_t_iterator_funs->iterator_pre;
  size_t tsize = _ITERATOR_TYPE_INFO_TYPE(dlast)->_t_typesize;
  while (!frome_equal(first, last))
  {
    from_pre(last);
    dest_pre(dlast);
    s = from_dref(first);
    d = from_dref(dlast);
    memcpy(d, s, tsize);
  }
}

void cstl_move(input_iterator_t* first, input_iterator_t* last, output_iterator_t* dlast)
{
  assert(iterator_is_valid(first) && iterator_is_valid(last) && iterator_is_valid(dlast));
  assert(iterator_same_elem_type(first, last) && iterator_same_elem_type(last, dlast));
  _byte_t *d, *s;
  iterator_next_t from_next = _ITERATOR_META_TYPE(first)->_t_iterator_funs->iterator_next;
  iterator_dref_t from_dref = _ITERATOR_META_TYPE(first)->_t_iterator_funs->iterator_dref;
  iterator_equal_t frome_equal = _ITERATOR_META_TYPE(dlast)->_t_iterator_funs->iterator_equal;
  iterator_next_t dest_next = _ITERATOR_META_TYPE(dlast)->_t_iterator_funs->iterator_next;
  size_t tsize = _ITERATOR_TYPE_INFO_TYPE(dlast)->_t_typesize;
  while (!frome_equal(first, last))
  {
    dest_next(dlast);
    from_next(first);
    s = from_dref(first);
    d = from_dref(dlast);
    memcpy(d, s, tsize);
  }
}

