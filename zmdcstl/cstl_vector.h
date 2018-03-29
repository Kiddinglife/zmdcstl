///////////////////////////////////////////////////////////////////////////////
// This file implements a vector (array-like container), much like the C++ std::vector.
// The primary distinctions between this vector and std::vector are:
//    - vector has a couple extension functions that increase performance.
//    - vector can contain objects with alignment requirements. 
//      std::vector cannot do so without a bit of tedious non-portable effort.
//    - vector supports debug memory naming natively.
//    - vector is easier to read, debug, and visualize.
//    - vector doesn't have exception handling, as is sometimes the case 
//       with console or embedded environments.
//    - vector has less deeply nested function calls and allows the user to 
//      enable forced inlining in debug builds in order to reduce bloat.
//    - vector<bool> is a vector of boolean values and not a bit vector.
//    - vector guarantees that memory is contiguous and that vector::iterator
//      is nothing more than a pointer to T.
//    - vector has an explicit data() method for obtaining a pointer to storage 
//      which is safe to call even if the block is empty. This avoids the 
//      common &v[0], &v.front(), and &*v.begin() constructs that trigger false 
//      asserts in STL debugging modes.
//    - vector data is guaranteed to be contiguous.
//    - vector has a set_capacity() function which frees excess capacity. 
//      The only way to do this with std::vector is via the cryptic non-obvious 
//      trick of using: vector<SomeClass>(x).swap(x);
///////////////////////////////////////////////////////////////////////////////

#ifndef MYCSTL_CSTL_VECTOR_H_
#define MYCSTL_CSTL_VECTOR_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "cstl_types.h"
#include "cstl_iterator.h"

#define _GET_VECTOR_TYPE_INFO(pvec_vector) (((meta_t*)pvec_vector)->_t_typeinfo)
#define _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector) \
  (_g_type_register._ptr_types[TYPE_INFO_TYPE_IDS(((meta_t*)pvec_vector)->_t_typeinfo)[0]])
#define _GET_VECTOR_TYPE_SIZE(pvec_vector) \
  (_GET_VECTOR_TYPE_INFO_TYPE(pvec_vector)->_t_typesize)
#define _GET_VECTOR_TYPE_NAME(pvec_vector)\
  get_type_name(_GET_VECTOR_TYPE_INFO_TYPE(pvec_vector)->_t_typeid)
#define _GET_VECTOR_TYPE_BASENAME(pvec_vector)\
  get_type_names(TYPE_INFO_TYPE_IDS((pvec_vector)->_t_typeinfo), (pvec_vector)->_t_typeinfo._t_typeidsize)
#define _GET_VECTOR_TYPE_INIT_FUNCTION(pvec_vector)  _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector)->_t_typeinit
#define _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector) _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector)->_t_typecopy
#define _GET_VECTOR_TYPE_LESS_FUNCTION(pvec_vector) _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector)->_t_typeless
#define _GET_VECTOR_TYPE_DESTROY_FUNCTION(pvec_vector) _GET_VECTOR_TYPE_INFO_TYPE(pvec_vector)->_t_typedestroy

typedef iterator_t vector_iterator_t;
typedef iterator_t vector_reverse_iterator_t;

/*
 * _pby_start          _pby_finish      _pby_endofstorage
 * |                     |               |
 * V                     V               V
 * +-------------------------------------+
 * |    ... data ...     |               |
 * +-------------------------------------+
 * |<--------size()----->|
 * |<---------------capacity()---------->|
 */
typedef struct _tagvector
{
  meta_t meta;
  /* vector core struct pointer */
  _byte_t* _pby_start; /* the start of used space */
  _byte_t* _pby_finish; /* the end of used space */
  _byte_t* _pby_endofstorage; /* the end of capacity space */
} vector_t;

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ VECTOR ITERATOR STARTS ////////////////////////////////////////
/**
 * Create new vector iterator.
 * @param void.
 * @return new vector iterator.
 * @remarks the newly created vector iterator is not a valid iterator, it does not belong to any vector.
 */
#define  create_vector_iterator(it_iter) \
    _VECTOR_ITERATOR_COREPOS((it_iter)) = NULL;\
    _ITERATOR_CONTAINER((it_iter)) = NULL;\
    _VECTOR_ITERATOR_CONTAINER_TYPE((it_iter)) = _VECTOR_CONTAINER;\
    _VECTOR_ITERATOR_ITERATOR_TYPE((it_iter)) = _RANDOM_ACCESS_ITERATOR;

/**
 * Compare two iterators for equality.
 * @param it_first   first iterator.
 * @param it_second  second iterator.
 * @return true if two iterators are equal, otherwise return false.
 * @remarks if two iterators with different container type or iterator type, then behavior is undefined.
 *          if two iterators are not belong to same container, then behavior is undefined.
 */
extern bool vector_iterator_equal(vector_iterator_t* it_first, vector_iterator_t* it_second);

/**
 * Testing of the first iterator is less than the second iterator.
 * @param it_first   first iterator.
 * @param it_second  second iterator.
 * @return true if the first iterator is less than the second one, otherwise return false.
 * @remarks if two iterators with different container type or iterator type, then behavior is undefined.
 *          if two iterators are not belong to same container, then behavior is undefined.
 */
extern bool vector_iterator_less(vector_iterator_t* it_first, vector_iterator_t* it_second);

/**
 * Testing of the first iterator is located in front of the second iterator.
 * @param it_first   first iterator.
 * @param it_second  second iterator.
 * @return true if the first iterator is in front of the second iterator, otherwise return false.
 * @remarks if two iterators with different container type or iterator type, then behavior is undefined.
 *          if two iterators are not belong to same container, then behavior is undefined.
 */
extern bool vector_iterator_before(vector_iterator_t* it_first, vector_iterator_t* it_second);

/**
 * Get iterator reference data.
 * @param it_iter vector iterator.
 * @param pv_value point to buffer that be used to save date.
 * @return void.
 * @remarks it_iter must be valid vector iterator, otherwise the behavior is undefined. if pv_value == NULL,
 *          then the behavior is undefined.
 */
extern void vector_iterator_get_value(vector_iterator_t* it_iter, void* pv_value);

/**
 * Set iterator reference data.
 * @param it_iter vector iterator.
 * @param cpv_value point to buffer that be used to save date.
 * @return void.
 * @remarks it_iter must be valid vector iterator, otherwise the behavior is undefined. if pv_value == NULL,
 *          then the behavior is undefined.
 */
extern void vector_iterator_set_value(vector_iterator_t* it_iter, const void* cpv_value);

/**
 * Get the pointer that point to the iterator reference data.
 * @param it_iter vector iterator.
 * @return data pointer.
 * @remarks it_iter must be valid vector iterator, otherwise the behavior is undefined.
 */
extern void* vector_iterator_get_pointer(vector_iterator_t* it_iter);

/**
 * Get the pointer that point to the iterator reference data, but ignore char*.
 * @param it_iter vector iterator.
 * @return data pointer.
 * @remarks it_iter must be valid vector iterator, otherwise the behavior is undefined.
 */
extern void* vector_iterator_get_pointer_ignore_cstr(vector_iterator_t* it_iter);

/**
 * Get the iterator that reference next data.
 * @param it_iter vector iterator.
 * @remarks it_iter and the returned iterator must be valid vector iterator, otherwise the behavior is undefined.
 */
extern void vector_iterator_next(vector_iterator_t* it_iter);

/**
 * Get the iterator that reference previous data.
 * @param it_iter vector iterator.
 * @remarks it_iter and the returned iterator must be valid vector iterator, otherwise the behavior is undefined.
 */
extern void vector_iterator_prev(vector_iterator_t* it_iter);

/**
 * Get the iterator that reference next n data.
 * @param it_iter vector iterator.
 * @param n_step steps to move.
 * @return next n iterator.
 * @remarks it_iter and the returned iterator must be valid vector iterator, otherwise the behavior is undefined.
 *          if n_step > 0, iterator move to the end of the container. if n_step < 0, iterator move to the begin of
 *          the container. if n_step == 0, iterator dose not move.
 */
extern void vector_iterator_next_n(vector_iterator_t* it_iter, size_t n_step);

/**
 * Get the iterator that reference previous n data.
 * @param it_iter vector iterator.
 * @param n_step steps to move.
 * @return next n iterator.
 * @remarks it_iter and the returned iterator must be valid vector iterator, otherwise the behavior is undefined.
 *          if n_step > 0, iterator move to the begin of the container. if n_step < 0, iterator move to the end of
 *          the container. if n_step == 0, iterator dose not move.
 */
extern void vector_iterator_prev_n(vector_iterator_t* it_iter, size_t n_step);

/**
 * Access iterator reference data randomly with subscript.
 * @param it_iter vector iterator.
 * @param n_index subscript
 * @return reference data.
 * @remarks it_iter must be valid vector iterator, and referenced data must whitin the vector, otherwise the behavior
 *          is undefined. if n_index > 0, iterator move to the begin of the container. if n_index < 0, iterator move to
 *          the end of the container. if n_index == 0, return iterator reference data.
 *  @caution internally forward it_iter and so it will not point to the previous element. create a new itr if you want to leep the old itr
 */
extern void* vector_iterator_at(vector_iterator_t* it_iter, size_t n_index);

/**
 * Calculate the distance between two iterators.
 * @param it_first first vector iterator.
 * @param it_second second vector iterator.
 * @return the distance between two iterators.
 * @remarks the two iterators must be valid vector iterator, otherwist the behavious is undefined. if it_first < it_second,
 *          then return value < 0, if it_first > it_second, then return value > 0, if it_first == it_second, then return
 *          value == 0.
 */
extern size_t vector_iterator_minus(vector_iterator_t* it_first, vector_iterator_t* it_second);

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ VECTOR ITERATOR ENDS ////////////////////////////////////////

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ VECTOR VALIDATION STARTS ////////////////////////////////////////
/**
 * Test iterator referenced data is within the vector.
 * @param cpvec_vector point to vector container.
 * @param it_iter vector iterator.
 * @return if iterator referenced is within the vector, then return true, otherwise return false.
 * @remarks if cpvec_vector == NULL, then the behavior is undefined, the it_iter must be valie vector iterator and
 *          must belong to vector, otherwist the behavior is undefined.
 */
extern bool vector_iterator_valid(const vector_t* cpvec_vector, vector_iterator_t* it_iter);
extern bool vector_iterator_valid_end(const vector_t* cpvec_vector, vector_iterator_t* it_iter);
/**
 * Test vector is initialized by vector initialization functions.
 * @param cpvec_vector  vector container.
 * @return if vector is initialized by vector initialization functions, then return true, else return false.
 * @remarks if cpvec_vector == NULL, then the behavior is undefined.
 */
extern bool vector_is_inited(const vector_t* cpvec_vector);

/**
 * Test the type that saved in the vector container is same.
 * @param cpvec_first first vector.
 * @param cpvec_second second vector.
 * @return if the type is same, return true, else return false.
 * @remarks the two vector must have called vector_ctor_*(),
 */
extern bool vector_is_same_type(const vector_t* cpvec_first, const vector_t* cpvec_second);

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ VECTOR VALIDATION ENDS ////////////////////////////////////////

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ VECTOR STARTS ////////////////////////////////////////
extern void vector_ctor(vector_t* vec, size_t argsize, ...);
extern void vector_ctor_n(vector_t* vec, size_t elesize, size_t argsize, ...);
extern void vector_ctor_n_v(vector_t* vec, size_t elesize, void* val, size_t argsize, ...);
extern void vector_ctor_range(vector_t* vec, forward_iterator_t* first, forward_iterator_t* last);
extern void vector_ctor_range_n(vector_t* pvec_vector, forward_iterator_t* first, size_t size);
extern void vector_ctor_vector(vector_t* vec, vector_t* x);
extern void vector_dtor(vector_t* vec);

extern size_t vector_size(vector_t* cpvec_vector);
extern size_t vector_capacity(vector_t* cpvec_vector);
extern bool empty(vector_t* cpvec_vector);

/**
 * Test the two vectors are equal.
 * @param cpvec_first   first vector container.
 * @param cpvec_second  second vector container.
 * @return if first vector equal to second vector, then return true, else return false.
 * @remarks the two vectors must be initialized, otherwise the behavior is undefined.
 * if the two vectors are not same type, then return false.
 * if cpvec_first == cpvec_second, then return true.
 */
extern bool vector_equal(vector_t* cpvec_first, vector_t* cpvec_second);

/**
 * Assigns new contents to the vector, replacing its current contents,
 * and modifying its size accordingly.
 * @remarks
 * a vector filled with some data and you call an assign on it, this will:
 * destroy all the elements of the vector (their destructor is called) like a call to clear()
 * fill the now-empty vector with n copies of the given object, which must have a copy constructor.
 * So if your class allocates some memory you have to:
 * take care of this in your copy constructor
 * free it in the destructor
 */
extern void vector_assign_n_v(vector_t* pvec,const void* v, size_t n);
extern void vector_assign_range(input_iterator_t* first, input_iterator_t* last);
extern void vector_assign_range_n(input_iterator_t* first, size_t n);

/**
 * a iterator that points just beyond the end of vector container.
 * @param cpvec_vector  vector container.
 * @return a iterator to the end of vector.
 * @remarks if cpvec_vector == NULL, then the behavior is undefined. the vector must be initialized, otherwise the behavior
 *          is undefined.
 */
extern void vector_end(const vector_t* cpvec_vector, vector_iterator_t* it_end);
extern void vector_begin(const vector_t* cpvec_vector, vector_iterator_t* begin);

/**
 * a  iterator that points just beyond the end of vector container.
 * will update end position internally
 * @param cpvec_vector  vector container.
 * @remarks vector_end() has been called to init it_end
 */
extern void vector_end_again(vector_iterator_t* it_end);

/**
 * swap exchanges the contents of two containers.
 * @param x  vector container.
 */
extern void vector_swap(vector_t* pvec_first, vector_t* pvec_second);

extern void vector_erase(random_access_iterator_t* position, bool destruct);
extern void vector_erase_unsort(random_access_iterator_t* position,bool destruct);
extern void vector_erase_range(random_access_iterator_t* first, random_access_iterator_t* last,bool destruct);
extern void vector_erase_range_unsort(random_access_iterator_t* first, random_access_iterator_t* last,bool destruct);
extern void vector_erase_range_n(random_access_iterator_t* first, size_t n,bool destruct);
extern void vector_erase_range__n_unsort(random_access_iterator_t* first, size_t n,bool destruct);

extern void vector_clear(vector_t* pvec);
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ VECTOR ENDS ////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif /* MYCSTL_CSTL_VECTOR_H_ */
