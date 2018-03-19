#include "cstl_vector.h"
#include "cstl_types.h"
#include "cstl_memory.h"
#include "cstl_alloc.h"

bool vector_is_inited(const vector_t* cpvec_vector)
{
  if (cpvec_vector == NULL)
    return false;
  if (_GET_VECTOR_TYPE_INFO_TYPE(cpvec_vector) == NULL)
    return false;
  if (cpvec_vector->_pby_start == NULL && cpvec_vector->_pby_finish == NULL && cpvec_vector->_pby_endofstorage == NULL)
    return true;
  if (cpvec_vector->_pby_start != NULL && cpvec_vector->_pby_finish != NULL && cpvec_vector->_pby_endofstorage != NULL
      && cpvec_vector->_pby_finish >= cpvec_vector->_pby_start
      && cpvec_vector->_pby_endofstorage > cpvec_vector->_pby_start
      && cpvec_vector->_pby_endofstorage >= cpvec_vector->_pby_finish)
    return true;
  return false;
}

bool vector_iterator_valid(const vector_t* cpvec_vector, vector_iterator_t* it_iter)
{
  bool b1 = vector_is_inited(cpvec_vector) &&
  _VECTOR_ITERATOR_ITERATOR_TYPE(it_iter) == _RANDOM_ACCESS_ITERATOR &&
  _VECTOR_ITERATOR_CONTAINER_TYPE(it_iter) == _VECTOR_CONTAINER &&
  _VECTOR_ITERATOR_CONTAINER(it_iter) == cpvec_vector &&
  _VECTOR_ITERATOR_COREPOS(it_iter) >= cpvec_vector->_pby_start;

  bool b2;
  if (cpvec_vector->_pby_finish != cpvec_vector->_pby_start)
  {
    // there is ele now in vector so _pby_finish != _pby_start, must comepare with _pby_finish
    b2 = _VECTOR_ITERATOR_COREPOS(it_iter) < cpvec_vector->_pby_finish;
  }
  else
  {
    // no ele now in vector so _pby_finish = _pby_start, must comepare with _pby_endofstorage
    b2 = _VECTOR_ITERATOR_COREPOS(it_iter) <= cpvec_vector->_pby_endofstorage;
  }
  return b1 && b2;
}

/**
 * Get the iterator that reference next data.
 */
void vector_iterator_next(vector_iterator_t* it_iter)
{
  assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_iter), it_iter));
  _VECTOR_ITERATOR_COREPOS(it_iter) += _GET_VECTOR_TYPE_SIZE(_VECTOR_ITERATOR_CONTAINER(it_iter));
  assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_iter), it_iter));
}

void vector_end(const vector_t* cpvec_vector, vector_iterator_t* it_end)
{
  assert(cpvec_vector != NULL);
  assert(vector_is_inited(cpvec_vector));
  _VECTOR_ITERATOR_CONTAINER_TYPE(it_end) = _VECTOR_CONTAINER;
  _VECTOR_ITERATOR_ITERATOR_TYPE(it_end) = _RANDOM_ACCESS_ITERATOR;
  _ITERATOR_CONTAINER(it_end) = (vector_t*) cpvec_vector;
  _VECTOR_ITERATOR_COREPOS(it_end) = cpvec_vector->_pby_finish;
}

void vector_end_again(vector_iterator_t* it_end)
{
  assert(it_end != NULL);
  assert((vector_t*)it_end->_pt_container != NULL);
  assert(vector_is_inited((vector_t* )it_end->_pt_container));
  _VECTOR_ITERATOR_COREPOS(it_end) = ((vector_t*) it_end->_pt_container)->_pby_finish;
}

bool vector_iterator_equal(vector_iterator_t* it_first, vector_iterator_t* it_second)
{
  assert(iterator_same_type(it_first, it_second));
  assert(_VECTOR_ITERATOR_CONTAINER(it_first) == _VECTOR_ITERATOR_CONTAINER(it_second));
  assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_first), it_first));
  assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_second), it_second));
  return _VECTOR_ITERATOR_COREPOS(it_first) == _VECTOR_ITERATOR_COREPOS(it_second);
}

void vector_iterator_get_value(vector_iterator_t* it_iter, void* pv_value)
{
  assert(pv_value != NULL);
  assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_iter), it_iter));
  assert((void*)it_iter->_t_pos != _VECTOR_ITERATOR_CONTAINER(it_iter)->_pby_finish);
  size_t size = 0;
  //if (_VECTOR_ITERATOR_CONTAINER(it_iter)->_t_typeinfo._pt_type->_t_typeid == cstr)
  //{
  // @TODO
  //}
  //else
  {
    size = _GET_VECTOR_TYPE_SIZE(_VECTOR_ITERATOR_CONTAINER(it_iter));
    _GET_VECTOR_TYPE_COPY_FUNCTION(_VECTOR_ITERATOR_CONTAINER(it_iter))(pv_value, _VECTOR_ITERATOR_COREPOS(it_iter),
        &size);
    assert(size);
  }
}

bool vector_iterator_less(vector_iterator_t* it_first, vector_iterator_t* it_second)
{
  assert(iterator_same_type(it_first, it_second));
  assert(_VECTOR_ITERATOR_CONTAINER(it_first) == _VECTOR_ITERATOR_CONTAINER(it_second));
  assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_first), it_first));
  assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_second), it_second));
  return _VECTOR_ITERATOR_COREPOS(it_first) < _VECTOR_ITERATOR_COREPOS(it_second);
}

bool vector_iterator_before(vector_iterator_t* it_first, vector_iterator_t* it_second)
{
  return vector_iterator_less(it_first, it_second);
}

void vector_iterator_set_value(vector_iterator_t* it_iter, const void* cpv_value)
{
  bool b_result = false;

  assert(cpv_value != NULL);
  assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_iter), it_iter));
  assert((_byte_t*)it_iter->_t_pos < _VECTOR_ITERATOR_CONTAINER(it_iter)->_pby_finish);

  /* char* */
  // @TODO
  //if (strncmp(_GET_VECTOR_TYPE_BASENAME(_VECTOR_ITERATOR_CONTAINER(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
  //    string_assign_cstr((string_t*)_VECTOR_ITERATOR_COREPOS(it_iter), (char*)cpv_value);
  //}
  //else
  //{
  b_result = _GET_VECTOR_TYPE_SIZE(_VECTOR_ITERATOR_CONTAINER(it_iter));
  _GET_VECTOR_TYPE_COPY_FUNCTION(_VECTOR_ITERATOR_CONTAINER(it_iter))(_VECTOR_ITERATOR_COREPOS(it_iter), cpv_value,
      &b_result);
  assert(b_result);
  //}
}

void vector_iterator_prev(vector_iterator_t* it_iter)
{
  assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_iter), it_iter));
  _VECTOR_ITERATOR_COREPOS(it_iter) -= _GET_VECTOR_TYPE_SIZE(_VECTOR_ITERATOR_CONTAINER(it_iter));
  assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_iter), it_iter));
}

void vector_iterator_next_n(vector_iterator_t* it_iter, size_t n_step)
{
  assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_iter), it_iter));
  _VECTOR_ITERATOR_COREPOS(it_iter) +=
  _GET_VECTOR_TYPE_SIZE(_VECTOR_ITERATOR_CONTAINER(it_iter)) * n_step;
  assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_iter), it_iter));
}

void vector_iterator_prev_n(vector_iterator_t* it_iter, size_t n_step)
{
  assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_iter), it_iter));
  _VECTOR_ITERATOR_COREPOS(it_iter) -=
  _GET_VECTOR_TYPE_SIZE(_VECTOR_ITERATOR_CONTAINER(it_iter)) * n_step;
  assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_iter), it_iter));
}

void* vector_iterator_at(vector_iterator_t* it_iter, size_t n_index)
{
  vector_iterator_next_n(it_iter, n_index);
  return vector_iterator_get_pointer(it_iter);
}

void* vector_iterator_get_pointer(vector_iterator_t* it_iter)
{
  assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_iter), it_iter));
  assert((_byte_t*)it_iter->_t_pos < _VECTOR_ITERATOR_CONTAINER(it_iter)->_pby_finish);

  /* char* */
  // @TODO
  //if (strncmp(_GET_VECTOR_TYPE_BASENAME(_VECTOR_ITERATOR_CONTAINER(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
  //    return string_c_str((string_t*)_VECTOR_ITERATOR_COREPOS(it_iter));
  //else
  return _VECTOR_ITERATOR_COREPOS(it_iter);
}

void* vector_iterator_get_pointer_ignore_cstr(vector_iterator_t* it_iter)
{
  assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_iter), it_iter));
  assert((_byte_t*)it_iter->_t_pos < _VECTOR_ITERATOR_CONTAINER(it_iter)->_pby_finish);
  return _VECTOR_ITERATOR_COREPOS(it_iter);
}

size_t vector_iterator_minus(vector_iterator_t* it_first, vector_iterator_t* it_second)
{
  assert(iterator_same_type(it_first, it_second));
  assert(_VECTOR_ITERATOR_CONTAINER(it_first) == _VECTOR_ITERATOR_CONTAINER(it_second));
  assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_first), it_first));
  assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_second), it_second));
  return (_VECTOR_ITERATOR_COREPOS(it_first) - _VECTOR_ITERATOR_COREPOS(it_second))
      / (int) _GET_VECTOR_TYPE_SIZE(_VECTOR_ITERATOR_CONTAINER(it_first));
}

#include <stdint.h>
void vector_ctor(vector_t* pvec_vector, size_t size, ...)
{
  // map_t<vector_t<int>, list<string>>
  unsigned char* tmp;
  if (size > TYPE_ID_SIZE)
  {
    pvec_vector->meta._t_typeinfo.typeids_ptr = cstl_alloc(unsigned char, size);
    tmp = pvec_vector->meta._t_typeinfo.typeids_ptr;
  }
  else
  {
    tmp = (unsigned char*) &pvec_vector->meta._t_typeinfo.typeids_ptr;
  }

  va_list args;
  va_start(args, size);
  for (int x = 0; x < size; x++)
  {
    tmp[x] = va_arg(args, int);
  }
  va_end(args);

  pvec_vector->meta._t_containertype = _VECTOR_CONTAINER;
  pvec_vector->meta._t_iteratortype = _RANDOM_ACCESS_ITERATOR;
  pvec_vector->meta._t_typeinfo._t_typeidsize = size;
  pvec_vector->_pby_finish = pvec_vector->_pby_start = pvec_vector->_pby_endofstorage = NULL;
}
void vector_ctor_n(vector_t* pvec_vector, size_t elesize, size_t size, ...)
{
  unsigned char* tmp;
  if (size > TYPE_ID_SIZE)
  {
    pvec_vector->meta._t_typeinfo.typeids_ptr = cstl_alloc(unsigned char, size);
    tmp = pvec_vector->meta._t_typeinfo.typeids_ptr;
  }
  else
  {
    tmp = (unsigned char*) &pvec_vector->meta._t_typeinfo.typeids_ptr;
  }

  va_list args;
  va_start(args, size);
  for (int x = 0; x < size; x++)
  {
    tmp[x] = va_arg(args, int);
  }
  va_end(args);

  pvec_vector->meta._t_containertype = _VECTOR_CONTAINER;
  pvec_vector->meta._t_iteratortype = _RANDOM_ACCESS_ITERATOR;
  pvec_vector->meta._t_typeinfo._t_typeidsize = size;
  type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector);
  pvec_vector->_pby_start = pvec_vector->_pby_finish = cstl_alloc_ex(type->_t_typesize, type->_t_typealign, elesize);
  size_t bytessize = elesize * type->_t_typesize;
  pvec_vector->_pby_endofstorage = pvec_vector->_pby_start + bytessize;

  // this is actually vector's uninitialized_fill_n
  memset(pvec_vector->_pby_start, 0, bytessize);
}

void vector_ctor_n_v(vector_t* pvec_vector, size_t elesize, void* val, size_t size, ...)
{
  unsigned char* tmp;
  if (size > TYPE_ID_SIZE)
  {
    pvec_vector->meta._t_typeinfo.typeids_ptr = cstl_alloc(unsigned char, size);
    tmp = pvec_vector->meta._t_typeinfo.typeids_ptr;
  }
  else
  {
    tmp = (unsigned char*) &pvec_vector->meta._t_typeinfo.typeids_ptr;
  }

  va_list args;
  va_start(args, size);
  for (int x = 0; x < size; x++)
  {
    tmp[x] = va_arg(args, int);
  }
  va_end(args);

  pvec_vector->meta._t_containertype = _VECTOR_CONTAINER;
  pvec_vector->meta._t_iteratortype = _RANDOM_ACCESS_ITERATOR;
  pvec_vector->meta._t_typeinfo._t_typeidsize = size;
  type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector);
  pvec_vector->_pby_start = pvec_vector->_pby_finish = cstl_alloc_ex(type->_t_typesize, type->_t_typealign, elesize);
  pvec_vector->_pby_endofstorage = pvec_vector->_pby_start + elesize * type->_t_typesize;

  bool ret;
  tmp = pvec_vector->_pby_start;
  for (; elesize > 0; elesize--)
  {
    type->_t_typecopy ? type->_t_typecopy(tmp, val, &ret) : memcpy(tmp, val, _GET_VECTOR_TYPE_SIZE(pvec_vector));
    tmp += _GET_VECTOR_TYPE_SIZE(pvec_vector);
  }
}
void vector_ctor_range(vector_t* pvec_vector, forward_iterator_t* first, forward_iterator_t* last)
{
  assert(iterator_limit_type(first, _FORWARD_ITERATOR) && iterator_limit_type(last, _FORWARD_ITERATOR));
  assert(iterator_same_elem_type(first, last));
  assert(iterator_same_type(first, last));

  int elesize = iterator_distance(first, last);
  _ITERATOR_META_TYPE(first)->_t_typeinfo.typeids_ptr = NULL;
  pvec_vector->meta = *_ITERATOR_META_TYPE(first);
  type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector);
  pvec_vector->_pby_start = pvec_vector->_pby_finish = cstl_alloc_ex(type->_t_typesize, type->_t_typealign, elesize);
  pvec_vector->_pby_endofstorage = pvec_vector->_pby_start + elesize * type->_t_typesize;

  random_access_iterator_t itr;
  _ITERATOR_CONTAINER(&itr) = pvec_vector;
  _VECTOR_ITERATOR_COREPOS(&itr) = pvec_vector->_pby_start;
  uninitialized_copy(first, last, &itr);
}
void vector_ctor_vector(vector_t* pvec_vector, vector_t* x)
{
  assert(vector_is_inited(x));

  pvec_vector->meta = x->meta;
  type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector);

  // copy x's type info
  size_t size = pvec_vector->meta._t_typeinfo._t_typeidsize;
  if (size > TYPE_ID_SIZE)
  {
    pvec_vector->meta._t_typeinfo.typeids_ptr = cstl_alloc(unsigned char, size);
    memcpy(pvec_vector->meta._t_typeinfo.typeids_ptr, x->meta._t_typeinfo.typeids_ptr, size);
  }

  int elesize = x->_pby_finish - x->_pby_start;
  if (elesize == 0)
  {
    pvec_vector->_pby_start = pvec_vector->_pby_finish = pvec_vector->_pby_endofstorage = NULL;
  }
  else
  {
    pvec_vector->_pby_start = pvec_vector->_pby_finish = cstl_alloc_ex_totaln(type->_t_typesize, type->_t_typealign,
        elesize);
    pvec_vector->_pby_endofstorage = pvec_vector->_pby_start + elesize;
    _byte_t* to = pvec_vector->_pby_start;
    _byte_t* from = x->_pby_start;
    if (type->_t_typecopy)
    {
      bool ret;
      size_t typesize = _GET_VECTOR_TYPE_SIZE(pvec_vector);
      for (; elesize > 0; elesize--)
      {
        type->_t_typecopy(to, from, &ret);
        to += typesize;
        from += typesize;
      }
    }
    else
    {
      memcpy(to, from, elesize);
    }
  }
}
void vector_dtor(vector_t* pvec_vector)
{
  if (pvec_vector->meta._t_typeinfo._t_typeidsize > TYPE_ID_SIZE && pvec_vector->meta._t_typeinfo.typeids_ptr)
  {
    cstl_free(pvec_vector->meta._t_typeinfo.typeids_ptr);
  }
  if (pvec_vector->_pby_start)
    cstl_free(pvec_vector->_pby_start);
}

