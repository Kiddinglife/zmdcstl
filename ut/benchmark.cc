#include "greatest.h"
#include <chrono>
#include <vector>
#include <iostream>
#include "../zmdcstl/cstl_vector.h"

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS()

struct user_defined_type_init0_destroy0_copy0_less
{
    int a;
    // no deep copy and so copy function cam be NULL
    void* b;
    char c[32];
    user_defined_type_init0_destroy0_copy0_less()
    {
      a = 0;
      b = 0;
      memset(c, 0, 32);
    }
    user_defined_type_init0_destroy0_copy0_less(const user_defined_type_init0_destroy0_copy0_less& x)
    {
      a = x.a;
      b = x.b;
      cstl_memcpy(c, x.c, 32 * sizeof(int));
    }
};
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

struct user_defined_type_init_destroy_copy_less
{
    int a;
    // no deep copy and so copy function cam be NULL
    int* b;
    char c[32];
    user_defined_type_init_destroy_copy_less()
    {
      a = 100;
      b = cstl_alloc(int, a);
      //b = (int*) malloc(a * sizeof(int));
      memset(b, 0, a * sizeof(int));
      //printf("default ctor called, b=%p\n", b);
      memset(c, 0, 32);
      c[0] = 100;
    }
    user_defined_type_init_destroy_copy_less(const user_defined_type_init_destroy_copy_less& x)
    {
      a = x.a;
      b = cstl_alloc(int, a);
      //printf("cpy ctor called, x.a=%d,x.b=%p,x.c[0]=%d, this->b=%p\n", x.a, x.b, x.c[0], b);
      cstl_memcpy(b, x.b, a * sizeof(int));
      cstl_memcpy(c, x.c, 32);
    }
    ~user_defined_type_init_destroy_copy_less()
    {
      //printf("dtor called, b=%p\n", b);
      cstl_free(b);
    }
};
static typeid_t user_defined_non_pod_id;
static void func_init_user_defined_type_init_destroy_copy_less(const void* in, void* out)
{
  ((user_defined_type_init_destroy_copy_less*) in)->b = cstl_alloc(int, 32);
  //printf("init alloc = %x\n", ((user_defined_type_init_destroy_copy_less*) in)->b);
  memset(((user_defined_type_init_destroy_copy_less*) in)->b, 0, 32 * sizeof(int));
  ((user_defined_type_init_destroy_copy_less*) in)->a = 0;
  memset(((user_defined_type_init_destroy_copy_less*) in)->c, 0, 32);
}
static void func_copy_user_defined_type_init_destroy_copy_less(const void* in, const void* in_, void* out)
{
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

#define profile_start(id) auto start##id = std::chrono::system_clock::now()
#define profile_end_ms(id)\
    auto end##id = std::chrono::system_clock::now();\
    auto elapsed##id = std::chrono::duration<float, std::milli>(end##id - start##id);\
    std::cout << #id << ":" << elapsed##id.count() << "ms, "
#define profile_end_ns(id)\
    auto end##id = std::chrono::system_clock::now();\
    auto elapsed##id = std::chrono::duration<float>(end##id - start##id);\
    std::cout << #id << ":" << elapsed##id.count() << "ns, "
#define profile_ratio(id1,id2)   std::cout << "ratio: " << elapsed##id1/elapsed##id2 << "\n"

size_t size = 100000;

TEST benchmark_vector_ctor(void)
{
  profile_start(stdvec);
  std::vector<user_defined_type_init_destroy_copy_less> stdvec;
  //stdvec.~vector(); cannot explicately call dtor because when excute ends, it will call dtor automatically
  profile_end_ns(stdvec);

  profile_start(zmdcstlvec);
  vector_t zmdcstlvec;
  vector_ctor(&zmdcstlvec, 1, user_defined_non_pod_id);
  profile_end_ns(zmdcstlvec);

  profile_ratio(zmdcstlvec, stdvec);

  vector_dtor(&zmdcstlvec);

  PASS();
}
TEST benchmark_vector_ctor_n(void)
{
  profile_start(stdvec);
  std::vector<user_defined_type_init_destroy_copy_less> stdvec(size);
  //stdvec.~vector(); cannot explicately call dtor because when excute ends, it will call dtor automatically
  profile_end_ms(stdvec);

  profile_start(zmdcstlvec);
  vector_t zmdcstlvec;
  vector_ctor_n(&zmdcstlvec, size, 1, user_defined_non_pod_id);
  profile_end_ms(zmdcstlvec);

  profile_ratio(zmdcstlvec, stdvec);

  vector_dtor(&zmdcstlvec);

  PASS();
}
TEST benchmark_vector_ctor_n_v(void)
{
  user_defined_type_init_destroy_copy_less v;

  profile_start(stdvec);
  std::vector<user_defined_type_init_destroy_copy_less> stdvec(size, v);
  //stdvec.~vector(); cannot explicately call dtor because when excute ends, it will call dtor automatically
  profile_end_ms(stdvec);

  profile_start(zmdcstlvec);
  vector_t zmdcstlvec;
  vector_ctor_n_v(&zmdcstlvec, size, &v, 1, user_defined_non_pod_id);
  profile_end_ms(zmdcstlvec);

  profile_ratio(zmdcstlvec, stdvec);

  vector_dtor(&zmdcstlvec);

  PASS();
}
TEST benchmark_vector_ctor_vector(void)
{
  user_defined_type_init_destroy_copy_less v;
  std::vector<user_defined_type_init_destroy_copy_less> stdvec_(size, v);

  profile_start(stdvec);
  std::vector<user_defined_type_init_destroy_copy_less> stdvec(stdvec_);
  //stdvec.~vector(); cannot explicately call dtor because when excute ends, it will call dtor automatically
  profile_end_ms(stdvec);

  vector_t zmdcstlvec_;
  vector_ctor_n_v(&zmdcstlvec_, size, &v, 1, user_defined_non_pod_id);
  profile_start(zmdcstlvec);
  vector_t zmdcstlvec;
  vector_ctor_vector(&zmdcstlvec, &zmdcstlvec_);
  profile_end_ms(zmdcstlvec);

  profile_ratio(zmdcstlvec, stdvec);

  vector_dtor(&zmdcstlvec_);
  vector_dtor(&zmdcstlvec);

  PASS();
}
TEST benchmark_vector_ctor_range(void)
{
  user_defined_type_init_destroy_copy_less v;
  std::vector<user_defined_type_init_destroy_copy_less> stdvec_(size, v);

  profile_start(stdvec);
  std::vector<user_defined_type_init_destroy_copy_less> stdvec(stdvec_.begin(), stdvec_.end());
  //stdvec.~vector(); cannot explicately call dtor because when excute ends, it will call dtor automatically
  profile_end_ms(stdvec);

  vector_t zmdcstlvec_;
  vector_ctor_n_v(&zmdcstlvec_, size, &v, 1, user_defined_non_pod_id);

  random_access_iterator_t first;
  vector_begin(&zmdcstlvec_, &first);

  random_access_iterator_t last;
  vector_end(&zmdcstlvec_, &last);

  profile_start(zmdcstlvec);
  vector_t zmdcstlvec;
  vector_ctor_range(&zmdcstlvec, &first, &last);
  profile_end_ms(zmdcstlvec);

  profile_ratio(zmdcstlvec, stdvec);

  vector_dtor(&zmdcstlvec_);
  vector_dtor(&zmdcstlvec);

  PASS();
}
SUITE(benchmark_vector)
{
  RUN_TEST(benchmark_vector_ctor);
  RUN_TEST(benchmark_vector_ctor_n);
  RUN_TEST(benchmark_vector_ctor_n_v);
  RUN_TEST(benchmark_vector_ctor_vector);
  RUN_TEST(benchmark_vector_ctor_range);
}

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
  //...
  /* Tests can also be gathered into test suites. */
  RUN_SUITE(benchmark_vector);
  GREATEST_MAIN_END(); /* display results */

  destroy_types();
}
