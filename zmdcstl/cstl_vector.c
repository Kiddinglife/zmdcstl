#include "cstl_types.h"
#include "cstl_memory.h"
#include "cstl_alloc.h"
#include "cstl_vector.h"
#include "cstl_algorithm.h"

static inline void destruct_vec(type_t* type, _byte_t* first, _byte_t* end)
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
static inline _byte_t* uninitialized_default_fill_n_vector(type_t* type, _byte_t* destination, size_t totalbytes)
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
		memset(destination, 0, totalbytes);
	return end;
}
static inline void uninitialized_fill_continue(type_t* type, _byte_t* first, _byte_t* e, void* val)
{
	bfun_t cpyctor = type->_t_typecopy;
	switch (type->_t_typeid) {
	case cstl_int8:
		fill_char((char*)first, (char*)e, *(char*)val);
		break;
	case cstl_uint8:
		fill_uchar((unsigned char*)first, e, *(unsigned char*)val);
		break;
	case cstl_int16:
		fill_int16((int16_t*)first, (int16_t*)e, *(int16_t*)val);
		break;
	case cstl_uint16:
		fill_uint16((uint16_t*)first, (uint16_t*)e, *(uint16_t*)val);
		break;
	case cstl_int32:
		fill_int32((int32_t*)first, (int32_t*)e, *(int32_t*)val);
		break;
	case cstl_uint32:
		fill_uint32((uint32_t*)first, (uint32_t*)e, *(uint32_t*)val);
		break;
	case cstl_int64:
		fill_int64((int64_t*)first, (int64_t*)e, *(int64_t*)val);
		break;
	case cstl_uint64:
		fill_uint64((uint64_t*)first, (uint64_t*)e, *(uint64_t*)val);
		break;
	case cstl_void_pt:
		fill_uint64((uint64_t*)first, (uint64_t*)e, *(uint64_t*)val);
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
				memcpy(first, val, tsize);
		}
		break;
	}
}
static inline _byte_t* uninitialized_fill_n_continue(type_t* type, _byte_t* destPosition, size_t totalbytes,
	const void* val)
{
	bfun_t cpyctor = type->_t_typecopy;
	_byte_t* end = destPosition + totalbytes;
	switch (type->_t_typeid) {
	case cstl_int8:
		fill_char((char*)destPosition, (char*)end, *(char*)val);
		break;
	case cstl_uint8:
		fill_uchar((unsigned char*)destPosition, end, *(unsigned char*)val);
		break;
	case cstl_int16:
		fill_int16((int16_t*)destPosition, (int16_t*)end, *(int16_t*)val);
		break;
	case cstl_uint16:
		fill_uint16((uint16_t*)destPosition, (uint16_t*)end, *(uint16_t*)val);
		break;
	case cstl_int32:
		fill_int32((int32_t*)destPosition, (int32_t*)end, *(int32_t*)val);
		break;
	case cstl_uint32:
		fill_uint32((uint32_t*)destPosition, (uint32_t*)end, *(uint32_t*)val);
		break;
	case cstl_int64:
		fill_int64((int64_t*)destPosition, (int64_t*)end, *(int64_t*)val);
		break;
	case cstl_uint64:
		fill_uint64((uint64_t*)destPosition, (uint64_t*)end, *(uint64_t*)val);
		break;
	case cstl_void_pt:
		fill_uint64((uint64_t*)destPosition, (uint64_t*)end, *(uint64_t*)val);
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
				memcpy(destPosition, val, size);
		}
		break;
	}
	return end;
}
static inline _byte_t* copy_from_vec_to_vec(type_t* type, _byte_t* from, _byte_t* end, _byte_t* result)
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
		memcpy(result, from, end - from);
		result += end - from;
	}
	return result;
}
static inline _byte_t* uninitialized_copy_from_vec_to_vec(type_t* type, _byte_t* from, _byte_t* end, _byte_t* result)
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
		memcpy(result, from, end - from);
		result += end - from;
	}
	return result;
}
static inline _byte_t* uninitialized_copy_from_vec_to_vec_dtor_from(type_t* type, _byte_t* from, _byte_t* end,
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
		memcpy(result, from, end - from);
		result += end - from;
	}
	return result;
}
static inline _byte_t* fill_n_vec(type_t* type, _byte_t* destPosition, size_t n, const void* val)
{
	bfun_t cpyctor = type->_t_typecopy;
	_byte_t* e = destPosition + type->_t_typesize * n;
	switch (type->_t_typeid) {
	case cstl_int8:
		fill_n_char((char*)destPosition, n, *(char*)val);
		break;
	case cstl_uint8:
		fill_n_uchar((unsigned char*)destPosition, n, *(unsigned char*)val);
		break;
	case cstl_int16:
		fill_n_int16((int16_t*)destPosition, n, *(int16_t*)val);
		break;
	case cstl_uint16:
		fill_n_uint16((uint16_t*)destPosition, n, *(uint16_t*)val);
		break;
	case cstl_int32:
		fill_n_int32((int32_t*)destPosition, n, *(int32_t*)val);
		break;
	case cstl_uint32:
		fill_n_uint32((uint32_t*)destPosition, n, *(uint32_t*)val);
		break;
	case cstl_int64:
		fill_n_int64((int64_t*)destPosition, n, *(int64_t*)val);
		break;
	case cstl_uint64:
		fill_n_uint64((uint64_t*)destPosition, n, *(uint64_t*)val);
		break;
	case cstl_void_pt:
		fill_n_uint64((uint64_t*)destPosition, n, *(uint64_t*)val);
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
				memcpy(destPosition, val, tsize);
		}
		break;
	}
	return e;
}
static inline void fill_vec(type_t* type, _byte_t* first, _byte_t* e, void* val)
{
	bfun_t cpyctor = type->_t_typecopy;
	switch (type->_t_typeid) {
	case cstl_int8:
		fill_char((char*)first, (char*)e, *(char*)val);
		break;
	case cstl_uint8:
		fill_uchar((unsigned char*)first, e, *(unsigned char*)val);
		break;
	case cstl_int16:
		fill_int16((int16_t*)first, (int16_t*)e, *(int16_t*)val);
		break;
	case cstl_uint16:
		fill_uint16((uint16_t*)first, (uint16_t*)e, *(uint16_t*)val);
		break;
	case cstl_int32:
		fill_int32((int32_t*)first, (int32_t*)e, *(int32_t*)val);
		break;
	case cstl_uint32:
		fill_uint32((uint32_t*)first, (uint32_t*)e, *(uint32_t*)val);
		break;
	case cstl_int64:
		fill_int64((int64_t*)first, (int64_t*)e, *(int64_t*)val);
		break;
	case cstl_uint64:
		fill_uint64((uint64_t*)first, (uint64_t*)e, *(uint64_t*)val);
		break;
	case cstl_void_pt:
		fill_uint64((uint64_t*)first, (uint64_t*)e, *(uint64_t*)val);
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
				memcpy(first, val, tsize);
		}
		break;
	}
}
void vecor_debug(vector_t* pvec)
{
	printf("debug:\nstart=%p\nfinish=%p\nend=%p\n", pvec->_pby_start, pvec->_pby_finish, pvec->_pby_endofstorage);
	printf("finish-start=%lu\n", pvec->_pby_finish - pvec->_pby_start);
	printf("end-start=%lu\n", pvec->_pby_endofstorage - pvec->_pby_start);
}
bool vector_is_inited(const vector_t* cpvec_vector)
{
	if (cpvec_vector == NULL)
	{
		return false;
	}
	if (_GET_VECTOR_TYPE_INFO_TYPE(cpvec_vector) == NULL)
	{

		return false;
	}
	if (_GET_VECTOR_TYPE_INFO_TYPE(cpvec_vector)->_t_typeless == NULL)
	{
		return false;
	}
	if (_GET_VECTOR_TYPE_INFO_TYPE(cpvec_vector)->_t_typedestroy != NULL &&
		_GET_VECTOR_TYPE_INFO_TYPE(cpvec_vector)->_t_typecopy == NULL)
		return false;
	if (_GET_VECTOR_TYPE_INFO_TYPE(cpvec_vector)->_t_typedestroy == NULL &&
		_GET_VECTOR_TYPE_INFO_TYPE(cpvec_vector)->_t_typecopy != NULL)
		return false;
	if (cpvec_vector->meta._t_containertype != _VECTOR_CONTAINER)
		return false;
	if (cpvec_vector->meta._t_iteratortype_t != _RANDOM_ACCESS_ITERATOR)
		return false;
	if (cpvec_vector->meta.iterator_dref != vector_iterator_dref)
		return false;
	if (cpvec_vector->meta.iterator_equal != vector_iterator_equal)
		return false;
	if (cpvec_vector->meta.iterator_next != vector_iterator_next)
		return false;
	if (cpvec_vector->meta.iterator_next != vector_iterator_next)
		return false;
	return true;
}
bool vector_iterator_valid(const vector_t* cpvec_vector, vector_iterator_t* it_iter)
{
	bool b1 = vector_is_inited(cpvec_vector);
	bool b2 = _VECTOR_ITERATOR_CONTAINER_TYPE(it_iter) == _VECTOR_CONTAINER;
	bool b3 = _ITERATOR_TYPE(it_iter) == _RANDOM_ACCESS_ITERATOR;
	bool b4 = _VECTOR_ITERATOR_CONTAINER(it_iter) == cpvec_vector;
	bool b5 = _VECTOR_ITERATOR_COREPOS(it_iter) >= cpvec_vector->_pby_start;
	bool b6 = _VECTOR_ITERATOR_COREPOS(it_iter) <= cpvec_vector->_pby_finish;
	return b1 && b2 && b3 && b4 && b5 && b6;
}
bool vector_iterator_valid_end(const vector_t* cpvec_vector, vector_iterator_t* it_iter)
{
	bool b1 = vector_is_inited(cpvec_vector);
	bool b2 = _VECTOR_ITERATOR_CONTAINER_TYPE(it_iter) == _VECTOR_CONTAINER;
	bool b3 = _VECTOR_ITERATOR_CONTAINER(it_iter) == cpvec_vector;
	bool b4 = _VECTOR_ITERATOR_COREPOS(it_iter) >= cpvec_vector->_pby_start;
	bool b5 = _VECTOR_ITERATOR_COREPOS(it_iter) <= cpvec_vector->_pby_endofstorage;
	return b1 && b2 && b3 && b4 && b5;
}
void vector_iterator_next(vector_iterator_t* it_iter)
{
	assert(vector_is_inited(_VECTOR_ITERATOR_CONTAINER(it_iter)));
	it_iter->_t_pos += _GET_VECTOR_TYPE_SIZE(_VECTOR_ITERATOR_CONTAINER(it_iter));
}
void vector_end(vector_t* cpvec_vector, vector_iterator_t* it_end)
{
	assert(vector_is_inited(cpvec_vector));
	_ITERATOR_CONTAINER(it_end) = cpvec_vector;
	_VECTOR_ITERATOR_COREPOS(it_end) = cpvec_vector->_pby_finish;
}
void vector_begin(vector_t* cpvec_vector, vector_iterator_t* begin)
{
	assert(vector_is_inited(cpvec_vector));
	_ITERATOR_CONTAINER(begin) = cpvec_vector;
	_VECTOR_ITERATOR_COREPOS(begin) = cpvec_vector->_pby_start;
}
void vector_end_again(vector_iterator_t* it_end)
{
	assert(it_end != NULL);
	assert((vector_t*)it_end->_pt_container != NULL);
	assert(vector_is_inited((vector_t*)it_end->_pt_container));
	_VECTOR_ITERATOR_COREPOS(it_end) = ((vector_t*)it_end->_pt_container)->_pby_finish;
}
_byte_t* vector_iterator_dref(vector_iterator_t* it)
{
	return it->_t_pos;
}
size_t vector_iterator_distance(iterator_t* first, iterator_t* last)
{
	vector_t* cpvec_vector = (vector_t*)first->_pt_container;
	assert(vector_is_inited(cpvec_vector));
	size_t diff = last->_t_pos > first->_t_pos ? (last->_t_pos - first->_t_pos) : (first->_t_pos - last->_t_pos);
	return (size_t)(diff / _GET_VECTOR_TYPE_SIZE(cpvec_vector));
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
	assert(vector_iterator_valid_end(_VECTOR_ITERATOR_CONTAINER(it_first), it_first));
	assert(vector_iterator_valid_end(_VECTOR_ITERATOR_CONTAINER(it_second), it_second));
	return (_VECTOR_ITERATOR_COREPOS(it_second) - _VECTOR_ITERATOR_COREPOS(it_first))
		/ (int)_GET_VECTOR_TYPE_SIZE(_VECTOR_ITERATOR_CONTAINER(it_first));
}
void vector_ctor(vector_t* pvec_vector, size_t size, ...)
{
	// map_t<vector_t<int>, list<string>>
	if (size > TYPE_ID_SIZE)
	{
		pvec_vector->meta._t_typeinfo.typeids_ptr = cstl_alloc(unsigned char, size);
		pvec_vector->_pby_endofstorage = pvec_vector->meta._t_typeinfo.typeids_ptr;
	}
	else
	{
		pvec_vector->_pby_endofstorage = (unsigned char*)&pvec_vector->meta._t_typeinfo.typeids_ptr;
	}
	va_list args;
	va_start(args, size);
	for (int x = 0; x < size; x++)
		pvec_vector->_pby_endofstorage[x] = va_arg(args, int);
	va_end(args);
	pvec_vector->meta._t_containertype = _VECTOR_CONTAINER;
	pvec_vector->meta._t_iteratortype_t = _RANDOM_ACCESS_ITERATOR;
	pvec_vector->meta._t_typeinfo._t_typeidsize = size;
	pvec_vector->meta.iterator_equal = vector_iterator_equal;
	pvec_vector->meta.iterator_next = vector_iterator_next;
	pvec_vector->meta.iterator_next_n = vector_iterator_next_n;
	pvec_vector->meta.iterator_pre = vector_iterator_prev;
	pvec_vector->meta.iterator_pre_n = vector_iterator_prev_n;
	pvec_vector->meta.iterator_dref = vector_iterator_dref;
	pvec_vector->meta.iterator_distance = vector_iterator_distance;
	pvec_vector->meta._t_type = _INIT_VECTOR_TYPE_INFO_TYPE(pvec_vector);

	pvec_vector->_pby_finish = pvec_vector->_pby_start = pvec_vector->_pby_endofstorage = NULL;
}
void vector_ctor_n(vector_t* pvec_vector, size_t elesize, size_t size, ...)
{
	va_list args;
	va_start(args, size);
	if (size > TYPE_ID_SIZE)
	{
		pvec_vector->meta._t_typeinfo.typeids_ptr = cstl_alloc(unsigned char, size);
		pvec_vector->_pby_endofstorage = pvec_vector->meta._t_typeinfo.typeids_ptr;
	}
	else
	{
		pvec_vector->_pby_endofstorage = (unsigned char*)&pvec_vector->meta._t_typeinfo.typeids_ptr;
	}
	for (int x = 0; x < size; x++)
		pvec_vector->_pby_endofstorage[x] = va_arg(args, int);
	pvec_vector->meta._t_containertype = _VECTOR_CONTAINER;
	pvec_vector->meta._t_iteratortype_t = _RANDOM_ACCESS_ITERATOR;
	pvec_vector->meta._t_typeinfo._t_typeidsize = size;
	pvec_vector->meta.iterator_equal = vector_iterator_equal;
	pvec_vector->meta.iterator_next = vector_iterator_next;
	pvec_vector->meta.iterator_next_n = vector_iterator_next_n;
	pvec_vector->meta.iterator_pre = vector_iterator_prev;
	pvec_vector->meta.iterator_pre_n = vector_iterator_prev_n;
	pvec_vector->meta.iterator_dref = vector_iterator_dref;
	pvec_vector->meta.iterator_distance = vector_iterator_distance;
	pvec_vector->meta._t_type = _INIT_VECTOR_TYPE_INFO_TYPE(pvec_vector);

	type_t* type = pvec_vector->meta._t_type;
	size = type->_t_typesize * elesize;
	pvec_vector->_pby_finish = pvec_vector->_pby_start = cstl_alloc_ex_totaln(type->_t_typealign, size);
	pvec_vector->_pby_endofstorage = pvec_vector->_pby_finish = uninitialized_default_fill_n_vector(type,
		pvec_vector->_pby_start, size);
	va_end(args);
}
void vector_ctor_n_v(vector_t* pvec_vector, size_t elesize, void* val, size_t size, ...)
{
	va_list args;
	va_start(args, size);
	if (size > TYPE_ID_SIZE)
	{
		pvec_vector->meta._t_typeinfo.typeids_ptr = cstl_alloc(unsigned char, size);
		pvec_vector->_pby_endofstorage = pvec_vector->meta._t_typeinfo.typeids_ptr;
	}
	else
	{
		pvec_vector->_pby_endofstorage = (unsigned char*)&pvec_vector->meta._t_typeinfo.typeids_ptr;
	}
	for (int x = 0; x < size; x++)
		pvec_vector->_pby_endofstorage[x] = va_arg(args, int);
	pvec_vector->meta._t_containertype = _VECTOR_CONTAINER;
	pvec_vector->meta._t_iteratortype_t = _RANDOM_ACCESS_ITERATOR;
	pvec_vector->meta._t_typeinfo._t_typeidsize = size;
	pvec_vector->meta.iterator_equal = vector_iterator_equal;
	pvec_vector->meta.iterator_next = vector_iterator_next;
	pvec_vector->meta.iterator_next_n = vector_iterator_next_n;
	pvec_vector->meta.iterator_pre = vector_iterator_prev;
	pvec_vector->meta.iterator_pre_n = vector_iterator_prev_n;
	pvec_vector->meta.iterator_dref = vector_iterator_dref;
	pvec_vector->meta.iterator_distance = vector_iterator_distance;
	pvec_vector->meta._t_type = _INIT_VECTOR_TYPE_INFO_TYPE(pvec_vector);
	type_t* type = pvec_vector->meta._t_type;
	size = type->_t_typesize * elesize;
	pvec_vector->_pby_start = pvec_vector->_pby_finish = cstl_alloc_ex_totaln(type->_t_typealign, size);
	pvec_vector->_pby_endofstorage = pvec_vector->_pby_finish = uninitialized_fill_n_continue(type,
		pvec_vector->_pby_start, size, val);
	va_end(args);
}
void vector_ctor_array(vector_t* pvec_vector, size_t elesize, void* array, size_t size, ...)
{
	va_list args;
	va_start(args, size);
	if (size > TYPE_ID_SIZE)
	{
		pvec_vector->meta._t_typeinfo.typeids_ptr = cstl_alloc(unsigned char, size);
		pvec_vector->_pby_endofstorage = pvec_vector->meta._t_typeinfo.typeids_ptr;
	}
	else
	{
		pvec_vector->_pby_endofstorage = (unsigned char*)&pvec_vector->meta._t_typeinfo.typeids_ptr;
	}
	for (int x = 0; x < size; x++)
		pvec_vector->_pby_endofstorage[x] = va_arg(args, int);
	pvec_vector->meta._t_containertype = _VECTOR_CONTAINER;
	pvec_vector->meta._t_iteratortype_t = _RANDOM_ACCESS_ITERATOR;
	pvec_vector->meta._t_typeinfo._t_typeidsize = size;
	pvec_vector->meta.iterator_equal = vector_iterator_equal;
	pvec_vector->meta.iterator_next = vector_iterator_next;
	pvec_vector->meta.iterator_next_n = vector_iterator_next_n;
	pvec_vector->meta.iterator_pre = vector_iterator_prev;
	pvec_vector->meta.iterator_pre_n = vector_iterator_prev_n;
	pvec_vector->meta.iterator_dref = vector_iterator_dref;
	pvec_vector->meta.iterator_distance = vector_iterator_distance;
	pvec_vector->meta._t_type = _INIT_VECTOR_TYPE_INFO_TYPE(pvec_vector);
	type_t* type = pvec_vector->meta._t_type;
	size = type->_t_typesize * elesize;
	pvec_vector->_pby_start = pvec_vector->_pby_finish = cstl_alloc_ex_totaln(type->_t_typealign, size);
	pvec_vector->_pby_endofstorage = pvec_vector->_pby_finish = uninitialized_copy_from_vec_to_vec(type, array,
		((_byte_t*)array) + size, pvec_vector->_pby_start);
	va_end(args);
}
void vector_ctor_range(vector_t* pvec_vector, forward_iterator_t* first, forward_iterator_t* last)
{
	assert(iterator_same_elem_type(first, last));
	assert(iterator_same_type(first, last));
	pvec_vector->meta = *_ITERATOR_META_TYPE(first);
	// copy x's type info
	size_t size = pvec_vector->meta._t_typeinfo._t_typeidsize;
	if (size > TYPE_ID_SIZE)
	{
		pvec_vector->meta._t_typeinfo.typeids_ptr = cstl_alloc(unsigned char, size);
		memcpy(pvec_vector->meta._t_typeinfo.typeids_ptr,
			_ITERATOR_TYPE_INFO(first).typeids_ptr, size);
	}
	size = (_ITERATOR_META_TYPE(first)->iterator_distance)(first, last);
	if (size == 0)
	{
		pvec_vector->_pby_start = pvec_vector->_pby_finish = pvec_vector->_pby_endofstorage = NULL;
	}
	else
	{
		type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector);
		pvec_vector->_pby_start = cstl_alloc_ex(type->_t_typesize, type->_t_typealign, size);
		vector_create_iterator(result, pvec_vector, pvec_vector->_pby_start);
		uninitialized_copy(first, last, &result);
		pvec_vector->_pby_endofstorage = pvec_vector->_pby_finish = result._t_pos;
	}
}
void vector_ctor_range_n(vector_t* pvec_vector, forward_iterator_t* first, size_t size)
{
	pvec_vector->meta = *_ITERATOR_META_TYPE(first);
	// copy x's type info
	if (pvec_vector->meta._t_typeinfo._t_typeidsize > TYPE_ID_SIZE)
	{
		pvec_vector->meta._t_typeinfo.typeids_ptr = cstl_alloc(unsigned char, pvec_vector->meta._t_typeinfo._t_typeidsize);
		memcpy(pvec_vector->meta._t_typeinfo.typeids_ptr,
			_ITERATOR_TYPE_INFO(first).typeids_ptr, pvec_vector->meta._t_typeinfo._t_typeidsize);
	}
	if (size == 0)
		pvec_vector->_pby_start = pvec_vector->_pby_finish = pvec_vector->_pby_endofstorage = NULL;
	else
	{
		type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector);
		pvec_vector->_pby_start = cstl_alloc_ex(type->_t_typesize, type->_t_typealign, size);
		vector_create_iterator(result, pvec_vector, pvec_vector->_pby_start);
		uninitialized_copy_n(first, size, &result);
		pvec_vector->_pby_endofstorage = pvec_vector->_pby_finish = result._t_pos;
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
		memcpy(pvec_vector->meta._t_typeinfo.typeids_ptr, x->meta._t_typeinfo.typeids_ptr, size);
	}
	_byte_t* from = x->_pby_start;
	_byte_t* end = x->_pby_finish;
	size = end - from;
	if (size == 0)
		pvec_vector->_pby_start = pvec_vector->_pby_finish = pvec_vector->_pby_endofstorage = NULL;
	else
	{
		type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector);
		pvec_vector->_pby_start = cstl_alloc_ex_totaln(type->_t_typealign, size);
		pvec_vector->_pby_endofstorage = pvec_vector->_pby_finish = uninitialized_copy_from_vec_to_vec(type, from, end,
			pvec_vector->_pby_start);
	}
}
void vector_dtor(vector_t* pvec_vector)
{
	if (pvec_vector->meta._t_typeinfo._t_typeidsize > TYPE_ID_SIZE && pvec_vector->meta._t_typeinfo.typeids_ptr)
	{
		cstl_free(pvec_vector->meta._t_typeinfo.typeids_ptr); //free typeids
		pvec_vector->meta._t_typeinfo.typeids_ptr = 0;
	}
	if (pvec_vector->_pby_start)
	{
		type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector);
		destruct_vec(type, pvec_vector->_pby_start, pvec_vector->_pby_finish);
		cstl_free(pvec_vector->_pby_start);
		pvec_vector->_pby_start = 0;
	}
}
void vector_reserve_n(vector_t* cpvec_vector, size_t n)
{
	type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(cpvec_vector);
	size_t size = n * type->_t_typesize;
	if (size > (cpvec_vector->_pby_endofstorage - cpvec_vector->_pby_start))
	{
		// do grow
		_byte_t* pNewData = cstl_alloc_ex_totaln(type->_t_typealign, size);
		_byte_t* pNewStart = pNewData;
		pNewData = uninitialized_copy_from_vec_to_vec_dtor_from(type, cpvec_vector->_pby_start, cpvec_vector->_pby_finish,
			pNewData);
		cstl_free(cpvec_vector->_pby_start);
		cpvec_vector->_pby_start = pNewStart;
		cpvec_vector->_pby_finish = pNewData;
		cpvec_vector->_pby_endofstorage = pNewStart + size;
	}
}
void vector_set_capacity(vector_t* cpvec_vector, size_t n)
{
	type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(cpvec_vector);
	size_t newcapacity = n * type->_t_typesize;
	size_t vcsize = cpvec_vector->_pby_finish - cpvec_vector->_pby_start;
	if (newcapacity > vcsize)
	{
		_byte_t* s = cpvec_vector->_pby_start;
		_byte_t* e = cpvec_vector->_pby_finish;
		cpvec_vector->_pby_start = cstl_alloc_ex_totaln(type->_t_typealign, newcapacity);
		cpvec_vector->_pby_finish = uninitialized_copy_from_vec_to_vec(type, s, e, cpvec_vector->_pby_start);
		cpvec_vector->_pby_endofstorage = cpvec_vector->_pby_start + newcapacity;
		destruct_vec(type, s, e);
		cstl_free(s);
	}
	else
	{
		newcapacity != 0 ? vector_resize_n(cpvec_vector, n) : vector_clear(cpvec_vector);
		vector_shrink_to_fit(cpvec_vector);
	}
}
void vector_shrink_to_fit(vector_t* x)
{
	vector_t pvec_vector;
	pvec_vector.meta = x->meta;
	size_t size = x->_pby_finish - x->_pby_start;
	if (size == 0)
	{
		pvec_vector._pby_start = pvec_vector._pby_finish = pvec_vector._pby_endofstorage = NULL;
	}
	else
	{
		type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector);
		pvec_vector._pby_start = pvec_vector._pby_finish = cstl_alloc_ex_totaln(type->_t_typealign, size);
		pvec_vector._pby_endofstorage = pvec_vector._pby_finish = uninitialized_copy_from_vec_to_vec(type, x->_pby_start,
			x->_pby_finish, pvec_vector._pby_finish);
	}
	vector_swap(x, &pvec_vector);
	if (pvec_vector._pby_start)
	{
		type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector);
		destruct_vec(type, pvec_vector._pby_start, pvec_vector._pby_finish); // destruct vector
		cstl_free(pvec_vector._pby_start); //free vector
	}
}
// This needs to return a value of at least currentCapacity and at least typesize.
#define get_new_capacity_(currentCapacity, typesize) (((currentCapacity) > 0) ? (2 * (currentCapacity)) : typesize)
static inline void do_insert_value_at_end_v(vector_t* pvec_vector, const void* value)
{
	type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector);
	size_t nPrevSize = pvec_vector->_pby_endofstorage - pvec_vector->_pby_finish;
	if (type->_t_typesize > nPrevSize)
	{
		const size_t nNewSize = get_new_capacity_(pvec_vector->_pby_endofstorage - pvec_vector->_pby_start,
			type->_t_typesize);
		_byte_t* pNewData = cstl_alloc_ex_totaln(type->_t_typealign, nNewSize);
		// copy the old elements to pNewData
		_byte_t* pNewEnd = uninitialized_copy_from_vec_to_vec_dtor_from(type, pvec_vector->_pby_start,
			pvec_vector->_pby_finish, pNewData);
		//free the old vector
		cstl_free(pvec_vector->_pby_start);
		// copy the new element
		pNewEnd = fill_n_vec(type, pNewEnd, 1, value);
		// set up new vector
		pvec_vector->_pby_start = pNewData;
		pvec_vector->_pby_finish = pNewEnd;
		pvec_vector->_pby_endofstorage = pNewData + nNewSize;
	}
	else
	{
		// copy the new element
		pvec_vector->_pby_finish = fill_n_vec(type, pvec_vector->_pby_finish, 1, value);
	}
}
static inline void do_insert_value_at_end_n(vector_t* pvec_vector, size_t totalbytes)
{
	type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector);
	size_t nPrevSize = pvec_vector->_pby_endofstorage - pvec_vector->_pby_finish;
	if (totalbytes > nPrevSize)
	{
		nPrevSize = pvec_vector->_pby_endofstorage - pvec_vector->_pby_start;
		size_t nNewSize = cstl_min(get_new_capacity_(nPrevSize, type->_t_typesize), nPrevSize + totalbytes);
		_byte_t* pNewData = cstl_alloc_ex_totaln(type->_t_typealign, nNewSize);
		// copy the old elements to pNewData
		_byte_t* pNewEnd = uninitialized_copy_from_vec_to_vec_dtor_from(type, pvec_vector->_pby_start,
			pvec_vector->_pby_finish, pNewData);
		//free the old vector
		cstl_free(pvec_vector->_pby_start);
		// init new element to pNewEnd
		pNewEnd = uninitialized_default_fill_n_vector(type, pNewEnd, totalbytes);
		// set up new vector
		pvec_vector->_pby_start = pNewData;
		pvec_vector->_pby_finish = pNewEnd;
		pvec_vector->_pby_endofstorage = pNewData + nNewSize;
	}
	else
		//totalbytes <= pvec_vector->_pby_endofstorage - pvec_vector->_pby_finish
		pvec_vector->_pby_finish = uninitialized_default_fill_n_vector(type, pvec_vector->_pby_finish, totalbytes);
}
static inline void do_insert_value_at_end_n_v(vector_t* pvec_vector, size_t totalbytes, void* val)
{
	type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector);
	size_t nPrevSize = pvec_vector->_pby_endofstorage - pvec_vector->_pby_finish;
	if (totalbytes > nPrevSize)
	{
		nPrevSize = pvec_vector->_pby_endofstorage - pvec_vector->_pby_start;
		size_t nNewSize = cstl_min(get_new_capacity_(nPrevSize, type->_t_typesize), nPrevSize + totalbytes);
		_byte_t* pNewData = cstl_alloc_ex_totaln(type->_t_typealign, nNewSize);
		// uninit copy the old elements to pNewData
		_byte_t* pNewEnd = uninitialized_copy_from_vec_to_vec(type, pvec_vector->_pby_start, pvec_vector->_pby_finish,
			pNewData);
		// uninit fill new element to pNewEnd
		pNewEnd = uninitialized_fill_n_continue(type, pNewEnd, totalbytes, val);
		//free the old vector
		cstl_free(pvec_vector->_pby_start);
		// set up new vector
		pvec_vector->_pby_start = pNewData;
		pvec_vector->_pby_finish = pNewEnd;
		pvec_vector->_pby_endofstorage = pNewData + nNewSize;
	}
	else
		//totalbytes <= pvec_vector->_pby_endofstorage - pvec_vector->_pby_finish
		pvec_vector->_pby_finish = uninitialized_fill_n_continue(type, pvec_vector->_pby_finish, totalbytes, val);
}
void vector_pop_back(vector_t* cpvec_vector)
{
	assert(vector_is_inited(cpvec_vector));
	type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(cpvec_vector);
	cpvec_vector->_pby_finish -= type->_t_typesize;
	if (type->_t_typedestroy)
	{
		bool ret;
		type->_t_typedestroy(cpvec_vector->_pby_finish, &ret);
	}
}
void* vector_push_back(vector_t* cpvec_vector)
{
	assert(vector_is_inited(cpvec_vector));
	type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(cpvec_vector);
	do_insert_value_at_end_n(cpvec_vector, type->_t_typesize);
	return cpvec_vector->_pby_finish - type->_t_typesize;
}
void vector_push_back_v(vector_t* cpvec_vector, void* value)
{
	assert(vector_is_inited(cpvec_vector));
	do_insert_value_at_end_v(cpvec_vector, value);
}
void* vector_push_back_v_placement(vector_t* cpvec_vector)
{
	assert(vector_is_inited(cpvec_vector));
	if (cpvec_vector->_pby_finish == cpvec_vector->_pby_endofstorage)
	{
		size_t newsize = ((size_t)(cpvec_vector->_pby_endofstorage - cpvec_vector->_pby_start));
		vector_reserve_n(cpvec_vector, newsize << 1);
	}
	return cpvec_vector->_pby_finish + _GET_VECTOR_TYPE_INFO_TYPE(cpvec_vector)->_t_typesize;
}
void vector_resize_n_v(vector_t* cpvec_vector, size_t n, void* value)
{
	assert(vector_is_inited(cpvec_vector));
	type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(cpvec_vector);
	size_t size = n * type->_t_typesize;
	if (size > cpvec_vector->_pby_finish - cpvec_vector->_pby_start)
		do_insert_value_at_end_n_v(cpvec_vector, size, value);
	else
	{
		_byte_t* s = cpvec_vector->_pby_start + size;
		destruct_vec(type, s, cpvec_vector->_pby_finish);
		cpvec_vector->_pby_finish = s;
		fill_n_vec(type, cpvec_vector->_pby_start, n, value);
	}
}
void vector_resize_n(vector_t* cpvec_vector, size_t n)
{
	assert(vector_is_inited(cpvec_vector));
	type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(cpvec_vector);
	size_t size = n * type->_t_typesize;
	if (size > cpvec_vector->_pby_finish - cpvec_vector->_pby_start)
		do_insert_value_at_end_n(cpvec_vector, size);
	else
	{
		_byte_t* s = cpvec_vector->_pby_start + size;
		destruct_vec(type, s, cpvec_vector->_pby_finish);
		cpvec_vector->_pby_finish = s;
	}
}
bool vector_is_same_type(const vector_t* cpvec_first, const vector_t* cpvec_second)
{
	assert(vector_is_inited(cpvec_first));
	assert(vector_is_inited(cpvec_second));
	if (cpvec_first == cpvec_second)
		return true;
	type_t* typefirst = _GET_VECTOR_TYPE_INFO_TYPE(cpvec_first);
	type_t* typesecond = _GET_VECTOR_TYPE_INFO_TYPE(cpvec_second);
	type_info_t* typeinfofirst = &_GET_VECTOR_TYPE_INFO(cpvec_first);
	type_info_t* typeinfosecond = &_GET_VECTOR_TYPE_INFO(cpvec_second);
	bool b1 = typefirst->_t_typeid == typesecond->_t_typeid;
	bool b2 = type_info_is_same(typeinfofirst, typeinfosecond);
	return b1 && b2;
}
size_t vector_size(vector_t* cpvec_vector)
{
	assert(vector_is_inited(cpvec_vector));
	return (cpvec_vector->_pby_finish - cpvec_vector->_pby_start) / _GET_VECTOR_TYPE_SIZE(cpvec_vector);
}
bool empty(vector_t* cpvec_vector)
{
	assert(vector_is_inited(cpvec_vector));
	return cpvec_vector->_pby_start == cpvec_vector->_pby_finish;
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
	vector_create_iterator(first1, cpvec_first, cpvec_first->_pby_start);
	vector_create_iterator(last1, cpvec_first, cpvec_first->_pby_finish);
	vector_create_iterator(first2, cpvec_second, cpvec_second->_pby_start);
	bool ret = cstl_equal(&first1, &last1, &first2);
	return ret;
}
void vector_swap(vector_t* pvec_first, vector_t* pvec_second)
{
	/* test the two vector has the same type */
	assert(vector_is_same_type(pvec_first, pvec_second));
	vector_t vec_swap; /* the swap temporary vector */
	vec_swap = *pvec_first;
	*pvec_first = *pvec_second;
	*pvec_second = vec_swap;
}
void vector_clear(vector_t* pvec_vector)
{
	assert(vector_is_inited(pvec_vector));
	type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector);
	destruct_vec(type, pvec_vector->_pby_start, pvec_vector->_pby_finish);
	pvec_vector->_pby_finish = pvec_vector->_pby_start;
}
void vector_assign_n_v(vector_t* pvec, void* val, size_t elesize)
{
	assert(vector_is_inited(pvec));
	type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec);
	size_t totalbytes = elesize * (type->_t_typesize);
	if (totalbytes > pvec->_pby_endofstorage - pvec->_pby_start)
	{
		// elesize > vector_capacity
		destruct_vec(type, pvec->_pby_start, pvec->_pby_finish);
		cstl_free(pvec->_pby_start);
		pvec->_pby_start = cstl_alloc_ex_totaln(type->_t_typealign, totalbytes);
		pvec->_pby_endofstorage = pvec->_pby_finish = uninitialized_fill_n_continue(type, pvec->_pby_start, totalbytes,
			val);
	}
	else if (totalbytes > pvec->_pby_finish - pvec->_pby_start)
	{
		// elesize > vector_size
		// fill old elements
		fill_vec(type, pvec->_pby_start, pvec->_pby_finish, val);
		// uninit fill new elements
		_byte_t* newstart = pvec->_pby_finish;
		pvec->_pby_finish = pvec->_pby_start + totalbytes;
		uninitialized_fill_continue(type, newstart, pvec->_pby_finish, val);
	}
	else if (totalbytes > 0)
	{
		//0 < elesize <= vector_size
		// fill old elements
		fill_vec(type, pvec->_pby_start, pvec->_pby_start + totalbytes, val);
	}
}
static inline void vector_assign_const_vector_aux(vector_t* to, _byte_t* _pby_start, _byte_t* _pby_finish)
{
	size_t totalbytes = _pby_finish - _pby_start;
	if (totalbytes == 0)
	{
		to->_pby_finish = to->_pby_start;
		return;
	}
	type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(to);
	if (totalbytes > to->_pby_endofstorage - to->_pby_start)
	{ // elesize > vector_capacity
		_byte_t* newstart = cstl_alloc_ex_totaln(type->_t_typealign, totalbytes);
		_byte_t* newend = uninitialized_copy_from_vec_to_vec(type, _pby_start, _pby_finish, newstart);

		destruct_vec(type, to->_pby_start, to->_pby_finish);
		cstl_free(to->_pby_start);

		to->_pby_start = newstart;
		to->_pby_finish = newend;
		to->_pby_endofstorage = newstart + totalbytes;
	}
	else if (totalbytes <= to->_pby_finish - to->_pby_start)
	{ //elesize <= size
		_byte_t* newsfinish = copy_from_vec_to_vec(type, _pby_start, _pby_finish, to->_pby_start);
		destruct_vec(type, newsfinish, to->_pby_finish);
		to->_pby_finish = newsfinish;
	}
	else
	{ //size < elesize <= capacity
		_byte_t* pos = _pby_start + (to->_pby_finish - to->_pby_start);
		copy_from_vec_to_vec(type, _pby_start, pos, to->_pby_start);
		to->_pby_finish = uninitialized_copy_from_vec_to_vec(type, pos, _pby_finish, to->_pby_finish);
	}
}
void vector_assign_const_vector(vector_t* to, const vector_t* from)
{
	assert(vector_is_same_type(to, from));
	if (to == from)
		return;
	vector_assign_const_vector_aux(to, from->_pby_start, from->_pby_finish);
}
void vector_assign_vector(vector_t* to, vector_t* from)
{
	assert(vector_is_same_type(to, from));
	if (to == from)
		return;
	if (to->_pby_start)
	{
		destruct_vec(_GET_VECTOR_TYPE_INFO_TYPE(to), to->_pby_start, to->_pby_finish);
		cstl_free(to->_pby_start);
	}
	to->_pby_start = from->_pby_start;
	to->_pby_finish = from->_pby_finish;
	to->_pby_endofstorage = from->_pby_endofstorage;
	from->_pby_endofstorage = from->_pby_start = from->_pby_finish = NULL;
}
void vector_erase(random_access_iterator_t* position, bool destruct_element)
{
	assert(position->_t_pos >= ((vector_t*)(position->_pt_container))->_pby_start);
	assert(position->_t_pos < ((vector_t*)(position->_pt_container))->_pby_finish);
	vector_t* pvec = ((vector_t*)(position->_pt_container));
	type_t* type = pvec->meta._t_type;
	if (destruct_element &&  type->_t_typedestroy)
	{
		bool ret;
		type->_t_typedestroy(position->_t_pos, &ret); // destruct the erased element
	}
	memcpy(position->_t_pos, position->_t_pos + type->_t_typesize, pvec->_pby_finish - position->_t_pos - type->_t_typesize);
	pvec->_pby_finish -= type->_t_typesize;
}
void vector_erase_unsort(random_access_iterator_t* position, bool destruct_element)
{
	assert(position->_t_pos >= ((vector_t*)(position->_pt_container))->_pby_start);
	assert(position->_t_pos < ((vector_t*)(position->_pt_container))->_pby_finish);
	vector_t* pvec = (vector_t*)(position->_pt_container);
	type_t* type = pvec->meta._t_type;
	if (destruct_element && type->_t_typedestroy)
	{
		bool ret;
		type->_t_typedestroy(position->_t_pos, &ret); // destruct the erased element
	}
	pvec->_pby_finish -= type->_t_typesize;
	if (position->_t_pos != pvec->_pby_finish)
		memcpy(position->_t_pos, pvec->_pby_finish, type->_t_typesize);
}
void vector_erase_range(random_access_iterator_t* first, random_access_iterator_t* last, bool destruct)
{
	vector_t* pvec = ((vector_t*)first->_pt_container);
	assert(pvec->_pby_start < pvec->_pby_finish);
	assert(last->_t_pos > first->_t_pos && last->_t_pos <= pvec->_pby_finish);
	assert(first->_t_pos >= pvec->_pby_start && first->_t_pos < pvec->_pby_finish);
	if (destruct)
		destruct_vec(pvec->meta._t_type, first->_t_pos, last->_t_pos);
	memcpy(first->_t_pos, last->_t_pos, pvec->_pby_finish - last->_t_pos);
	pvec->_pby_finish -= last->_t_pos - first->_t_pos;
}
void vector_insert_range(random_access_iterator_t* insertpos, input_iterator_t* first, input_iterator_t* last)
{

}
void vector_insert_v_copy(random_access_iterator_t* first, void** value)
{
	vector_t* pvec = ((vector_t*)first->_pt_container);
	assert(vector_is_inited(pvec));
	assert(pvec->_pby_start < pvec->_pby_finish);
	assert(first->_t_pos >= pvec->_pby_start && first->_t_pos <= pvec->_pby_finish);
	const ptrdiff_t nbytes = first->_t_pos - pvec->_pby_start; // Save this because we might reallocate.
	type_t* type = pvec->meta._t_type;
	size_t tsize = type->_t_typesize;
	_byte_t* destPosition = first->_t_pos;
	if (pvec->_pby_finish != pvec->_pby_endofstorage)
	{
		// value pointer is indes 3 v 4, insertion index = 1
		// 0 1 2 3 4
		// 1 2 3 4 5
		// 1    2 3 4 5 as you see now nums[4] has a value of 3 instead of 4
		// so we need increment it
		if (destPosition != pvec->_pby_finish)
		{
			// If value comes from within the range to be moved.
			// Set pValue to be where it will be after the copy.
			if (*value >= destPosition && *value < pvec->_pby_finish)
				(_byte_t*)(*value) += tsize;
			memmove(destPosition + tsize, destPosition, pvec->_pby_finish - destPosition);
		}
		if (type->ctor_copy)
			type->ctor_copy(destPosition, value);
		else
			memcpy(destPosition, value, tsize);
		pvec->_pby_finish += tsize;
	}
	else
	{
		const size_t newsize = get_new_capacity_(pvec->_pby_finish - pvec->_pby_start, tsize);
		_byte_t* pNewData = cstl_alloc_ex_totaln(type->_t_typealign, newsize);
		// move inserted ele to new buffer
		size_t nPosSize = nbytes;
		if (type->ctor_copy)
			type->ctor_copy(pNewData + nPosSize, value);
		else
			memcpy(pNewData + nPosSize, value, tsize);
		// move old eles to new buffer
		_byte_t* pNewEnd = (_byte_t*)(memcpy(pNewData, pvec->_pby_start, nPosSize));
		pNewEnd += tsize;
		nPosSize = pvec->_pby_finish - destPosition;
		pNewEnd = (_byte_t*)(memcpy(pNewEnd, destPosition, nPosSize));
		// destruct old vec
		destruct_vec(type, pvec->_pby_start, pvec->_pby_finish);
		cstl_free(pvec->_pby_start);
		//reset new vec
		pvec->_pby_start = pNewData;
		pvec->_pby_finish = pNewEnd;
		pvec->_pby_endofstorage = pNewData + newsize;
	}
	first->_t_pos = pvec->_pby_start + nbytes;
}
void vector_insert_v_move(random_access_iterator_t* first, void** value)
{
	vector_t* pvec = ((vector_t*)first->_pt_container);
	type_t* type = pvec->meta._t_type;
	assert(vector_is_inited(pvec));
	assert(pvec->_pby_start < pvec->_pby_finish);
	assert(first->_t_pos >= pvec->_pby_start && first->_t_pos <= pvec->_pby_finish);
	assert(type->ctor_move);
	assert(type->dtor); // havextor_move, must have dtor as there is heap allocation
	const ptrdiff_t nbytes = first->_t_pos - pvec->_pby_start; // Save this because we might reallocate.
	size_t tsize = type->_t_typesize;
	_byte_t* destPosition = first->_t_pos;
	if (pvec->_pby_finish < pvec->_pby_endofstorage)
	{
		// value pointer is indes 3 v 4, insertion index = 1
		// 0 1 2 3 4
		// 1 2 3 4 5
		// 1    2 3 4 5 as you see now nums[4] has a value of 3 instead of 4
		// so we need increment it
		if (destPosition != pvec->_pby_finish)
		{
			// If value comes from within the range to be moved.
			// Set pValue to be where it will be after the copy.
			if (*value >= destPosition && *value < pvec->_pby_finish)
				(_byte_t*)(*value) += tsize;
			memmove(destPosition + tsize, destPosition, pvec->_pby_finish - destPosition);
		}
		type->ctor_move(destPosition, value);
		pvec->_pby_finish += tsize;
	}
	else
	{
		const size_t newsize = get_new_capacity_(pvec->_pby_finish - pvec->_pby_start, tsize);
		_byte_t* pNewData = cstl_alloc_ex_totaln(type->_t_typealign, newsize);
		// move inserted ele to new buffer
		size_t nPosSize = nbytes;
		type->ctor_move(pNewData + nPosSize, value);
		// move old eles to new buffer
		_byte_t* pNewEnd = (_byte_t*)(memcpy(pNewData, pvec->_pby_start, nPosSize));
		pNewEnd += tsize;
		nPosSize = pvec->_pby_finish - destPosition;
		pNewEnd = (_byte_t*)(memcpy(pNewEnd, destPosition, nPosSize));
		// destruct old vec
		destruct_vec(type, pvec->_pby_start, pvec->_pby_finish);
		cstl_free(pvec->_pby_start);
		//reset new vec
		pvec->_pby_start = pNewData;
		pvec->_pby_finish = pNewEnd;
		pvec->_pby_endofstorage = pNewData + newsize;
	}
	first->_t_pos = pvec->_pby_start + nbytes;
}
#define vector_assign_range_aux(itertor_equal, itertor_next)\
if (cpy)\
{\
  bool is_opt_assign = true;\
  for (; s != e && !itertor_equal(first, last); s += tsize, itertor_next(first))\
    cpy(s, first->_t_pos, &is_opt_assign);\
} else\
{\
  for (; s != e && !itertor_equal(first, last); s += tsize, itertor_next(first))\
    memcpy(s, first->_t_pos, tsize);\
}\
if (itertor_equal(first, last))\
{\
  vector_create_iterator(sitr, pvec, s);\
  vector_create_iterator(eitr, pvec, pvec->_pby_finish);\
  vector_erase_range(&sitr, &eitr, false);\
} else\
{\
  vector_create_iterator(pos, pvec, pvec->_pby_finish);\
  vector_insert_range(&pos, first, last);\
}
void vector_assign_range(vector_t* pvec, input_iterator_t * first, input_iterator_t * last)
{
	//todo  need earse() and insert() done
	assert(vector_is_inited(pvec));
	iterator_same_elem_type(first, last);
	assert(_GET_VECTOR_TYPE_INFO_TYPE(pvec)->_t_typeid == _ITERATOR_TYPE_INFO_TYPE(first)->_t_typeid);
	if (first->_t_pos == last->_t_pos)
		return;
	type_t* type = _GET_VECTOR_TYPE_INFO_TYPE(pvec);
	size_t tsize = type->_t_typesize;
	bfun_t cpy = type->_t_typecopy;
	_byte_t* s = pvec->_pby_start;
	_byte_t* e = pvec->_pby_finish;
	switch (_ITERATOR_CONTAINER_TYPE(first)) {
	case _VECTOR_CONTAINER:
		vector_assign_const_vector_aux(pvec, first->_t_pos, last->_t_pos);
		break;
	case _DEQUE_CONTAINER:
		/*
		 if (cpy)
		 {
		 bool is_opt_assign = true;
		 for (; s != e && !itertor_equal(first, last); s += tsize, itertor_next(first))
		 cpy(s, first->_t_pos, &is_opt_assign);
		 } else
		 {
		 for (; s != e && !itertor_equal(first, last); s += tsize, itertor_next(first))
		 memcpy(s, first->_t_pos, tsize);
		 }
		 if (itertor_equal(first, last))
		 {
		 vector_create_iterator(sitr, pvec, s);
		 vector_create_iterator(eitr, pvec, pvec->_pby_finish);
		 vector_erase_range(pvec, &sitr, &eitr);
		 } else
		 {
		 vector_create_iterator(pos, pvec, pvec->_pby_finish);
		 vector_insert(pos, first, last);
		 }
		 */
		vector_assign_range_aux(vector_iterator_equal, vector_iterator_next)
			break;
	case _BASIC_STRING_CONTAINER:
		break;
	case _LIST_CONTAINER:
		//vector_assign_range_aux(list_iterator_equal, list_iterator_next)
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
void vector_assign_array(vector_t* to, _byte_t* elearr, size_t elesize)
{

}

