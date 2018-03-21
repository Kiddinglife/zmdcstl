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
  *(bool*) pv_output = memcmp(cpv_first, cpv_second, *(size_t*) pv_output) < 0 ? true : false;
}
void _type_destroy_default(const void* cpv_input, void* pv_output)
{
  void* pv_avoidwarning = NULL;
  assert(cpv_input != NULL && pv_output != NULL);
  pv_avoidwarning = (void*) cpv_input;
  *(bool*) pv_output = true;
}

/* char */
void _type_less_char(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(bool*) pv_output = *(char*) cpv_first < *(char*) cpv_second ? true : false;
}

/* unsigned char */
void _type_less_uchar(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(bool*) pv_output = *(unsigned char*) cpv_first < *(unsigned char*) cpv_second ? true : false;
}

/* short */
void _type_init_short(const void* cpv_input, void* pv_output)
{
  assert(cpv_input != NULL && pv_output != NULL);
  *(short*) cpv_input = 0;
  *(bool*) pv_output = true;
}

void _type_copy_short(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(short*) cpv_first = *(short*) cpv_second;
  *(bool*) pv_output = true;
}

void _type_less_short(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(bool*) pv_output = *(short*) cpv_first < *(short*) cpv_second ? true : false;
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

void _type_less_ushort(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(bool*) pv_output = *(unsigned short*) cpv_first < *(unsigned short*) cpv_second ?
  true :
                                                                                      false;
}

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

void _type_less_int(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(bool*) pv_output = *(int*) cpv_first < *(int*) cpv_second ? true : false;
}

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

void _type_less_uint(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(bool*) pv_output = *(unsigned int*) cpv_first < *(unsigned int*) cpv_second ? true : false;
}

void _type_destroy_uint(const void* cpv_input, void* pv_output)
{
  _type_destroy_default(cpv_input, pv_output);
}

/* long */
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

void _type_less_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(bool*) pv_output = *(long*) cpv_first < *(long*) cpv_second ? true : false;
}

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

void _type_less_ulong(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(bool*) pv_output = *(unsigned long*) cpv_first < *(unsigned long*) cpv_second ? true : false;
}

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

void _type_less_float(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(bool*) pv_output = *(float*) cpv_first - *(float*) cpv_second < -FLT_EPSILON ? true : false;
}

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

void _type_less_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(bool*) pv_output = *(double*) cpv_first - *(double*) cpv_second < -DBL_EPSILON ?
  true :
                                                                                     false;
}

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

void _type_less_long_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(bool*) pv_output = *(long double*) cpv_first - *(long double*) cpv_second < -LDBL_EPSILON ?
  true :
                                                                                                false;
}

void _type_destroy_long_double(const void* cpv_input, void* pv_output)
{
  _type_destroy_default(cpv_input, pv_output);
}

/* bool */
void _type_init_cstl_bool(const void* cpv_input, void* pv_output)
{
  assert(cpv_input != NULL && pv_output != NULL);
  *(bool*) cpv_input = false;
  *(bool*) pv_output = true;
}

void _type_copy_cstl_bool(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(bool*) cpv_first = *(bool*) cpv_second;
  *(bool*) pv_output = true;
}

void _type_less_cstl_bool(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(bool*) pv_output = *(bool*) cpv_first < *(bool*) cpv_second ? true : false;
}

void _type_destroy_cstl_bool(const void* cpv_input, void* pv_output)
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

void _type_less_pointer(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(bool*) pv_output = *(void**) cpv_first < *(void**) cpv_second ? true : false;
}

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

void _type_less_bool(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(bool*) pv_output = *(_Bool*) cpv_first < *(_Bool*) cpv_second ? true : false;
}

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

void _type_less_long_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(bool*) pv_output = *(int64_t*) cpv_first < *(int64_t*) cpv_second ? true : false;
}

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

void _type_less_ulong_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
  assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
  *(bool*) pv_output = *(uint64_t*) cpv_first < *(uint64_t*) cpv_second ? true : false;
}

void _type_destroy_ulong_long(const void* cpv_input, void* pv_output)
{
  _type_destroy_default(cpv_input, pv_output);
}

