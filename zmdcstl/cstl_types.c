#include "cstl_types.h"
#include "cstl_alloc.h"
#include "cstl_types_builtin.h"

/** local constant declaration and local macro section **/
type_register_t _g_type_register = { 0 };

inline static const char* gettypename(typeid_t tid)
{
  switch (tid) {
    case cstl_int8:
      return "cstl_int8";
      break;
    case cstl_uint8:
      return "cstl_uint8";
      break;
    case cstl_int16:
      return "cstl_int16";
      break;
    case cstl_uint16:
      return "cstl_int16";
      break;
    case cstl_int32:
      return "cstl_int16";
      break;
    case cstl_uint32:
      return "cstl_int16";
      break;
    case cstl_int64:
      return "cstl_int16";
      break;
    case cstl_uint64:
      return "cstl_int16";
      break;
    case cstl_float:
      return "cstl_float";
      break;
    case cstl_double:
      return "cstl_double";
      break;

      //@TODO register cstl types
    case cstl_vector:
      return "cstl_vector";
      break;
    default:
      return "error: type id does not exit";
      break;
  }
  return "error: type id does not exit";
}

const char* print_type_name(typeid_t typeid)
{
  const char* str = gettypename(typeid);
  assert(str != NULL);
  return str;
}

void print_type_names(typeid_t typeids[], size_t size)
{
  char buff[256];
  char* buf = buff;
  int n;
  int maxbsize = 256;
  for (int i = 0; i < size; i++)
  {
    n = snprintf(buf, maxbsize, "%s, ", gettypename(i));
    buf += n;
    maxbsize -= n;
  }
  puts(buff);
}

typeid_t register_type(size_t typesize, size_t typealign, dtor_t dtor, ctor_default_t ctor_default,
    ctor_custom_t ctor_custom, ctor_copy_t ctor_copy, ctor_move_t ctor_move, opt_assign_copy_t opt_assign_copy,
    opt_assign_move_t opt_assign_move, compare_t compare)
{
  type_t* pt_type = cstl_alloc(type_t, 1);
  pt_type->_t_typeid = _g_type_register._registered_size;
  pt_type->_t_typesize = typesize;
  pt_type->_t_typealign = typealign;
  pt_type->dtor = dtor;
  pt_type->ctor_default = ctor_default;
  pt_type->ctor_custom = ctor_custom;
  pt_type->ctor_copy = ctor_copy;
  pt_type->ctor_move = ctor_move;
  pt_type->opt_assign_copy = opt_assign_copy;
  pt_type->opt_assign_move = opt_assign_move;
  pt_type->compare = compare;
  _g_type_register._ptr_types[_g_type_register._registered_size] = pt_type;
  _g_type_register._registered_size++;
  return (typeid_t) (_g_type_register._registered_size - 1);
}

void destroy_types()
{
  if (_g_type_register._ptr_types)
  {
    for (int i = 0; i < _g_type_register._total_size; i++)
    {
      if (_g_type_register._ptr_types[i])
        cstl_free(_g_type_register._ptr_types[i]);
    }
    cstl_free(_g_type_register._ptr_types);
    _g_type_register._ptr_types = 0;
  }
}
#define register_ctype_aux(type) \
register_type(sizeof(type), CSTL_ALIGN_OF(type), NULL, NULL, NULL,NULL, NULL, NULL,NULL,_type_less_##type)

void init_types(size_t usertypesize)
{
  if (_g_type_register._ptr_types)
    return;

  if (usertypesize == 0)
    usertypesize = TYPE_REGISTER_BUCKET_COUNT;

  _g_type_register._total_size = usertypesize + (size_t) default_types_size;
  _g_type_register._ptr_types = cstl_alloc(type_t*, _g_type_register._total_size);
  register_ctype_aux(int8_t);
  register_ctype_aux(uint8_t);
  register_ctype_aux(int16_t);
  register_ctype_aux(uint16_t);
  register_ctype_aux(int32_t);
  register_ctype_aux(uint32_t);
  register_ctype_aux(int64_t);
  register_ctype_aux(uint64_t);
  register_ctype_aux(float);
  register_ctype_aux(double);
  register_type(sizeof(void*), CSTL_ALIGN_OF(void*), NULL, NULL, NULL,NULL, NULL, NULL,NULL,_type_less_pointer);

  //@TODO register cstl types

  for (int i = _g_type_register._registered_size; i < _g_type_register._total_size; i++)
    _g_type_register._ptr_types[i] = NULL;
}

bool type_info_is_same(const type_info_t* pt_first, const type_info_t* pt_second)
{
  if (pt_first->_t_typeidsize != pt_second->_t_typeidsize)
    return false;
  unsigned char* firstp = TYPE_INFO_TYPE_PTR_IDS(pt_first);
  unsigned char* secondp = TYPE_INFO_TYPE_PTR_IDS(pt_second);
  for (int i = 0; i < pt_first->_t_typeidsize; i++)
  {
    if (firstp[i] != secondp[i])
      return false;
  }
  return true;
}
