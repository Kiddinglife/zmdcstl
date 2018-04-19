/*
 * cstl_iterator.c
 *
 *  Created on: 7 Mar. 2018
 *      Author: jackiez
 */

#include "cstl_iterator.h"
#include "cstl_vector.h"
#include "cstl_types.h"

bool iterator_is_valid(iterator_t* it_iter)
{
	return ((_ITERATOR_CONTAINER_TYPE(it_iter) >= _VECTOR_CONTAINER &&
		_ITERATOR_CONTAINER_TYPE(it_iter) <= _BASIC_STRING_CONTAINER));
}

bool iterator_same_type(iterator_t* it_first, iterator_t* it_second)
{
	bool b1 = iterator_is_valid(it_first);
	bool b2 = iterator_is_valid(it_first);
	bool b3 = _ITERATOR_CONTAINER_TYPE(it_first) == _ITERATOR_CONTAINER_TYPE(it_second);
	bool b4 = _ITERATOR_TYPE(it_first) == _ITERATOR_TYPE(it_second);
	return b1 && b2 && b3 && b4;
}

bool iterator_before(iterator_t* it_first, iterator_t* it_second)
{
	assert(iterator_same_type(it_first, it_second));
	switch (_ITERATOR_CONTAINER_TYPE(it_first))
	{
	case _VECTOR_CONTAINER:
		return vector_iterator_before(it_first, it_second);
		break;
		/* case _DEQUE_CONTAINER:
		 return _deque_iterator_before(it_first, it_second);
		 break;
		 case _LIST_CONTAINER:
		 return _list_iterator_before(it_first, it_second);
		 break;
		 case _SLIST_CONTAINER:
		 return _slist_iterator_before(it_first, it_second);
		 break;
		 case _SET_CONTAINER:
		 return _set_iterator_before(it_first, it_second);
		 break;
		 case _MULTISET_CONTAINER:
		 return _multiset_iterator_before(it_first, it_second);
		 break;
		 case _MAP_CONTAINER:
		 return _map_iterator_before(it_first, it_second);
		 break;
		 case _MULTIMAP_CONTAINER:
		 return _multimap_iterator_before(it_first, it_second);
		 break;
		 case _HASH_SET_CONTAINER:
		 return _hash_set_iterator_before(it_first, it_second);
		 break;
		 case _HASH_MULTISET_CONTAINER:
		 return _hash_multiset_iterator_before(it_first, it_second);
		 break;
		 case _HASH_MAP_CONTAINER:
		 return _hash_map_iterator_before(it_first, it_second);
		 break;
		 case _HASH_MULTIMAP_CONTAINER:
		 return _hash_multimap_iterator_before(it_first, it_second);
		 break;
		 case _BASIC_STRING_CONTAINER:
		 return _basic_string_iterator_before(it_first, it_second);
		 break;*/
	default:
		return false;
		break;
	}
}

const void* iterator_get_pointer_ignore_cstr(iterator_t* it_iter)
{
	assert(iterator_is_valid(it_iter));

	switch (_ITERATOR_CONTAINER_TYPE(it_iter))
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

bool iterator_same_elem_type(iterator_t* it_first, iterator_t* it_second)
{
	assert(iterator_is_valid(it_first));
	assert(iterator_is_valid(it_second));
	assert(iterator_get_typeinfo(it_first));
	assert(iterator_get_typeinfo(it_second));
	return type_info_is_same(iterator_get_typeinfo(it_first), iterator_get_typeinfo(it_second));
}

bool iterator_equal(iterator_t* it_first, iterator_t* it_second)
{
	assert(iterator_same_type(it_first, it_second));
	assert(iterator_same_elem_type(it_first, it_second));
	return it_first->_t_pos == it_second->_t_pos;
}

bool iterator_valid_range(iterator_t* it_first, iterator_t* it_end,
	iteratortype_t t_type)
{
	return (iterator_same_type(it_first, it_end)
		&& (iterator_equal(it_first, it_end) || iterator_before(it_first, it_end)));
}

void iterator_next(forward_iterator_t* it_iter)
{
	assert(iterator_is_valid(it_iter));
	switch (_ITERATOR_CONTAINER_TYPE(it_iter))
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

void iterator_get_value(input_iterator_t* it_iter, void* pv_value)
{
	assert(pv_value != NULL);
	assert(iterator_is_valid(it_iter));
	switch (_ITERATOR_CONTAINER_TYPE(it_iter))
	{
	case _VECTOR_CONTAINER:
		vector_iterator_get_value((input_iterator_t*)it_iter, pv_value);
		break;
		/*case _LIST_CONTAINER:
		 _list_iterator_get_value(it_iter, pv_value);
		 break;
		 case _DEQUE_CONTAINER:
		 _deque_iterator_get_value(it_iter, pv_value);
		 break;
		 case _SLIST_CONTAINER:
		 _slist_iterator_get_value(it_iter, pv_value);
		 break;
		 case _SET_CONTAINER:
		 _set_iterator_get_value(it_iter, pv_value);
		 break;
		 case _MULTISET_CONTAINER:
		 _multiset_iterator_get_value(it_iter, pv_value);
		 break;
		 case _MAP_CONTAINER:
		 _map_iterator_get_value(it_iter, pv_value);
		 break;
		 case _MULTIMAP_CONTAINER:
		 _multimap_iterator_get_value(it_iter, pv_value);
		 break;
		 case _HASH_SET_CONTAINER:
		 _hash_set_iterator_get_value(it_iter, pv_value);
		 break;
		 case _HASH_MULTISET_CONTAINER:
		 _hash_multiset_iterator_get_value(it_iter, pv_value);
		 break;
		 case _HASH_MAP_CONTAINER:
		 _hash_map_iterator_get_value(it_iter, pv_value);
		 break;
		 case _HASH_MULTIMAP_CONTAINER:
		 _hash_multimap_iterator_get_value(it_iter, pv_value);
		 break;
		 case _BASIC_STRING_CONTAINER:
		 _basic_string_iterator_get_value(it_iter, pv_value);
		 break;*/
	default:
		assert(false);
		break;
	}
}

void iterator_prev(bidirectional_iterator_t* bidirectional_iterator)
{
	assert(iterator_is_valid(bidirectional_iterator));
	//@TODO
	switch (_ITERATOR_CONTAINER_TYPE(bidirectional_iterator))
	{
	case _VECTOR_CONTAINER:
		return vector_iterator_prev(bidirectional_iterator);
		break;
	case _LIST_CONTAINER:
		//return _list_iterator_next(it_iter);
		break;
	case _DEQUE_CONTAINER:
		// return _deque_iterator_next(it_iter);
		break;
	case _SLIST_CONTAINER:
		//return _slist_iterator_next(it_iter);
		break;
	case _SET_CONTAINER:
		//return _set_iterator_next(it_iter);
		break;
	case _MULTISET_CONTAINER:
		//return _multiset_iterator_next(it_iter);
		break;
	case _MAP_CONTAINER:
		//return _map_iterator_next(it_iter);
		break;
	case _MULTIMAP_CONTAINER:
		//return _multimap_iterator_next(it_iter);
		break;
	case _HASH_SET_CONTAINER:
		// return _hash_set_iterator_next(it_iter);
		break;
	case _HASH_MULTISET_CONTAINER:
		//return _hash_multiset_iterator_next(it_iter);
		break;
	case _HASH_MAP_CONTAINER:
		//return _hash_map_iterator_next(it_iter);
		break;
	case _HASH_MULTIMAP_CONTAINER:
		//return _hash_multimap_iterator_next(it_iter);
		break;
	case _BASIC_STRING_CONTAINER:
		//return _basic_string_iterator_next(it_iter);
		break;
	default:
		assert(false);
		break;
	}
}

void iterator_next_n(forward_iterator_t* random_access_iterator, size_t n_step)
{
	assert(iterator_is_valid(random_access_iterator));
	assert(n_step > 0);
	// @TODO
	switch (_ITERATOR_CONTAINER_TYPE(random_access_iterator))
	{
	case _VECTOR_CONTAINER:
		vector_iterator_next_n(random_access_iterator, n_step);
		break;
	case _DEQUE_CONTAINER:
		// deque_iterator_next_n(it_iter, n_step);
		break;
	case _BASIC_STRING_CONTAINER:
		// basic_string_iterator_next_n(it_iter, n_step);
		break;
	default:
		assert(false);
		break;
	}
}

void iterator_prev_n(random_access_iterator_t* it_iter, int n_step)
{
	assert(iterator_is_valid(it_iter));
	assert(n_step > 0);
	//@TODO
	switch (_ITERATOR_CONTAINER_TYPE(it_iter))
	{
	case _VECTOR_CONTAINER:
		return vector_iterator_prev_n(it_iter, n_step);
		break;
	case _DEQUE_CONTAINER:
		//return _deque_iterator_prev_n(it_iter, n_step);
		break;
	case _BASIC_STRING_CONTAINER:
		// return _basic_string_iterator_prev_n(it_iter, n_step);
		break;
	default:
		assert(false);
		break;
	}
}

bool iterator_less(random_access_iterator_t* it_first,
	random_access_iterator_t* it_second)
{
	assert(iterator_is_valid(it_first));
	assert(iterator_is_valid(it_second));

	switch (_ITERATOR_CONTAINER_TYPE(it_first))
	{
	case _VECTOR_CONTAINER:
		return vector_iterator_less(it_first, it_second);
		break;
	case _DEQUE_CONTAINER:
		//return _deque_iterator_less(it_first, it_second);
		break;
	case _BASIC_STRING_CONTAINER:
		//return _basic_string_iterator_less(it_first, it_second);
		break;
	default:
		assert(false);
		return false;
		break;
	}
	return false;
}

bool iterator_less_equal(random_access_iterator_t* it_first,
	random_access_iterator_t* it_second)
{
	return iterator_less(it_first, it_second)
		|| iterator_equal(it_first, it_second);
}

bool iterator_greater(random_access_iterator_t* it_first,
	random_access_iterator_t* it_second)
{
	return iterator_less(it_second, it_first);
}

bool iterator_greater_equal(random_access_iterator_t* it_first,
	random_access_iterator_t* it_second)
{
	return iterator_greater(it_first, it_second)
		|| iterator_equal(it_first, it_second);
}

void* iterator_at(random_access_iterator_t* it_iter, int n_index)
{
	assert(iterator_is_valid(it_iter));

	switch (_ITERATOR_CONTAINER_TYPE(it_iter))
	{
	case _VECTOR_CONTAINER:
		return vector_iterator_at(it_iter, n_index);
		break;
	case _DEQUE_CONTAINER:
		// return _deque_iterator_at(it_iter, n_index);
		break;
	case _BASIC_STRING_CONTAINER:
		//return _basic_string_iterator_at(it_iter, n_index);
		break;
	default:
		assert(false);
		return NULL;
		break;
	}
	return NULL;
}

int iterator_continue_minus(random_access_iterator_t* it_first,
	random_access_iterator_t* it_second)
{
	assert(iterator_is_valid(it_first));
	assert(iterator_is_valid(it_second));

	switch (_ITERATOR_CONTAINER_TYPE(it_first))
	{
	case _VECTOR_CONTAINER:
		return vector_iterator_minus(it_first, it_second);
		break;
	case _DEQUE_CONTAINER:
		//return _deque_iterator_minus(it_first, it_second);
		break;
	case _BASIC_STRING_CONTAINER:
		//return _basic_string_iterator_minus(it_first, it_second);
		break;
	default:
		assert(false);
		return -1;
		break;
	}
	return -1;
}

void iterator_advance(forward_iterator_t* it_iter, size_t n_step)
{
	assert(iterator_is_valid(it_iter));
	switch (_ITERATOR_CONTAINER_TYPE(it_iter))
	{
	case _VECTOR_CONTAINER:
		it_iter->_t_pos += _ITERATOR_TYPE_INFO_TYPE(it_iter)->_t_typesize
			* n_step;
		assert(
			it_iter->_t_pos >= ((vector_t*)it_iter->_pt_container)->_pby_finish);
		break;
	case _DEQUE_CONTAINER: // DYNAMIC-GROWN ARRAY BASED
	  //it_iter->_t_pos += ((type_info_t*) it_iter->_pt_container)->_pt_type->_t_typesize * n_step;
	  //assert();     // @TODO
		break;
	case _BASIC_STRING_CONTAINER:
		//it_iter->_t_pos += ((type_info_t*) it_iter->_pt_container)->_pt_type->_t_typesize * n_step;
		//assert();     // @TODO
		break;
	default:
		for (; n_step > 0; --n_step)
			iterator_next(it_iter);
		break;
	}
}

void iterator_disadvance(bidirectional_iterator_t* it_iter, size_t n_step)
{
	assert(iterator_is_valid(it_iter));
	for (; n_step > 0; --n_step)
		iterator_prev(it_iter);
}

int iterator_distance(iterator_t* it_first, iterator_t* it_second)
{
	assert(iterator_same_type(it_first, it_second));
	switch (_ITERATOR_CONTAINER_TYPE(it_first))
	{
	case _VECTOR_CONTAINER:
	case _DEQUE_CONTAINER:
	case _BASIC_STRING_CONTAINER:
		return iterator_continue_minus(it_first, it_second);
		break;
	case _LIST_CONTAINER:
		//return _list_iterator_distance(it_first, it_second);
		break;
	case _SLIST_CONTAINER:
		//return _slist_iterator_distance(it_first, it_second);
		break;
	case _SET_CONTAINER:
		//return _set_iterator_distance(it_first, it_second);
		break;
	case _MULTISET_CONTAINER:
		//return _multiset_iterator_distance(it_first, it_second);
		break;
	case _MAP_CONTAINER:
		//return _map_iterator_distance(it_first, it_second);
		break;
	case _MULTIMAP_CONTAINER:
		// return _multimap_iterator_distance(it_first, it_second);
		break;
	case _HASH_SET_CONTAINER:
		// return _hash_set_iterator_distance(it_first, it_second);
		break;
	case _HASH_MULTISET_CONTAINER:
		//return _hash_multiset_iterator_distance(it_first, it_second);
		break;
	case _HASH_MAP_CONTAINER:
		//return _hash_map_iterator_distance(it_first, it_second);
		break;
	case _HASH_MULTIMAP_CONTAINER:
		//return _hash_multimap_iterator_distance(it_first, it_second);
		break;
	default:
		assert(false);
		return -1;
		break;
	}
	return -1;
}
