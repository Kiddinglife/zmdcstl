///////////////////////////////////////////////////////////////////////////////
// This file implements a vector (array-like container), much like the C++ std::vector.
// The primary distinctions between this vector and std::vector are:
//    - vector has a couple extension functions that increase performance.
//    - vector can contain objects with alignment requirements. std::vector 
//      cannot do so without a bit of tedious non-portable effort.
//    - vector supports debug memory naming natively.
//    - vector is easier to read, debug, and visualize.
//    - vector is savvy to an environment that doesn't have exception handling,
//      as is sometimes the case with console or embedded environments.
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

typedef iterator_t vector_iterator_t;
typedef iterator_t vector_reverse_iterator_t;

#define _GET_VECTOR_TYPE_SIZE(pvec_vector)             ((pvec_vector)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_VECTOR_TYPE_NAME(pvec_vector)             get_type_name((pvec_vector)->_t_typeinfo._pt_type->_t_typeid)
#define _GET_VECTOR_TYPE_BASENAME(pvec_vector)         get_type_names((pvec_vector)->_t_typeinfo._t_typeids, (pvec_vector)->_t_typeinfo._t_typeidsize)
#define _GET_VECTOR_TYPE_INIT_FUNCTION(pvec_vector)    ((pvec_vector)->_t_typeinfo._pt_type->_t_typeinit)
#define _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)    ((pvec_vector)->_t_typeinfo._pt_type->_t_typecopy)
#define _GET_VECTOR_TYPE_LESS_FUNCTION(pvec_vector)    ((pvec_vector)->_t_typeinfo._pt_type->_t_typeless)
#define _GET_VECTOR_TYPE_DESTROY_FUNCTION(pvec_vector) ((pvec_vector)->_t_typeinfo._pt_type->_t_typedestroy)
#define _GET_VECTOR_TYPE_STYLE(pvec_vector)            ((pvec_vector)->_t_typeinfo._t_type->_t_style)

/*
 * vector_t
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
  /* element type information */
  type_info_t _t_typeinfo;
  iterator_fix_t _t_iterator_fix;
  /* vector core struct pointer */
  _byte_t* _pby_start; /* the start of used space */
  _byte_t* _pby_finish; /* the end of used space */
  _byte_t* _pby_endofstorage; /* the end of capacity space */
} vector_t;

/**
 * Test vector is initialized by vector initialization functions.
 * @param cpvec_vector  vector container.
 * @return if vector is initialized by vector initialization functions, then return true, else return false.
 * @remarks if cpvec_vector == NULL, then the behavior is undefined.
 */
extern bool vector_is_inited(const vector_t* cpvec_vector);

/**
 * Test iterator referenced data is within the vector.
 * @param cpvec_vector point to vector container.
 * @param it_iter vector iterator.
 * @return if iterator referenced is within the vector, then return true, otherwise return false.
 * @remarks if cpvec_vector == NULL, then the behavior is undefined, the it_iter must be valie vector iterator and
 *          must belong to vector, otherwist the behavior is undefined.
 */
extern bool vector_iterator_valid(const vector_t* cpvec_vector, vector_iterator_t* it_iter);

extern void vector_iterator_next(vector_iterator_t* it_iter);

/**
 * Create new vector iterator.
 * @param void.
 * @return new vector iterator.
 * @remarks the newly created vector iterator is not a valid iterator, it does not belong to any vector.
 */
extern void create_vector_iterator(vector_iterator_t* it);

/**
 * Create vector container.
 * @param s_typename element type name.
 * @return if create vector successfully, then return vector pointer, else return NULL.
 * @remarks if s_typename == NULL, then the behavior is undefined. s_typename should be C builtin type name,
 *          libcstl builtin typename or registed user defined type name, otherwise the function will return NULL.
 */
extern vector_t* create_vector(int size, ...);

#ifdef __cplusplus
}
#endif

#endif /* MYCSTL_CSTL_VECTOR_H_ */
