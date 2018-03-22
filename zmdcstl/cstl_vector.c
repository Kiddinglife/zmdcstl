#include "cstl_types.h"
#include "cstl_memory.h"
#include "cstl_alloc.h"
#include "cstl_vector.h"

bool vector_is_inited(const vector_t* cpvec_vector)
{
  if (cpvec_vector == NULL)
    return false;
  if (_GET_VECTOR_TYPE_INFO_TYPE(cpvec_vector) == NULL)
    return false;
  if (cpvec_vector->_pby_start == NULL && cpvec_vector->_pby_finish == NULL && cpvec_vector->_pby_endofstorage == NULL)
    return true;
  if (cpvec_vector->_pby_start != NULL && cpvec_vector->_pby_finish != NULL && cpvec_vector->_pby_endofstorage != NULL
      && cpvec_vector->_pby_finish > cpvec_vector->_pby_start
      && cpvec_vector->_pby_endofstorage > cpvec_vector->_pby_start
      && cpvec_vector->_pby_endofstorage >= cpvec_vector->_pby_finish)
    return true;
  return false;
}

bool vector_iterator_valid(const vector_t* cpvec_vector, vector_iterator_t* it_iter)
{
  bool b1 = vector_is_inited(cpvec_vector) &&
  _VECTOR_ITERATOR_CONTAINER_TYPE(it_iter) == _VECTOR_CONTAINER &&
  _VECTOR_ITERATOR_CONTAINER(it_iter) == cpvec_vector &&
  _VECTOR_ITERATOR_COREPOS(it_iter) >= cpvec_vector->_pby_start;

  bool b2 = _VECTOR_ITERATOR_COREPOS(it_iter) <= cpvec_vector->_pby_finish;
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
  //_VECTOR_ITERATOR_ITERATOR_TYPE(it_end) = _RANDOM_ACCESS_ITERATOR;
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
  if (size > TYPE_ID_SIZE)
  {
    pvec_vector->meta._t_typeinfo.typeids_ptr = cstl_alloc(unsigned char, size);
    pvec_vector->_pby_endofstorage = pvec_vector->meta._t_typeinfo.typeids_ptr;
  } else
  {
    pvec_vector->_pby_endofstorage = (unsigned char*) &pvec_vector->meta._t_typeinfo.typeids_ptr;
  }

  va_list args;
  va_start(args, size);
  for (int x = 0; x < size; x++)
  {
    pvec_vector->_pby_endofstorage[x] = va_arg(args, int);
  }
  va_end(args);

  pvec_vector->meta._t_containertype = _VECTOR_CONTAINER;
  pvec_vector->meta._t_typeinfo._t_typeidsize = size;
  pvec_vector->_pby_finish = pvec_vector->_pby_start = pvec_vector->_pby_endofstorage = NULL;
}
void vector_ctor_n(vector_t* pvec_vector, size_t elesize, size_t size, ...)
{
  if (size > TYPE_ID_SIZE)
  {
    pvec_vector->meta._t_typeinfo.typeids_ptr = cstl_alloc(unsigned char, size);
    pvec_vector->_pby_endofstorage = pvec_vector->meta._t_typeinfo.typeids_ptr;
  } else
  {
    pvec_vector->_pby_endofstorage = (unsigned char*) &pvec_vector->meta._t_typeinfo.typeids_ptr;
  }

  va_list args;
  va_start(args, size);
  for (int x = 0; x < size; x++)
  {
    pvec_vector->_pby_endofstorage[x] = va_arg(args, int);
  }
  va_end(args);

  pvec_vector->meta._t_containertype = _VECTOR_CONTAINER;
  pvec_vector->meta._t_typeinfo._t_typeidsize = size;
  type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector);
  if (type->_t_typeinit)
  {
    bool ret = false;
    size = type->_t_typesize;
    pvec_vector->_pby_finish = pvec_vector->_pby_start = cstl_alloc_ex_totaln(type->_t_typealign, elesize * size);
    for (; elesize > 0; elesize--)
    {
      type->_t_typeinit(pvec_vector->_pby_finish, &ret);
      pvec_vector->_pby_finish += size;
    }
  } else
  {
    size = type->_t_typesize * elesize;
    pvec_vector->_pby_finish = pvec_vector->_pby_start = cstl_alloc_ex_totaln(type->_t_typealign, size);
    memset(pvec_vector->_pby_start, 0, size);
    pvec_vector->_pby_finish += size;
  }
  pvec_vector->_pby_endofstorage = pvec_vector->_pby_finish;
}

void vector_ctor_n_v(vector_t* pvec_vector, size_t elesize, void* val, size_t size, ...)
{
  //printf("vector_ctor_n_v\n");
  if (size > TYPE_ID_SIZE)
  {
    pvec_vector->meta._t_typeinfo.typeids_ptr = cstl_alloc(unsigned char, size);
    pvec_vector->_pby_endofstorage = pvec_vector->meta._t_typeinfo.typeids_ptr;
  } else
  {
    pvec_vector->_pby_endofstorage = (unsigned char*) &pvec_vector->meta._t_typeinfo.typeids_ptr;
  }

  va_list args;
  va_start(args, size);
  for (int x = 0; x < size; x++)
  {
    pvec_vector->_pby_endofstorage[x] = va_arg(args, int);
  }
  va_end(args);

  pvec_vector->meta._t_containertype = _VECTOR_CONTAINER;
  pvec_vector->meta._t_typeinfo._t_typeidsize = size;
  type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector);
  size = type->_t_typesize;
  pvec_vector->_pby_start = pvec_vector->_pby_finish = cstl_alloc_ex(type->_t_typesize, type->_t_typealign, elesize);

  bool ret;
  if (type->_t_typecopy)
  {
    for (; elesize > 0; elesize--)
    {
      type->_t_typecopy(pvec_vector->_pby_finish, val, &ret);
      pvec_vector->_pby_finish += size;
    }
  } else
  {
    for (; elesize > 0; elesize--)
    {
      cstl_memcpy(pvec_vector->_pby_finish, val, size);
      pvec_vector->_pby_finish += size;
    }
  }
  pvec_vector->_pby_endofstorage = pvec_vector->_pby_finish;
}
void vector_ctor_range(vector_t* pvec_vector, forward_iterator_t* first, forward_iterator_t* last)
{
  //printf("vector_ctor_range\n");
  assert(iterator_limit_type(first, _FORWARD_ITERATOR) && iterator_limit_type(last, _FORWARD_ITERATOR));
  assert(iterator_same_elem_type(first, last));
  assert(iterator_same_type(first, last));

  pvec_vector->meta = *_ITERATOR_META_TYPE(first);
  // copy x's type info
  size_t size = pvec_vector->meta._t_typeinfo._t_typeidsize;
  if (size > TYPE_ID_SIZE)
  {
    pvec_vector->meta._t_typeinfo.typeids_ptr = cstl_alloc(unsigned char, size);
    cstl_memcpy(pvec_vector->meta._t_typeinfo.typeids_ptr,
    _ITERATOR_TYPE_INFO(first).typeids_ptr, size);
  }
  size = iterator_distance(first, last);
  if (size == 0)
  {
    pvec_vector->_pby_start = pvec_vector->_pby_finish = pvec_vector->_pby_endofstorage = NULL;
  } else
  {
    type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector);
    pvec_vector->_pby_start = cstl_alloc_ex(type->_t_typesize, type->_t_typealign, size);
    random_access_iterator_t ritr;
    ritr._pt_container = pvec_vector;
    ritr._t_pos = pvec_vector->_pby_start;
    uninitialized_copy(first, last, &ritr);
    pvec_vector->_pby_endofstorage = pvec_vector->_pby_finish = ritr._t_pos;
  }
}

void vector_ctor_range_n(vector_t* pvec_vector, forward_iterator_t* first, size_t size)
{
  assert(iterator_limit_type(first, _FORWARD_ITERATOR));

  pvec_vector->meta = *_ITERATOR_META_TYPE(first);
  // copy x's type info
  if (pvec_vector->meta._t_typeinfo._t_typeidsize > TYPE_ID_SIZE)
  {
    pvec_vector->meta._t_typeinfo.typeids_ptr = cstl_alloc(unsigned char, pvec_vector->meta._t_typeinfo._t_typeidsize);
    cstl_memcpy(pvec_vector->meta._t_typeinfo.typeids_ptr,
    _ITERATOR_TYPE_INFO(first).typeids_ptr, pvec_vector->meta._t_typeinfo._t_typeidsize);
  }
  if (size == 0)
  {
    pvec_vector->_pby_start = pvec_vector->_pby_finish = pvec_vector->_pby_endofstorage = NULL;
  } else
  {
    type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector);
    pvec_vector->_pby_start = cstl_alloc_ex(type->_t_typesize, type->_t_typealign, size);
    random_access_iterator_t ritr;
    ritr._pt_container = pvec_vector;
    ritr._t_pos = pvec_vector->_pby_start;
    uninitialized_copy_n(first, size, &ritr);
    pvec_vector->_pby_endofstorage = pvec_vector->_pby_finish = ritr._t_pos;
  }
}
void vector_ctor_vector(vector_t* pvec_vector, vector_t* x)
{
  assert(vector_is_inited(x));

  pvec_vector->meta = x->meta;
  // copy x's type info
  size_t size = pvec_vector->meta._t_typeinfo._t_typeidsize;
  if (size > TYPE_ID_SIZE)
  {
    pvec_vector->meta._t_typeinfo.typeids_ptr = cstl_alloc(unsigned char, size);
    cstl_memcpy(pvec_vector->meta._t_typeinfo.typeids_ptr, x->meta._t_typeinfo.typeids_ptr, size);
  }

  _byte_t* from = x->_pby_start;
  _byte_t* end = x->_pby_finish;
  size = end - from;
  if (size == 0)
  {
    pvec_vector->_pby_start = pvec_vector->_pby_finish = pvec_vector->_pby_endofstorage = NULL;
  } else
  {
    type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector);
    pvec_vector->_pby_start = pvec_vector->_pby_finish = cstl_alloc_ex_totaln(type->_t_typealign, size);
    if (type->_t_typecopy)
    {
      bool ret;
      size = type->_t_typesize;
      for (; from != end; from += size)
      {
        type->_t_typecopy(pvec_vector->_pby_finish, from, &ret);
        pvec_vector->_pby_finish += size;
      }
    } else
    {
      cstl_memcpy(pvec_vector->_pby_start, from, size);
      pvec_vector->_pby_finish += size;
    }
    pvec_vector->_pby_endofstorage = pvec_vector->_pby_finish;
  }
}
void vector_dtor(vector_t* pvec_vector)
{
  if (pvec_vector->meta._t_typeinfo._t_typeidsize > TYPE_ID_SIZE && pvec_vector->meta._t_typeinfo.typeids_ptr)
    cstl_free(pvec_vector->meta._t_typeinfo.typeids_ptr);  //free typeids
  if (pvec_vector->_pby_start)
  {
    type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector);
    _byte_t* tmp = pvec_vector->_pby_start;
    if (type->_t_typedestroy != NULL)
    {
      bool ret = false;
      size_t tsize = type->_t_typesize;
      for (; pvec_vector->_pby_start != pvec_vector->_pby_finish; pvec_vector->_pby_start += tsize)
      {
        // free elment
        type->_t_typedestroy(pvec_vector->_pby_start, &ret);
      }
    }
    //free vector
    cstl_free(tmp);
  }
}

// This needs to return a value of at least currentCapacity and at least 1.
#define get_new_capacity_(currentCapacity, typesize) \
  ((currentCapacity > 0) ? (2 * currentCapacity) : typesize)

static inline void do_insert_value_at_end_(vector_t* pvec_vector, const void* value)
{
  type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector);
  const size_t nPrevSize = pvec_vector->_pby_finish - pvec_vector->_pby_start;
  const size_t nNewSize = get_new_capacity_(nPrevSize, type->_t_typesize);
  _byte_t* pNewData = cstl_alloc_ex_totaln(type->_t_typealign, nNewSize);
  _byte_t* pNewEnd = pNewData;
  bool ret = false;

  if (type->_t_typecopy)
  {
    // copy the old elements to pNewData
    _byte_t* from = pvec_vector->_pby_start;
    do
    {
      type->_t_typecopy(pNewEnd, from, &ret);
      pNewEnd += type->_t_typesize;
      from += type->_t_typesize;
    } while (from != pvec_vector->_pby_finish);

    // copy new element to pNewEnd
    type->_t_typecopy(pNewEnd, value, &ret);

    // destruct each old element if there is _t_typecopy
    for (; pvec_vector->_pby_start != pvec_vector->_pby_finish; pvec_vector->_pby_start += type->_t_typesize)
    {
      type->_t_typedestroy(pvec_vector->_pby_start, &ret);
      assert(ret);
    }

  } else
  {
    // copy the old elements to pNewData
    cstl_memcpy(pNewEnd, pvec_vector->_pby_start, nPrevSize);
    pNewEnd += nPrevSize;
    // copy new element to pNewEnd
    cstl_memcpy(pNewEnd, value, type->_t_typesize);
  }

  //free the old vector
  cstl_free(pvec_vector->_pby_start);

  // set up new vector
  pvec_vector->_pby_start = pNewData;
  pvec_vector->_pby_finish = pNewEnd;
  pvec_vector->_pby_endofstorage = pNewData + nNewSize;
}

bool vector_is_same_type(const vector_t* cpvec_first, const vector_t* cpvec_second)
{
  assert(cpvec_first != NULL);
  assert(cpvec_second != NULL);
  assert(vector_is_inited(cpvec_first));
  assert(vector_is_inited(cpvec_second));

  if (cpvec_first == cpvec_second)
    return true;

  type_t* typefirst = _GET_VECTOR_TYPE_INFO_TYPE(cpvec_first);
  type_t* typesecond = _GET_VECTOR_TYPE_INFO_TYPE(cpvec_second);
  type_info_t* typeinfofirst = &_GET_VECTOR_TYPE_INFO(cpvec_first);
  type_info_t* typeinfosecond = &_GET_VECTOR_TYPE_INFO(cpvec_second);
  return (typefirst->_t_typeid == typesecond->_t_typeid) && type_info_is_same(typeinfofirst, typeinfosecond);
}

size_t vector_size(vector_t* cpvec_vector)
{
  assert(vector_is_inited(cpvec_vector));
  return (cpvec_vector->_pby_finish - cpvec_vector->_pby_start) / _GET_VECTOR_TYPE_SIZE(cpvec_vector);
}

size_t vector_capacity(vector_t* cpvec_vector)
{
  assert(vector_is_inited(cpvec_vector));
  return (cpvec_vector->_pby_endofstorage - cpvec_vector->_pby_start) / _GET_VECTOR_TYPE_SIZE(cpvec_vector);
}

bool vector_equal(vector_t* cpvec_first, vector_t* cpvec_second)
{
  assert(vector_is_inited(cpvec_first));
  assert(vector_is_inited(cpvec_second));
  assert(vector_is_same_type(cpvec_first, cpvec_second));

  if (cpvec_first == cpvec_second)
    return true;

  if (vector_size(cpvec_first) != vector_size(cpvec_second))
    return false;


  return true;
}

void vector_swap(vector_t* pvec_first, vector_t* pvec_second)
{
  /* test the two vector has the same type */
  assert(vector_is_inited(pvec_first));
  assert(vector_is_inited(pvec_second));
  assert(vector_is_same_type(pvec_first, pvec_second));
  vector_t vec_swap; /* the swap temporary vector */
  vec_swap = *pvec_first;
  *pvec_first = *pvec_second;
  *pvec_second = vec_swap;
}
