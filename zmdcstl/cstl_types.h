#ifndef _CSTL_TYPES_H_
#define _CSTL_TYPES_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include "cstl_def.h"

#ifndef CSTL_ALIGN_OF
#if   defined(_MSC_VER) && (_MSC_VER < 1700)
// Workaround for this VS 2010 compiler bug: https://connect.microsoft.com/VisualStudio/feedback/details/682695
#define CSTL_ALIGN_OF(...) ( (sizeof(__VA_ARGS__)*0) + (__alignof(__VA_ARGS__)) )
#elif !defined(__GNUC__) || (__GNUC__ >= 3) // GCC 2.x doesn't do __alignof correctly all the time.
#define CSTL_ALIGN_OF __alignof
#else
#define CSTL_ALIGN_OF(type) ((size_t)offsetof(struct{ char c; type m; }, m))
#endif
#endif

// user can override this
#define TYPE_NAME_SIZE 255
#define TYPE_REGISTER_BUCKET_COUNT  128
#define TYPE_ID_SIZE              (sizeof(unsigned char*))

typedef enum
{
  cstl_int8 = 0,
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
  //  cstl_list,
  //  cstl_map,
  //  cstl_hash,
  //  cstl_string,
  default_types_size
} typeid_t;

typedef void (*dtor_t)(void* self);
typedef void (*ctor_default_t)(void* self);
typedef void (*ctor_custom_t)(va_list args, size_t size);
typedef void (*ctor_copy_t)(void* self, void* another);
typedef void (*ctor_move_t)(void* self, void* another);
typedef void (*opt_assign_copy_t)(void* self, void* another);
typedef void (*opt_assign_move_t)(void* self, void* another);
typedef int (*compare_t)(void* self, void* another);

typedef struct _tagtype_t
{
  unsigned char _t_typeid;
  unsigned char _t_typealign;
  unsigned short _t_typesize;
  dtor_t dtor;
  ctor_default_t ctor_default;
  ctor_custom_t ctor_custom;
  ctor_copy_t ctor_copy;
  ctor_move_t ctor_move;
  opt_assign_copy_t opt_assign_copy;
  opt_assign_move_t opt_assign_move;
  compare_t compare;
} type_t;

#define TYPE_INFO_TYPE_ID_FIRST(type_info) ((type_info)._t_typeids[0])
#define TYPE_INFO_TYPE_ID_SIZE(type_info) ((type_info)._t_typeidsize)
#define TYPE_INFO_TYPE_IDS(_t_typeinfo) \
  (((_t_typeinfo)._t_typeidsize) > TYPE_ID_SIZE ? ((_t_typeinfo).typeids_ptr) : ((unsigned char*)&(_t_typeinfo.typeids_ptr)))
#define TYPE_INFO_TYPE_PTR_IDS(_t_typeinfo) \
  (((_t_typeinfo)->_t_typeidsize) > TYPE_ID_SIZE ? ((_t_typeinfo)->typeids_ptr) : ((unsigned char*)&(_t_typeinfo->typeids_ptr)))

typedef struct _tagtype_info_t
{
  unsigned char* typeids_ptr;
  unsigned char _t_typeidsize;
} type_info_t;

typedef struct _tagtype_register_t
{
  type_t** _ptr_types;
  unsigned char _registered_size;
  unsigned char _total_size;
} type_register_t;

void print_type_names(typeid_t typeids[], size_t size);
extern void print_registered_types();

extern type_register_t _g_type_register;
extern void init_types(size_t usertypesize);
extern void destroy_types();
extern typeid_t register_type(size_t typesize, size_t typealign, dtor_t dtor, ctor_default_t ctor_default,
    ctor_custom_t ctor_custom, ctor_copy_t ctor_copy, ctor_move_t ctor_move, opt_assign_copy_t opt_assign_copy,
    opt_assign_move_t opt_assign_move, compare_t compare);
extern bool type_info_is_same(const type_info_t* pt_first, const type_info_t* pt_second);

#ifdef __cplusplus
}
#endif
#endif /* _CSTL_TYPES_H_ */
