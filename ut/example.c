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
  *(bool*) out = ((user_defined_type_init0_destroy0_copy0_less*) in)->a
      < ((user_defined_type_init0_destroy0_copy0_less*) in_)->a;
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
  memset(((user_defined_type_init_destroy_copy_less*) in)->b, 0, 32 * sizeof(int));
  ((user_defined_type_init_destroy_copy_less*) in)->a = 0;
  memset(((user_defined_type_init_destroy_copy_less*) in)->c, 0, 32);
}
static void func_copy_user_defined_type_init_destroy_copy_less(const void* in, const void* in_, void* out)
{
  ((user_defined_type_init_destroy_copy_less*) in)->b = cstl_alloc(int,
      ((user_defined_type_init_destroy_copy_less* ) in_)->a);
  cstl_memcpy(((user_defined_type_init_destroy_copy_less*) in)->b, ((user_defined_type_init_destroy_copy_less*) in_)->b,
      ((user_defined_type_init_destroy_copy_less*) in_)->a * sizeof(int));
  ((user_defined_type_init_destroy_copy_less*) in)->a = ((user_defined_type_init_destroy_copy_less*) in_)->a;
  cstl_memcpy(((user_defined_type_init_destroy_copy_less*) in)->c, ((user_defined_type_init_destroy_copy_less*) in_)->c,
      32);
}
static void func_destroy_user_defined_type_init_destroy_copy_less(const void* in, void* out)
{
  cstl_free(((user_defined_type_init_destroy_copy_less* )in)->b);
}
static void func_less_user_defined_type_init_destroy_copy_less(const void* in, const void* in_, void* out)
{
  *(bool*) out = ((user_defined_type_init_destroy_copy_less*) in)->a
      < ((user_defined_type_init_destroy_copy_less*) in_)->a;
}

TEST test_cstl_alloc_free(void)
{
  int* x;
  for (int i = 0; i < 1000000; i++)
  {
    x = (int*) cstl_alloc(int, 2);
    *x = 100;
    *(x + 1) = 200;
    ASSERT_EQ(*x, 100);
    ASSERT_EQ(*(x+1), 200);
    cstl_free(x);
  }
  PASS();
}
SUITE(test_cstl_alloc)
{
  RUN_TEST(test_cstl_alloc_free);
}

TEST test_vector_ctor_scalar_type(void)
{
  vector_t pvec_vector =
  { 0 };
  vector_ctor(&pvec_vector, 1, cstl_uint32);
  ASSERT_EQ(pvec_vector._pby_finish, NULL );
  ASSERT_EQ(pvec_vector._pby_start, NULL );
  ASSERT_EQ(pvec_vector._pby_endofstorage, NULL );
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER );
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, cstl_uint32);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);
  vector_dtor(&pvec_vector);
  PASS();
}
TEST test_vector_ctor_user_defined_pod()
{
  vector_t pvec_vector;
  vector_ctor(&pvec_vector, 1, user_defined_pod_id);
  ASSERT_EQ(pvec_vector._pby_finish, NULL );
  ASSERT_EQ(pvec_vector._pby_start, NULL );
  ASSERT_EQ(pvec_vector._pby_endofstorage, NULL );
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER );
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, user_defined_pod_id);
  ASSERT_EQ_FMT(1, pvec_vector.meta._t_typeinfo._t_typeidsize, "%d");
  vector_dtor(&pvec_vector);
  PASS();
}
TEST test_vector_ctor_user_defined_non_pod()
{
  vector_t pvec_vector;
  vector_ctor(&pvec_vector, 1, user_defined_non_pod_id);
  ASSERT_EQ(pvec_vector._pby_finish, NULL );
  ASSERT_EQ(pvec_vector._pby_start, NULL );
  ASSERT_EQ(pvec_vector._pby_endofstorage, NULL );
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER );
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, user_defined_non_pod_id);
  ASSERT_EQ_FMT(1, pvec_vector.meta._t_typeinfo._t_typeidsize, "%d");
  vector_dtor(&pvec_vector);
  PASS();
}
TEST test_vector_ctor_n_scalar_type()
{
  vector_t pvec_vector;
  vector_ctor_n(&pvec_vector, 1, 1, cstl_uint32);
  ASSERT_EQ(pvec_vector._pby_start, pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start, _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_FALSE(pvec_vector._pby_endofstorage == NULL);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER );
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, cstl_uint32);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);
  vector_dtor(&pvec_vector);
  PASS();
}
TEST test_vector_ctor_n_user_defined_pod(void)
{
  vector_t pvec_vector;
  vector_ctor_n(&pvec_vector, 10, 1, user_defined_pod_id);
  ASSERT_EQ(pvec_vector._pby_start, pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start, 10*_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_FALSE(pvec_vector._pby_endofstorage == NULL);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER );
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, user_defined_pod_id);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);
  vector_dtor(&pvec_vector);
  PASS();
}
TEST test_vector_ctor_n_user_defined_non_pod(void)
{
  vector_t pvec_vector;
  vector_ctor_n(&pvec_vector, 10, 1, user_defined_non_pod_id);
  ASSERT_EQ(pvec_vector._pby_start, pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start, 10*_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_FALSE(pvec_vector._pby_endofstorage == NULL);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER );
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, user_defined_non_pod_id);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);
  vector_dtor(&pvec_vector);
  PASS();
}
TEST test_vector_ctor_n_v_scalar_type(void)
{
  vector_t pvec_vector;
  unsigned int v = 100;
  size_t elesize = 100;
  vector_ctor_n_v(&pvec_vector, elesize, &v, 1, cstl_uint32);

  ASSERT_EQ(pvec_vector._pby_start, pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start, elesize * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_FALSE(pvec_vector._pby_endofstorage == NULL);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER );
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
TEST test_vector_ctor_n_v_user_defined_pod(void)
{
  vector_t pvec_vector;
  user_defined_type_init0_destroy0_copy0_less v;
  v.a = 100;
  v.b = 0;
  v.c[0] = 100;
  size_t elesize = 100;
  vector_ctor_n_v(&pvec_vector, elesize, &v, 1, user_defined_pod_id);

  ASSERT_EQ(pvec_vector._pby_start, pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start, elesize * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_FALSE(pvec_vector._pby_endofstorage == NULL);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER );
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
TEST test_vector_ctor_n_v_user_defined_non_pod(void)
{
  vector_t pvec_vector;
  user_defined_type_init_destroy_copy_less v;
  v.a = 100;
  v.b = cstl_alloc(int, v.a);
  v.c[0] = 100;
  size_t elesize = v.a;
  CHECK_CALL(test_vector_ctor_n_user_defined_non_pod());
  vector_ctor_n_v(&pvec_vector, elesize, &v, 1, user_defined_non_pod_id);

  ASSERT_EQ(pvec_vector._pby_start, pvec_vector._pby_finish);
  ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start, elesize * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typesize);
  ASSERT_FALSE(pvec_vector._pby_endofstorage == NULL);
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER );
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
    tmp += _GET_VECTOR_TYPE_SIZE(&pvec_vector);
  }

  cstl_free(v.b);
  vector_dtor(&pvec_vector);
  PASS();
}
TEST test_vector_ctor_vec_scalar_type(void)
{
  vector_t pvec_vector_;
  unsigned int v = 100;
  size_t elesize = 100;
  vector_ctor_n_v(&pvec_vector_, elesize, &v, 1, cstl_uint32);

  vector_t pvec_vector;
  vector_ctor_vector(&pvec_vector, &pvec_vector_);
  vector_ctor(&pvec_vector, 1, cstl_uint32);

  // as nothing pushed to pvec_vector_ and so pvec_vector should be also empty
  ASSERT_EQ(pvec_vector._pby_finish, NULL );
  ASSERT_EQ(pvec_vector._pby_start, NULL );
  ASSERT_EQ(pvec_vector._pby_endofstorage, NULL );
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER );
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

  // as nothing pushed to pvec_vector_ and so pvec_vector should be also empty
  ASSERT_EQ(pvec_vector._pby_finish, NULL );
  ASSERT_EQ(pvec_vector._pby_start, NULL );
  ASSERT_EQ(pvec_vector._pby_endofstorage, NULL );
  ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER );
  ASSERT_EQ(_GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector)->_t_typeid, user_defined_pod_id);
  ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1);

  vector_dtor(&pvec_vector);
  vector_dtor(&pvec_vector_);
  PASS();
}
TEST test_vector_ctor_range_scalar_type(void)
{
  vector_t pvec_vector;
  unsigned int v = 100;
  size_t elesize = 100;
  vector_ctor_n_v(&pvec_vector, elesize, &v, 1, cstl_uint32);

  size_t copysize = 5;
  random_access_iterator_t first;
  random_access_iterator_t last;
  first._pt_container = &pvec_vector;
  _VECTOR_ITERATOR_COREPOS(&first) = pvec_vector._pby_start;
  last._pt_container = &pvec_vector;
  _VECTOR_ITERATOR_COREPOS(&last) = pvec_vector._pby_start + copysize * _GET_VECTOR_TYPE_SIZE(&pvec_vector);

  vector_t pvec_vector_;
  vector_ctor_range(&pvec_vector_, &first, &last);

  ASSERT_EQ(pvec_vector_._pby_start, pvec_vector_._pby_finish);
  ASSERT_EQ(pvec_vector_._pby_endofstorage - pvec_vector_._pby_start, copysize * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector_)->_t_typesize);
  ASSERT_FALSE(pvec_vector_._pby_endofstorage == NULL);
  ASSERT_EQ(pvec_vector_.meta._t_containertype, _VECTOR_CONTAINER );
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
TEST test_vector_ctor_range_user_defined_pod(void)
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
  random_access_iterator_t first;
  random_access_iterator_t last;
  first._pt_container = &pvec_vector;
  _VECTOR_ITERATOR_COREPOS(&first) = pvec_vector._pby_start;
  last._pt_container = &pvec_vector;
  _VECTOR_ITERATOR_COREPOS(&last) = pvec_vector._pby_start + copysize * _GET_VECTOR_TYPE_SIZE(&pvec_vector);

  vector_t pvec_vector_;
  vector_ctor_range(&pvec_vector_, &first, &last);

  ASSERT_EQ(pvec_vector_._pby_start, pvec_vector_._pby_finish);
  ASSERT_EQ(pvec_vector_._pby_endofstorage - pvec_vector_._pby_start, copysize * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector_)->_t_typesize);
  ASSERT_FALSE(pvec_vector_._pby_endofstorage == NULL);
  ASSERT_EQ(pvec_vector_.meta._t_containertype, _VECTOR_CONTAINER );
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
TEST test_vector_ctor_range_user_defined_non_pod(void)
{
  vector_t pvec_vector;
  user_defined_type_init_destroy_copy_less v;
  v.a = 100;
  v.b = cstl_alloc(int, v.a);
  v.c[0] = 100;
  size_t elesize = v.a;
  CHECK_CALL(test_vector_ctor_n_v_user_defined_pod());
  vector_ctor_n_v(&pvec_vector, elesize, &v, 1, user_defined_non_pod_id);

  size_t copysize = 5;
  random_access_iterator_t first;
  random_access_iterator_t last;
  first._pt_container = &pvec_vector;
  _VECTOR_ITERATOR_COREPOS(&first) = pvec_vector._pby_start;
  last._pt_container = &pvec_vector;
  _VECTOR_ITERATOR_COREPOS(&last) = pvec_vector._pby_start + copysize * _GET_VECTOR_TYPE_SIZE(&pvec_vector);

  vector_t pvec_vector_;
  vector_ctor_range(&pvec_vector_, &first, &last);

  ASSERT_EQ(pvec_vector_._pby_start, pvec_vector_._pby_finish);
  ASSERT_EQ(pvec_vector_._pby_endofstorage - pvec_vector_._pby_start, copysize * _GET_VECTOR_TYPE_INFO_TYPE(&pvec_vector_)->_t_typesize);
  ASSERT_FALSE(pvec_vector_._pby_endofstorage == NULL);
  ASSERT_EQ(pvec_vector_.meta._t_containertype, _VECTOR_CONTAINER );
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
    tmp += _GET_VECTOR_TYPE_SIZE(&pvec_vector);
  }

  vector_dtor(&pvec_vector);
  vector_dtor(&pvec_vector_);
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
}

TEST test_union_ptr_as_buf(void)
{
  unsigned char* ptr = 0;
  for (int i = 0; i < TYPE_ID_SIZE; i++)
  {
    ((unsigned char*) &ptr)[i] = (unsigned char) i;
  }
  for (int i = 0; i < TYPE_ID_SIZE; i++)
  {
    ASSERT_EQ(i,((unsigned char*) &ptr)[i]);
  }
  PASS();
}

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS()
;

int main(int argc, char **argv)
{
  /* command-line options, initialization. */
  GREATEST_MAIN_BEGIN();

  /* Individual tests can be run directly in main, outside of suites. */
  RUN_TEST(test_union_ptr_as_buf);

  /* Tests can also be gathered into test suites. */
  init_types(0);
  user_defined_pod_id = register_type(sizeof(user_defined_type_init0_destroy0_copy0_less),
  CSTL_ALIGN_OF(user_defined_type_init0_destroy0_copy0_less), 0, 0, 0,
      func_less_user_defined_type_init0_destroy0_copy0_less);
  user_defined_non_pod_id = register_type(sizeof(user_defined_type_init_destroy_copy_less),
  CSTL_ALIGN_OF(user_defined_type_init_destroy_copy_less), func_init_user_defined_type_init_destroy_copy_less,
      func_copy_user_defined_type_init_destroy_copy_less, func_destroy_user_defined_type_init_destroy_copy_less,
      func_less_user_defined_type_init_destroy_copy_less);

  //printf("init user defined type, id=%d\n", typeid_user_defined_type_init_destroy_copy_less);
  RUN_SUITE(test_cstl_alloc);
  RUN_SUITE(test_vector);

  destroy_types();
  GREATEST_MAIN_END(); /* display results */
}
