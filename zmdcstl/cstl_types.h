#ifndef _CSTL_TYPES_H_
#define _CSTL_TYPES_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include "cstl_def.h"

// user can override this
#define TYPE_NAME_SIZE 255
#define TYPE_REGISTER_BUCKET_COUNT  64
#define TYPE_ID_SIZE              8

typedef enum {
	cstl_int8t = 0,
	cstl_uint8,
	cstl_int16,
	cstl_uint16,
	cstl_int32,
	cstl_uint32,
	cstl_int64,
	cstl_uint64,
	cstl_float,
	cstl_double,
	cstl_void_pt,

	cstl_vector,
	cstl_list,
	cstl_map,
	cstl_hash,
	cstl_string,
} typeid_t;

typedef enum {
	_TYPE_STYLE_POD = 0,
	_TYPE_STYLE_CSTL,
	_TYPE_STYLE_USER_DEFINED,
	_TYPE_STYLE_INVALID
} typestyle_t;

/*
 * Type definition of unary function and binary function.
 * Note: The last parameter is for output
 */
typedef void (*unary_function_t)(const void* in, void* out);
typedef void (*binary_function_t)(const void* in, const void* in_, void* out);
typedef unary_function_t ufun_t;
typedef binary_function_t bfun_t;

typedef struct {
	unsigned char _t_typeid;
	unsigned char _t_typealign;
	unsigned short _t_typesize; /* type size */
	unsigned char _t_style; /* type style */
	ufun_t _t_typeinit; /* if null, use bzero */
	ufun_t _t_typedestroy; /* if null, do nothing */
	bfun_t _t_typecopy; /* if null, use memcpy*/
	bfun_t _t_typeless; /* if null, use memcmp*/
} type_t;

typedef struct {
	unsigned char _t_typeids[TYPE_ID_SIZE];
	unsigned char _t_typeidsize;
	type_t* _pt_type;
} type_info_t;

extern type_t* _apt_bucket[TYPE_REGISTER_BUCKET_COUNT];
extern void show_registered_types();
extern void init_types(void);
extern const char* get_type_name(typeid_t typeid);
extern const char* get_type_names(typeid_t typeids[], size_t size);
extern bool type_info_is_same(const type_info_t* pt_first,
		const type_info_t* pt_second);

#ifdef __cplusplus
}
#endif
#endif /* _CSTL_TYPES_H_ */
