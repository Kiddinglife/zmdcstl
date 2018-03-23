#include "cstl_types_builtin.h"
#include "cstl_def.h"

/* default copy, less, and destroy function */
void _type_init_default(const void* cpv_input, void* pv_output)
{
  assert(cpv_input != NULL && pv_output != NULL);
  memset((void*) cpv_input, 0x00, *(size_t*) pv_output);
  *(bool*) pv_output = true;
}
void _type_copy_default(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  memcpy((void*) cpv_first, cpv_second, *(size_t*) pv_output);
  *(bool*) pv_output = true;
}
void _type_less_default(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(char*) pv_output = memcmp(cpv_first, cpv_second, *(size_t*) pv_output);
}
void _type_destroy_default(const void* cpv_input, void* pv_output)
{
  void* pv_avoidwarning = NULL;
  assert(cpv_input != NULL && pv_output != NULL);
  pv_avoidwarning = (void*) cpv_input;
  *(bool*) pv_output = true;
}

#define define_type_less_ctype(type, realtype) \
void _type_less_##type(const void* cpv_first, const void* cpv_second, void* pv_output)\
{\
  if (*(realtype*) cpv_first < *(realtype*) cpv_second)\
    *(char*) pv_output = -1;\
  else if (*(realtype*) cpv_first > *(realtype*) cpv_second)\
    *(char*) pv_output = 1;\
  else\
    *(char*) pv_output = 0;\
}

define_type_less_ctype(char, char)
define_type_less_ctype(uchar, unsigned char)

define_type_less_ctype(short, short)
void _type_copy_short(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(short*) cpv_first = *(short*) cpv_second;
  *(bool*) pv_output = true;
}
void _type_destroy_short(const void* cpv_input, void* pv_output)
{
  _type_destroy_default(cpv_input, pv_output);
}

/* unsigned short */
void _type_init_ushort(const void* cpv_input, void* pv_output)
{
  assert(cpv_input != NULL && pv_output != NULL);
  *(unsigned short*) cpv_input = 0;
  *(bool*) pv_output = true;
}
void _type_copy_ushort(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(unsigned short*) cpv_first = *(unsigned short*) cpv_second;
  *(bool*) pv_output = true;
}
define_type_less_ctype(ushort, unsigned short)
void _type_destroy_ushort(const void* cpv_input, void* pv_output)
{
  _type_destroy_default(cpv_input, pv_output);
}

/* int */
void _type_init_int(const void* cpv_input, void* pv_output)
{
  assert(cpv_input != NULL && pv_output != NULL);
  *(int*) cpv_input = 0;
  *(bool*) pv_output = true;
}
void _type_copy_int(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(int*) cpv_first = *(int*) cpv_second;
  *(bool*) pv_output = true;
}
define_type_less_ctype(int, int)
void _type_destroy_int(const void* cpv_input, void* pv_output)
{
  _type_destroy_default(cpv_input, pv_output);
}

/* unsigned int */
void _type_init_uint(const void* cpv_input, void* pv_output)
{
  assert(cpv_input != NULL && pv_output != NULL);
  *(unsigned int*) cpv_input = 0;
  *(bool*) pv_output = true;
}
void _type_copy_uint(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(unsigned int*) cpv_first = *(unsigned int*) cpv_second;
  *(bool*) pv_output = true;
}
define_type_less_ctype(uint, unsigned int)
void _type_destroy_uint(const void* cpv_input, void* pv_output)
{
  _type_destroy_default(cpv_input, pv_output);
}

void _type_init_long(const void* cpv_input, void* pv_output)
{
  assert(cpv_input != NULL && pv_output != NULL);
  *(long*) cpv_input = 0;
  *(bool*) pv_output = true;
}
void _type_copy_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(long*) cpv_first = *(long*) cpv_second;
  *(bool*) pv_output = true;
}
define_type_less_ctype(long, long)
void _type_destroy_long(const void* cpv_input, void* pv_output)
{
  _type_destroy_default(cpv_input, pv_output);
}

/* unsigned long */
void _type_init_ulong(const void* cpv_input, void* pv_output)
{
  assert(cpv_input != NULL && pv_output != NULL);
  *(unsigned long*) cpv_input = 0;
  *(bool*) pv_output = true;
}
void _type_copy_ulong(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(unsigned long*) cpv_first = *(unsigned long*) cpv_second;
  *(bool*) pv_output = true;
}
define_type_less_ctype(ulong, unsigned long)
void _type_destroy_ulong(const void* cpv_input, void* pv_output)
{
  _type_destroy_default(cpv_input, pv_output);
}

/* float */
void _type_init_float(const void* cpv_input, void* pv_output)
{
  assert(cpv_input != NULL && pv_output != NULL);
  *(float*) cpv_input = 0.0;
  *(bool*) pv_output = true;
}
void _type_copy_float(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(float*) cpv_first = *(float*) cpv_second;
  *(bool*) pv_output = true;
}
define_type_less_ctype(float, float)
void _type_destroy_float(const void* cpv_input, void* pv_output)
{
  _type_destroy_default(cpv_input, pv_output);
}

/* double */
void _type_init_double(const void* cpv_input, void* pv_output)
{
  assert(cpv_input != NULL && pv_output != NULL);
  *(double*) cpv_input = 0.0;
  *(bool*) pv_output = true;
}
void _type_copy_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(double*) cpv_first = *(double*) cpv_second;
  *(bool*) pv_output = true;
}
define_type_less_ctype(double, double)
void _type_destroy_double(const void* cpv_input, void* pv_output)
{
  _type_destroy_default(cpv_input, pv_output);
}

/* long double */
void _type_init_long_double(const void* cpv_input, void* pv_output)
{
  assert(cpv_input != NULL && pv_output != NULL);
  *(long double*) cpv_input = 0.0;
  *(bool*) pv_output = true;
}
void _type_copy_long_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(long double*) cpv_first = *(long double*) cpv_second;
  *(bool*) pv_output = true;
}
define_type_less_ctype(long_double, long double)
void _type_destroy_long_double(const void* cpv_input, void* pv_output)
{
  _type_destroy_default(cpv_input, pv_output);
}

/* void* */
void _type_init_pointer(const void* cpv_input, void* pv_output)
{
  assert(cpv_input != NULL && pv_output != NULL);
  *(void**) cpv_input = NULL;
  *(bool*) pv_output = true;
}
void _type_copy_pointer(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(void**) cpv_first = *(void**) cpv_second;
  *(bool*) pv_output = true;
}
define_type_less_ctype(pointer, void*)
void _type_destroy_pointer(const void* cpv_input, void* pv_output)
{
  _type_destroy_default(cpv_input, pv_output);
}

/* _Bool */
void _type_init_bool(const void* cpv_input, void* pv_output)
{
  assert(cpv_input != NULL && pv_output != NULL);
  *(_Bool*) cpv_input = false;
  *(bool*) pv_output = true;
}
void _type_copy_bool(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(_Bool*) cpv_first = *(_Bool*) cpv_second;
  *(bool*) pv_output = true;
}
define_type_less_ctype(bool, bool)
void _type_destroy_bool(const void* cpv_input, void* pv_output)
{
  _type_destroy_default(cpv_input, pv_output);
}

/* int64_t */
void _type_init_long_long(const void* cpv_input, void* pv_output)
{
  assert(cpv_input != NULL && pv_output != NULL);
  *(int64_t*) cpv_input = false;
  *(bool*) pv_output = true;
}
void _type_copy_long_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(int64_t*) cpv_first = *(int64_t*) cpv_second;
  *(bool*) pv_output = true;
}
define_type_less_ctype(long_long, long long)
void _type_destroy_long_long(const void* cpv_input, void* pv_output)
{
  _type_destroy_default(cpv_input, pv_output);
}

/* uint64_t */
void _type_init_ulong_long(const void* cpv_input, void* pv_output)
{
  assert(cpv_input != NULL && pv_output != NULL);
  *(uint64_t*) cpv_input = false;
  *(bool*) pv_output = true;
}
void _type_copy_ulong_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(uint64_t*) cpv_first = *(uint64_t*) cpv_second;
  *(bool*) pv_output = true;
}
define_type_less_ctype(ulong_long, unsigned long long)
void _type_destroy_ulong_long(const void* cpv_input, void* pv_output)
{
  _type_destroy_default(cpv_input, pv_output);
}

