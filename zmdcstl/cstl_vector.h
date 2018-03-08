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
  /* vector core struct pointer */
  _byte_t* _pby_start; /* the start of used space */
  _byte_t* _pby_finish; /* the end of used space */
  _byte_t* _pby_endofstorage; /* the end of capacity space */
} vector_t;

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
