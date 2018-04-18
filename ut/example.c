#include "greatest.h"
#include "../zmdcstl/cstl_alloc.h"
#include "../zmdcstl/cstl_vector.h"

typedef struct
{
  int a;
  // no deep copy and so copy function cam be NULL
  void* b;
  char c[32];
} user_defined_type_init0_destroy0_copy0_less;
static typeid_t user_defined_pod_id;
static void func_less_user_defined_type_init0_destroy0_copy0_less(const void* in, const void* in_, void* out)
{
  int a = ((user_defined_type_init0_destroy0_copy0_less*) in)->a;
  int b = ((user_defined_type_init0_destroy0_copy0_less*) in_)->a;
  if (a < b)
    *(char*) out = -1;
  else if (a > b)
    *(char*) out = 1;
  else
    *(char*) out = 0;
}

typedef struct
{
  int a;
  // no deep copy and so copy function cam be NULL
  int* b;
  char c[32];
} user_defined_type_init_destroy_copy_less;
static typeid_t user_defined_non_pod_id;
static void func_init_user_defined_type_init_destroy_copy_less(const void* in, void* out)
{
  ((user_defined_type_init_destroy_copy_less*) in)->b = cstl_alloc(int, 32);
  //printf("init alloc = %x\n", ((user_defined_type_init_destroy_copy_less*) in)->b);
  memset(((user_defined_type_init_destroy_copy_less*) in)->b, 0, 32 * sizeof(int));
  ((user_defined_type_init_destroy_copy_less*) in)->a = 32;
  memset(((user_defined_type_init_destroy_copy_less*) in)->c, 0, 32);
}
static void func_copy_user_defined_type_init_destroy_copy_less(const void* in, const void* in_, void* is_copy__assign)
{
  //assert(in != in_);
  if (in == in_)
    return;
  if (*(bool*) is_copy__assign)
    cstl_free(((user_defined_type_init_destroy_copy_less* )in)->b);

  ((user_defined_type_init_destroy_copy_less*) in)->b = cstl_alloc(int,
      ((user_defined_type_init_destroy_copy_less* )in_)->a);
  //printf("copy alloc = %x\n", ((user_defined_type_init_destroy_copy_less*) in)->b);
  cstl_memcpy(((user_defined_type_init_destroy_copy_less*) in)->b, ((user_defined_type_init_destroy_copy_less*) in_)->b,
      ((user_defined_type_init_destroy_copy_less*) in_)->a * sizeof(int));
  ((user_defined_type_init_destroy_copy_less*) in)->a = ((user_defined_type_init_destroy_copy_less*) in_)->a;
  cstl_memcpy(((user_defined_type_init_destroy_copy_less*) in)->c, ((user_defined_type_init_destroy_copy_less*) in_)->c,
      32);
}
static void func_destroy_user_defined_type_init_destroy_copy_less(const void* in, void* out)
{
  //printf("destroy alloc = %x\n", ((user_defined_type_init_destroy_copy_less*) in)->b);
  cstl_free(((user_defined_type_init_destroy_copy_less* )in)->b);
}
static void func_less_user_defined_type_init_destroy_copy_less(const void* in, const void* in_, void* out)
{
  int a = ((user_defined_type_init0_destroy0_copy0_less*) in)->a;
  int b = ((user_defined_type_init0_destroy0_copy0_less*) in_)->a;
  if (a < b)
    *(char*) out = -1;
  else if (a > b)
    *(char*) out = 1;
  else
    *(char*) out = 0;
}

TEST test_cstl_alloc_free()
{
  int* x;
  for (int i = 0; i < 1000000; i++)
  {
    x = (int*) cstl_alloc(int, 2);
    *x = 100;
    *(x + 1) = 200;
    ASSERT_EQ(*x, 100);
    ASSERT_EQ(*(x + 1), 200);
    cstl_free(x);
  }
  PASS();
}

TEST test_vector_ctor_scalar_type()
{
  vector_t pvec_vector = { 0 };
  vector_ctor(&pvec_vector, 1, cstl_uint32);
  ASSERT_EQ(pvec_vector._pby_finish, NULL);
  ASSERT_EQ(pvec_vector._pby_start, NULL);
  ASSERT_EQ(pvec_vector._pby_endofstorage, NULL);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, cstl_uint32);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);
  vector_dtor(&pvec_vector);
  PASS();
}
TEST test_vector_ctor_user_defined_pod()
{
  vector_t pvec_vector;
  vector_ctor(&pvec_vector, 1, user_defined_pod_id);
  ASSERT_EQ(pvec_vector._pby_finish, NULL);
  ASSERT_EQ(pvec_vector._pby_start, NULL);
  ASSERT_EQ(pvec_vector._pby_endofstorage, NULL);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, user_defined_pod_id);
  ASSERT_EQ_FMT(1, pvec_vector.meta._t_typeinfo._t_typeidsize, "%d");
  vector_dtor(&pvec_vector);
  PASS();
}
TEST test_vector_ctor_user_defined_non_pod()
{
  vector_t pvec_vector;
  vector_ctor(&pvec_vector, 1, user_defined_non_pod_id);
  ASSERT_EQ(pvec_vector._pby_finish, NULL);
  ASSERT_EQ(pvec_vector._pby_start, NULL);
  ASSERT_EQ(pvec_vector._pby_endofstorage, NULL);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, user_defined_non_pod_id);
  ASSERT_EQ_FMT(1, pvec_vector.meta._t_typeinfo._t_typeidsize, "%d");
  vector_dtor(&pvec_vector);
  PASS();
}
TEST test_vector_ctor_n_scalar_type()
{
  vector_t pvec_vector;
  vector_ctor_n(&pvec_vector, 1, 1, cstl_uint32);
  ASSERT_EQ(pvec_vector._pby_endofstorage, pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start,
      _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_FALSE(pvec_vector._pby_endofstorage == NULL);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, cstl_uint32);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);
  vector_dtor(&pvec_vector);
  PASS();
}
TEST test_vector_ctor_n_user_defined_pod()
{
  vector_t pvec_vector;
  vector_ctor_n(&pvec_vector, 10, 1, user_defined_pod_id);
  ASSERT_EQ(pvec_vector._pby_endofstorage, pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start, 10 * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_FALSE(pvec_vector._pby_endofstorage == NULL);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, user_defined_pod_id);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);
  vector_dtor(&pvec_vector);
  PASS();
}
TEST test_vector_ctor_n_user_defined_non_pod()
{
  vector_t pvec_vector;
  vector_ctor_n(&pvec_vector, 10, 1, user_defined_non_pod_id);
  ASSERT_EQ(pvec_vector._pby_endofstorage, pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start, 10 * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, user_defined_non_pod_id);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);
  vector_dtor(&pvec_vector);
  PASS();
}
TEST test_vector_ctor_n_v_scalar_type()
{
  vector_t pvec_vector;
  unsigned int v = 100;
  size_t elesize = 100;
  vector_ctor_n_v(&pvec_vector, elesize, &v, 1, cstl_uint32);
  ASSERT_EQ(pvec_vector._pby_endofstorage, pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start,
      elesize * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_FALSE(pvec_vector._pby_endofstorage == NULL);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, cstl_uint32);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);
  unsigned char* tmp = pvec_vector._pby_start;
  for (; elesize > 0; elesize--)
  {
    ASSERT_EQ(*(unsigned int*)tmp, v);
    tmp += _GET_VECTOR_TYPE_SIZE(&pvec_vector);
  }

  vector_dtor(&pvec_vector);
  PASS();
}
TEST test_vector_ctor_n_v_user_defined_pod()
{
  vector_t pvec_vector;
  user_defined_type_init0_destroy0_copy0_less v;
  v.a = 100;
  v.b = 0;
  v.c[0] = 100;
  size_t elesize = 100;
  vector_ctor_n_v(&pvec_vector, elesize, &v, 1, user_defined_pod_id);

  ASSERT_EQ(pvec_vector._pby_endofstorage, pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start, elesize * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_FALSE(pvec_vector._pby_endofstorage == NULL);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, user_defined_pod_id);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);
  unsigned char* tmp = pvec_vector._pby_start;
  user_defined_type_init0_destroy0_copy0_less* vptr;
  for (; elesize > 0; elesize--)
  {
    vptr = (user_defined_type_init0_destroy0_copy0_less*) tmp;
    ASSERT_EQ(vptr->a, 100);
    ASSERT_EQ(vptr->b, 0);
    ASSERT_EQ(vptr->c[0], 100);
    tmp += _GET_VECTOR_TYPE_SIZE(&pvec_vector);
  }

  vector_dtor(&pvec_vector);
  PASS();
}
TEST test_vector_ctor_n_v_user_defined_non_pod()
{
  vector_t pvec_vector;
  user_defined_type_init_destroy_copy_less v;
  v.a = 100;
  v.b = cstl_alloc(int, v.a);
  v.c[0] = 100;
  size_t elesize = v.a;
  CHECK_CALL(test_vector_ctor_n_user_defined_non_pod());
  vector_ctor_n_v(&pvec_vector, elesize, &v, 1, user_defined_non_pod_id);

  ASSERT_EQ(pvec_vector._pby_endofstorage, pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start, elesize * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_FALSE(pvec_vector._pby_endofstorage == NULL);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, user_defined_non_pod_id);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);
  unsigned char* tmp = pvec_vector._pby_start;
  user_defined_type_init_destroy_copy_less* vptr;
  for (; elesize > 0; elesize--)
  {
    vptr = (user_defined_type_init_destroy_copy_less*) tmp;
    ASSERT_EQ(vptr->a, 100);
    ASSERT_FALSE(vptr->b == NULL);
    ASSERT_EQ(vptr->c[0], 100);
    tmp += _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize;
  }

  cstl_free(v.b);
  vector_dtor(&pvec_vector);
  PASS();
}
TEST test_vector_ctor_vec_scalar_type()
{
  vector_t pvec_vector_;
  unsigned int v = 100;
  size_t elesize = 100;
  vector_ctor_n_v(&pvec_vector_, elesize, &v, 1, cstl_uint32);

  vector_t pvec_vector;
  vector_ctor_vector(&pvec_vector, &pvec_vector_);
  vector_ctor(&pvec_vector, 1, cstl_uint32);

  // as nothing pushed to pvec_vector_ and so pvec_vector should be also empty
  ASSERT_EQ(pvec_vector._pby_finish, NULL);
  ASSERT_EQ(pvec_vector._pby_start, NULL);
  ASSERT_EQ(pvec_vector._pby_endofstorage, NULL);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, cstl_uint32);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);

  vector_dtor(&pvec_vector);
  vector_dtor(&pvec_vector_);
  PASS();
}
TEST test_vector_ctor_vec_user_defined_pod()
{
  CHECK_CALL(test_vector_ctor_n_v_user_defined_pod());

  vector_t pvec_vector_;
  size_t elesize = 100;
  user_defined_type_init0_destroy0_copy0_less v;
  v.a = 100;
  v.b = 0;
  v.c[0] = 100;
  vector_ctor_n_v(&pvec_vector_, elesize, &v, 1, user_defined_pod_id);

  vector_t pvec_vector;
  vector_ctor_vector(&pvec_vector, &pvec_vector_);

  ASSERT_EQ(pvec_vector._pby_endofstorage, pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start,
      elesize * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, user_defined_pod_id);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);
  unsigned char* tmp = pvec_vector._pby_start;
  user_defined_type_init0_destroy0_copy0_less* vptr;
  for (; elesize > 0; elesize--)
  {
    vptr = (user_defined_type_init0_destroy0_copy0_less*) tmp;
    ASSERT_EQ_FMT(100, vptr->a, "%d");
    ASSERT_EQ(0, vptr->b);
    ASSERT_EQ_FMT(100, vptr->c[0], "%d");
    tmp += _GET_VECTOR_TYPE_SIZE(&pvec_vector);
  }

  vector_dtor(&pvec_vector);
  vector_dtor(&pvec_vector_);
  PASS();
}
TEST test_vector_ctor_range_scalar_type()
{
  vector_t pvec_vector;
  unsigned int v = 100;
  size_t elesize = 100;
  size_t copysize = 5;

  vector_ctor_n_v(&pvec_vector, elesize, &v, 1, cstl_uint32);

  // first = index50 last = index55
  random_access_iterator_t first;
  vector_begin(&pvec_vector, &first);
  vector_iterator_next_n(&first, elesize / 2);
  random_access_iterator_t last = first;
  vector_iterator_next_n(&last, copysize);

  vector_t pvec_vector_;
  vector_ctor_range(&pvec_vector_, &first, &last);

  ASSERT_EQ(pvec_vector_._pby_endofstorage, pvec_vector_._pby_finish);
  ASSERT_EQ(pvec_vector_._pby_endofstorage - pvec_vector_._pby_start, copysize * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector_)->_t_typesize);
  ASSERT_FALSE(pvec_vector_._pby_endofstorage == NULL);
  ASSERT_EQ(pvec_vector_.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector_)->_t_typeid, cstl_uint32);
  ASSERT_EQ(pvec_vector_.meta._t_typeinfo._t_typeidsize, 1);
  unsigned char* tmp = pvec_vector_._pby_start;
  for (; copysize > 0; copysize--)
  {
    ASSERT_EQ(*(unsigned int*)tmp, v);
    tmp += _GET_VECTOR_TYPE_SIZE(&pvec_vector_);
  }

  vector_dtor(&pvec_vector);
  vector_dtor(&pvec_vector_);
  PASS();
}
TEST test_vector_ctor_range_user_defined_pod()
{
  vector_t pvec_vector;
  size_t elesize = 100;
  user_defined_type_init0_destroy0_copy0_less v;
  v.a = 100;
  v.b = 0;
  v.c[0] = 100;
  CHECK_CALL(test_vector_ctor_n_v_user_defined_pod());
  vector_ctor_n_v(&pvec_vector, elesize, &v, 1, user_defined_pod_id);

  size_t copysize = 5;
  // first = index50 last = index55
  random_access_iterator_t first;
  vector_begin(&pvec_vector, &first);
  vector_iterator_next_n(&first, elesize / 2);
  random_access_iterator_t last = first;
  vector_iterator_next_n(&last, copysize);

  vector_t pvec_vector_;
  vector_ctor_range(&pvec_vector_, &first, &last);

  ASSERT_EQ(pvec_vector_._pby_endofstorage, pvec_vector_._pby_finish);
  ASSERT_EQ(pvec_vector_._pby_endofstorage - pvec_vector_._pby_start, copysize * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector_)->_t_typesize);
  ASSERT_FALSE(pvec_vector_._pby_endofstorage == NULL);
  ASSERT_EQ(pvec_vector_.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector_)->_t_typeid, user_defined_pod_id);
  ASSERT_EQ(pvec_vector_.meta._t_typeinfo._t_typeidsize, 1);
  unsigned char* tmp = pvec_vector_._pby_start;
  user_defined_type_init0_destroy0_copy0_less* vptr;
  for (; copysize > 0; copysize--)
  {
    vptr = (user_defined_type_init0_destroy0_copy0_less*) tmp;
    ASSERT_EQ_FMT(100, vptr->a, "%d");
    ASSERT_EQ(0, vptr->b);
    ASSERT_EQ_FMT(100, vptr->c[0], "%d");
    tmp += _GET_VECTOR_TYPE_SIZE(&pvec_vector);
  }

  vector_dtor(&pvec_vector);
  vector_dtor(&pvec_vector_);
  PASS();
}
TEST test_vector_ctor_range_user_defined_non_pod()
{
  vector_t pvec_vector;
  user_defined_type_init_destroy_copy_less v;
  v.a = 100;
  v.b = cstl_alloc(int, v.a);
  v.c[0] = 100;
  size_t elesize = v.a;
  CHECK_CALL(test_vector_ctor_n_v_user_defined_pod());
  vector_ctor_n_v(&pvec_vector, elesize, &v, 1, user_defined_non_pod_id);

  size_t copysize = 50;
  // first = index50 last = index55
  random_access_iterator_t first;
  vector_begin(&pvec_vector, &first);
  vector_iterator_next_n(&first, elesize / 2);
  random_access_iterator_t last = first;
  vector_iterator_next_n(&last, copysize);

  vector_t pvec_vector_;
  vector_ctor_range(&pvec_vector_, &first, &last);

  ASSERT_EQ(pvec_vector_._pby_endofstorage, pvec_vector_._pby_finish);
  ASSERT_EQ(pvec_vector_._pby_endofstorage - pvec_vector_._pby_start, copysize * _GET_VECTOR_TYPE_SIZE(&pvec_vector_));
  ASSERT_FALSE(pvec_vector_._pby_endofstorage == NULL);
  ASSERT_EQ(pvec_vector_.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector_)->_t_typeid, user_defined_non_pod_id);
  ASSERT_EQ(pvec_vector_.meta._t_typeinfo._t_typeidsize, 1);
  unsigned char* tmp = pvec_vector_._pby_start;
  user_defined_type_init_destroy_copy_less* vptr;
  for (; copysize > 0; copysize--)
  {
    vptr = (user_defined_type_init_destroy_copy_less*) tmp;
    ASSERT_EQ(vptr->a, 100);
    ASSERT_FALSE(vptr->b == NULL);
    ASSERT_EQ(vptr->c[0], 100);
    tmp += _GET_VECTOR_TYPE_SIZE(&pvec_vector_);
  }

  cstl_free(v.b);
  vector_dtor(&pvec_vector);
  vector_dtor(&pvec_vector_);
  PASS();
}
TEST test_vector_ctor_range_n_user_defined_non_pod()
{
  vector_t pvec_vector;
  user_defined_type_init_destroy_copy_less v;
  v.a = 100;
  v.b = cstl_alloc(int, v.a);
  v.c[0] = 100;
  size_t elesize = v.a;
  CHECK_CALL(test_vector_ctor_n_v_user_defined_pod());
  vector_ctor_n_v(&pvec_vector, elesize, &v, 1, user_defined_non_pod_id);

  size_t copysize = 50;
  random_access_iterator_t first;
  first._pt_container = &pvec_vector;
  _VECTOR_ITERATOR_COREPOS(&first) = pvec_vector._pby_start + 20 * _GET_VECTOR_TYPE_SIZE(&pvec_vector);

  vector_t pvec_vector_;
  vector_ctor_range_n(&pvec_vector_, &first, copysize);

  ASSERT_EQ(pvec_vector_._pby_endofstorage, pvec_vector_._pby_finish);
  ASSERT_EQ(pvec_vector_._pby_endofstorage - pvec_vector_._pby_start, copysize * _GET_VECTOR_TYPE_SIZE(&pvec_vector_));
  ASSERT_FALSE(pvec_vector_._pby_endofstorage == NULL);
  ASSERT_EQ(pvec_vector_.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector_)->_t_typeid, user_defined_non_pod_id);
  ASSERT_EQ(pvec_vector_.meta._t_typeinfo._t_typeidsize, 1);
  unsigned char* tmp = pvec_vector_._pby_start;
  user_defined_type_init_destroy_copy_less* vptr;
  for (; copysize > 0; copysize--)
  {
    vptr = (user_defined_type_init_destroy_copy_less*) tmp;
    ASSERT_EQ(vptr->a, 100);
    ASSERT_FALSE(vptr->b == NULL);
    ASSERT_EQ(vptr->c[0], 100);
    tmp += _GET_VECTOR_TYPE_SIZE(&pvec_vector_);
  }

  cstl_free(v.b);
  vector_dtor(&pvec_vector);
  vector_dtor(&pvec_vector_);
  PASS();
}
TEST test_vector_size()
{
  vector_t pvec_vector;

  vector_ctor(&pvec_vector, 1, user_defined_pod_id);
  ASSERT_EQ(vector_size(&pvec_vector), 0);
  vector_dtor(&pvec_vector);

  size_t elesize = 100;
  vector_ctor_n(&pvec_vector, elesize, 1, user_defined_pod_id);
  ASSERT_EQ(vector_size(&pvec_vector), elesize);
  vector_dtor(&pvec_vector);

  PASS();
}
TEST test_vector_equal()
{
  vector_t pvec_vector;
  vector_t pvec_vector1;
  bool ret;

  // same vector
  vector_ctor(&pvec_vector, 1, user_defined_pod_id);
  vector_ctor(&pvec_vector1, 1, user_defined_pod_id);
  ASSERT_EQ(vector_equal(&pvec_vector, &pvec_vector), true);

  // size not equal
  vector_ctor_n(&pvec_vector, 10, 1, user_defined_pod_id);
  vector_ctor(&pvec_vector1, 1, user_defined_pod_id);
  ret = vector_equal(&pvec_vector, &pvec_vector1);
  ASSERT_EQ(ret, false);
  vector_dtor(&pvec_vector);
  vector_dtor(&pvec_vector1);

  // same elements
  vector_ctor_n(&pvec_vector, 100, 1, user_defined_pod_id);
  vector_ctor_n(&pvec_vector1, 100, 1, user_defined_pod_id);
  bool is_equal = vector_equal(&pvec_vector, &pvec_vector1);
  ASSERT_EQ(is_equal, true);
  vector_dtor(&pvec_vector);
  vector_dtor(&pvec_vector1);

  // not same eles
  size_t elesize = 100;
  user_defined_type_init0_destroy0_copy0_less v;
  v.a = 100;
  v.b = 0;
  v.c[0] = 100;
  vector_ctor_n_v(&pvec_vector, elesize, &v, 1, user_defined_pod_id);
  v.a = 0;
  vector_ctor_n_v(&pvec_vector1, elesize, &v, 1, user_defined_pod_id);
  ASSERT_EQ(vector_equal(&pvec_vector, &pvec_vector1), false);
  vector_dtor(&pvec_vector);
  vector_dtor(&pvec_vector1);

  PASS();
}
TEST test_vector_assign_n_v()
{
  size_t elesize = 100;
  vector_t pvec_vector;
  user_defined_type_init0_destroy0_copy0_less v;
  v.a = 100;
  v.b = 0;
  v.c[0] = 100;

  // branch test: elesize > vector_capacity and no memeory allocated
  vector_ctor(&pvec_vector, 1, user_defined_pod_id);
  vector_assign_n_v(&pvec_vector, &v, elesize);
  ASSERT_EQ(pvec_vector._pby_endofstorage, pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start,
      elesize * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, user_defined_pod_id);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);
  unsigned char* tmp = pvec_vector._pby_start;
  user_defined_type_init0_destroy0_copy0_less* vptr;
  for (; elesize > 0; elesize--)
  {
    vptr = (user_defined_type_init0_destroy0_copy0_less*) tmp;
    ASSERT_EQ_FMT(100, vptr->a, "%d");
    ASSERT_EQ(0, vptr->b);
    ASSERT_EQ_FMT(100, vptr->c[0], "%d");
    tmp += _GET_VECTOR_TYPE_SIZE(&pvec_vector);
  }
  vector_dtor(&pvec_vector);

  // branch test: elesize > vector_capacity and memeory allocated and need to destrcut old elements
  elesize = 100;
  vector_ctor_n(&pvec_vector, elesize - 1, 1, user_defined_pod_id);
  vector_assign_n_v(&pvec_vector, &v, elesize);
  ASSERT_EQ(pvec_vector._pby_endofstorage, pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start,
      elesize * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, user_defined_pod_id);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);
  tmp = pvec_vector._pby_start;
  for (; elesize > 0; elesize--)
  {
    vptr = (user_defined_type_init0_destroy0_copy0_less*) tmp;
    ASSERT_EQ_FMT(100, vptr->a, "%d");
    ASSERT_EQ(0, vptr->b);
    ASSERT_EQ_FMT(100, vptr->c[0], "%d");
    tmp += _GET_VECTOR_TYPE_SIZE(&pvec_vector);
  }
  vector_dtor(&pvec_vector);

  // branch test: (elesize == vector_capacity) > vector_size
  elesize = 100;
  vector_ctor_n(&pvec_vector, elesize, 1, user_defined_pod_id);
  random_access_iterator_t ritr;
  vector_end(&pvec_vector, &ritr);
  vector_iterator_prev_n(&ritr, elesize / 2);
  vector_erase(&ritr, true); //size = elesize - 1
  vector_assign_n_v(&pvec_vector, &v, elesize);
  ASSERT_EQ(pvec_vector._pby_endofstorage, pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start,
      elesize * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, user_defined_pod_id);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);
  tmp = pvec_vector._pby_start;
  for (; elesize > 0; elesize--)
  {
    vptr = (user_defined_type_init0_destroy0_copy0_less*) tmp;
    ASSERT_EQ_FMT(100, vptr->a, "%d");
    ASSERT_EQ(0, vptr->b);
    ASSERT_EQ_FMT(100, vptr->c[0], "%d");
    tmp += _GET_VECTOR_TYPE_SIZE(&pvec_vector);
  }
  vector_dtor(&pvec_vector);

  // branch test:  vector_size < elesize  < vector_capacity
  elesize = 100;
  vector_ctor_n(&pvec_vector, elesize, 1, user_defined_pod_id);
  vector_end(&pvec_vector, &ritr);
  vector_iterator_prev_n(&ritr, elesize / 2);
  for (int i = 0; i < 10; i++)
    vector_erase(&ritr, true);
  elesize = 95; //size = 90 < 95 < 100
  vector_assign_n_v(&pvec_vector, &v, elesize);
  ASSERT_FALSE(pvec_vector._pby_endofstorage <= pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_finish - pvec_vector._pby_start,
      elesize * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, user_defined_pod_id);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);
  tmp = pvec_vector._pby_start;
  for (; elesize > 0; elesize--)
  {
    vptr = (user_defined_type_init0_destroy0_copy0_less*) tmp;
    ASSERT_EQ_FMT(100, vptr->a, "%d");
    ASSERT_EQ(0, vptr->b);
    ASSERT_EQ_FMT(100, vptr->c[0], "%d");
    tmp += _GET_VECTOR_TYPE_SIZE(&pvec_vector);
  }
  vector_dtor(&pvec_vector);

  // branch test: elesize = vector_size
  elesize = 100;
  vector_ctor_n(&pvec_vector, elesize, 1, user_defined_pod_id);
  size_t vecsize = vector_size(&pvec_vector);
  vector_assign_n_v(&pvec_vector, &v, vecsize);
  ASSERT_EQ(pvec_vector._pby_endofstorage, pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start,
      elesize * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, user_defined_pod_id);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);
  tmp = pvec_vector._pby_start;
  for (; elesize > 0; elesize--)
  {
    vptr = (user_defined_type_init0_destroy0_copy0_less*) tmp;
    ASSERT_EQ_FMT(100, vptr->a, "%d");
    ASSERT_EQ(0, vptr->b);
    ASSERT_EQ_FMT(100, vptr->c[0], "%d");
    tmp += _GET_VECTOR_TYPE_SIZE(&pvec_vector);
  }
  vector_dtor(&pvec_vector);

  //branch test: 0 < elesize < vector_size
  elesize = 100;
  vector_ctor_n(&pvec_vector, elesize, 1, user_defined_pod_id);
  vector_assign_n_v(&pvec_vector, &v, elesize / 2);
  ASSERT_EQ(pvec_vector._pby_endofstorage, pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start,
      elesize * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, user_defined_pod_id);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);
  tmp = pvec_vector._pby_start;
  size_t newelesize;
  for (newelesize = 0; newelesize < elesize / 2; newelesize++)
  {
    vptr = (user_defined_type_init0_destroy0_copy0_less*) tmp;
    ASSERT_EQ_FMT(100, vptr->a, "%d");
    ASSERT_EQ(0, vptr->b);
    ASSERT_EQ_FMT(100, vptr->c[0], "%d");
    tmp += _GET_VECTOR_TYPE_SIZE(&pvec_vector);
  }
  for (; newelesize < elesize; newelesize++)
  {
    vptr = (user_defined_type_init0_destroy0_copy0_less*) tmp;
    ASSERT_EQ_FMT(0, vptr->a, "%d");
    ASSERT_EQ(0, vptr->b);
    ASSERT_EQ_FMT(0, vptr->c[0], "%d");
    tmp += _GET_VECTOR_TYPE_SIZE(&pvec_vector);
  }
  vector_dtor(&pvec_vector);

  // branch test:  0 = elesize
  elesize = 100;
  vector_ctor_n(&pvec_vector, elesize, 1, user_defined_pod_id);
  vector_assign_n_v(&pvec_vector, &v, 0);
  ASSERT_EQ(pvec_vector._pby_endofstorage, pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start,
      elesize * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER);
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, user_defined_pod_id);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);
  tmp = pvec_vector._pby_start;
  for (; elesize > 0; elesize--)
  {
    vptr = (user_defined_type_init0_destroy0_copy0_less*) tmp;
    ASSERT_EQ_FMT(0, vptr->a, "%d");
    ASSERT_EQ(0, vptr->b);
    ASSERT_EQ_FMT(0, vptr->c[0], "%d");
    tmp += _GET_VECTOR_TYPE_SIZE(&pvec_vector);
  }
  vector_dtor(&pvec_vector);

  PASS();
}
TEST test_vector_erase()
{
  size_t elesize = 100;

  vector_t pvec_vector;
  vector_ctor_n(&pvec_vector, elesize, 1, user_defined_non_pod_id);

  // erase last ele
  random_access_iterator_t position;
  vector_end(&pvec_vector, &position);
  ASSERT_EQ(position._t_pos, pvec_vector._pby_finish);
  random_access_iterator_t pre_end = position;
  ASSERT_EQ(pre_end._t_pos,pvec_vector._pby_finish);
  vector_iterator_prev(&position);
  ASSERT_EQ(position._t_pos, pvec_vector._pby_finish-_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  vector_erase(&position, true);
  ASSERT_EQ(vector_size(&pvec_vector), elesize-1);
  ASSERT_EQ(pvec_vector._pby_finish, position._t_pos);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_finish,
      _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  vector_end(&pvec_vector, &position);
  ASSERT_EQ(1,iterator_continue_minus(&position, &pre_end));

  // erase first ele
  vector_begin(&pvec_vector, &position);
  ASSERT_EQ(position._t_pos, pvec_vector._pby_start);
  random_access_iterator_t second = position;
  vector_iterator_next(&second);
  ((user_defined_type_init_destroy_copy_less*) second._t_pos)->a -= 1;
  user_defined_type_init_destroy_copy_less secondval = *((user_defined_type_init_destroy_copy_less*) second._t_pos);
  vector_erase(&position, true);
  ASSERT_EQ(vector_size(&pvec_vector), elesize-2);
  ASSERT_EQ(((user_defined_type_init_destroy_copy_less*)position._t_pos)->a,secondval.a);

  vector_dtor(&pvec_vector);
  PASS();
}
TEST test_vector_swap()
{
  size_t firstelesize = 10000;
  user_defined_type_init_destroy_copy_less firstv;
  firstv.a = 100;
  firstv.b = cstl_alloc(int, firstv.a);
  firstv.c[0] = 100;
  vector_t firstpvec;
  vector_ctor_n_v(&firstpvec, firstelesize, &firstv, 1, user_defined_pod_id);

  size_t secondelesize = firstelesize / 2;
  user_defined_type_init_destroy_copy_less secondv;
  secondv.a = firstv.a / 2;
  secondv.b = cstl_alloc(int, secondv.a);
  secondv.c[0] = firstv.c[0] / 2;
  vector_t secondpvec;
  vector_ctor_n_v(&secondpvec, secondelesize, &secondv, 1, user_defined_pod_id);

  user_defined_type_init_destroy_copy_less* origisecfv = (user_defined_type_init_destroy_copy_less*) vector_at(
      &secondpvec, 0);
  size_t origisecsize = vector_size(&secondpvec);

  user_defined_type_init_destroy_copy_less* origifirstfv = (user_defined_type_init_destroy_copy_less*) vector_at(
      &firstpvec, 0);
  size_t origifirstsize = vector_size(&firstpvec);

  vector_swap(&firstpvec, &secondpvec);

  user_defined_type_init_destroy_copy_less* fv = (user_defined_type_init_destroy_copy_less*) vector_at(&firstpvec, 0);
  ASSERT_EQ(origisecfv->a, fv->a);
  ASSERT_EQ(origisecfv->c[0], fv->c[0]);
  ASSERT_EQ(origisecfv->b, fv->b);
  ASSERT_EQ(origisecsize, vector_size(&firstpvec));
  ASSERT_EQ(origisecsize, vector_size(&firstpvec));

  user_defined_type_init_destroy_copy_less* sv = (user_defined_type_init_destroy_copy_less*) vector_at(&secondpvec, 0);
  ASSERT_EQ(origifirstfv->a, sv->a);
  ASSERT_EQ(origifirstfv->c[0], sv->c[0]);
  ASSERT_EQ(origifirstfv->b, sv->b);
  ASSERT_EQ(origifirstsize, vector_size(&secondpvec));

  vector_dtor(&firstpvec);
  vector_dtor(&secondpvec);
  cstl_free(firstv.b);
  cstl_free(secondv.b);

  PASS();
}
TEST test_vector_reserve()
{
  // given a vector with 100 user_defined_type_init_destroy_copy_less structs
  size_t elesize = 100;
  user_defined_type_init_destroy_copy_less firstv;
  firstv.a = 100;
  firstv.b = cstl_alloc(int, firstv.a);
  firstv.c[0] = 100;
  vector_t pvec_vector;
  vector_ctor_n_v(&pvec_vector, elesize, &firstv, 1, user_defined_pod_id);

  // when reserve 101
  vector_reserve_n(&pvec_vector, elesize + 1);
  // then size should remains same
  ASSERT_EQ_FMT(vector_size(&pvec_vector), elesize, "%lu");
  // then capacity should increase
  ASSERT_EQ(vector_capacity(&pvec_vector), elesize+1);
  // then all elements should remain same to before
  elesize = vector_size(&pvec_vector);
  _byte_t* tmp = pvec_vector._pby_start;
  for (; elesize > 0; elesize--)
  {
    user_defined_type_init_destroy_copy_less* vptr = (user_defined_type_init_destroy_copy_less*) tmp;
    ASSERT_EQ_FMT(firstv.a, vptr->a, "%d");
    ASSERT_FALSE(vptr->b == 0);
    ASSERT_EQ_FMT(firstv.c[0], vptr->c[0], "%d");
    tmp += _GET_VECTOR_TYPE_SIZE(&pvec_vector);
  }

  vector_dtor(&pvec_vector);
  cstl_free(firstv.b);
  PASS();
}
SUITE(test_vector)
{
  RUN_TEST(test_vector_ctor_scalar_type);
  RUN_TEST(test_vector_ctor_n_scalar_type);
  RUN_TEST(test_vector_ctor_n_v_scalar_type);
  RUN_TEST(test_vector_ctor_vec_scalar_type);
  RUN_TEST(test_vector_ctor_range_scalar_type);
  RUN_TEST(test_vector_ctor_user_defined_pod);
  RUN_TEST(test_vector_ctor_n_user_defined_pod);
  RUN_TEST(test_vector_ctor_n_v_user_defined_pod);
  RUN_TEST(test_vector_ctor_vec_user_defined_pod);
  RUN_TEST(test_vector_ctor_range_user_defined_pod);
  RUN_TEST(test_vector_ctor_user_defined_non_pod);
  RUN_TEST(test_vector_ctor_n_user_defined_non_pod);
  RUN_TEST(test_vector_ctor_n_v_user_defined_non_pod);
  RUN_TEST(test_vector_ctor_range_user_defined_non_pod);
  RUN_TEST(test_vector_ctor_range_n_user_defined_non_pod);
  RUN_TEST(test_vector_size);
  RUN_TEST(test_vector_equal);
  RUN_TEST(test_vector_assign_n_v);
  RUN_TEST(test_vector_erase);
  RUN_TEST(test_vector_swap);
  RUN_TEST(test_vector_reserve);
}

TEST test_union_ptr_as_buf(void)
{
  unsigned char* ptr = 0;
  for (int i = 0; i < TYPE_ID_SIZE; i++)
  {
    ((unsigned char*) &ptr)[i] = (unsigned char) i;
    ASSERT_EQ(i, ((unsigned char*)&ptr)[i]);
  }

  unsigned char* ptrrr;
  for (int i = 0; i < TYPE_ID_SIZE; i++)
  {
    ptrrr = ((unsigned char*) (&ptr)) + i;
    for (int j = i; j < TYPE_ID_SIZE; j++)
    {
      ASSERT_EQ_FMT(j, ptrrr[j - i], "%d");
    }
    printf("\n");
  }
  PASS();
}

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS()
;

int main(int argc, char **argv)
{
  init_types(0);
  user_defined_pod_id = register_type(sizeof(user_defined_type_init0_destroy0_copy0_less),
  CSTL_ALIGN_OF(user_defined_type_init0_destroy0_copy0_less), 0, 0, 0,
      func_less_user_defined_type_init0_destroy0_copy0_less);
  user_defined_non_pod_id = register_type(sizeof(user_defined_type_init_destroy_copy_less),
  CSTL_ALIGN_OF(user_defined_type_init_destroy_copy_less), func_init_user_defined_type_init_destroy_copy_less,
      func_copy_user_defined_type_init_destroy_copy_less, func_destroy_user_defined_type_init_destroy_copy_less,
      func_less_user_defined_type_init_destroy_copy_less);

  /* command-line options, initialization. */
  GREATEST_MAIN_BEGIN();
  /* Individual tests can be run directly in main, outside of suites. */
  RUN_TEST(test_union_ptr_as_buf);
  RUN_TEST(test_cstl_alloc_free);
  /* Tests can also be gathered into test suites. */
  RUN_SUITE(test_vector);
  GREATEST_MAIN_END(); /* display results */

  destroy_types();
}
