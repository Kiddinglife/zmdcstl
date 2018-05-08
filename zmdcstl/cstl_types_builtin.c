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
  assert(cpv_input != NULL && pv_output != NULL);
  *(bool*) pv_output = true;
}

#define define_type_less_ctype(realtype) \
int _type_less_##realtype(void* cpv_first, void* cpv_second)\
{\
  if (*(realtype*) cpv_first < *(realtype*) cpv_second)\
    return -1;\
  else if (*(realtype*) cpv_first > *(realtype*) cpv_second)\
    return 1;\
  else\
    return 0;\
}

define_type_less_ctype(int8_t)
define_type_less_ctype(uint8_t)
define_type_less_ctype(int16_t)
define_type_less_ctype(uint16_t)
define_type_less_ctype(int32_t)
define_type_less_ctype(uint32_t)
define_type_less_ctype(int64_t)
define_type_less_ctype(uint64_t)
define_type_less_ctype(float)
define_type_less_ctype(double)
int _type_less_pointer(void* cpv_first, void* cpv_second)
{
  if (cpv_first < cpv_second)
    return -1;
  else if (cpv_first > cpv_second)
    return 1;
  else
    return 0;
}

