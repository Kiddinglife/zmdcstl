#include "greatest.h"
#include <chrono>
#include <vector>
#include <iostream>
#include "../zmdcstl/cstl_vector.h"

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS()

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

TEST benchmark_vector_ctor(void)
{
  profile_start(stdvec);
  std::vector<int> stdvec;
  profile_end_ns(stdvec);

  vector_t zmdcstlvec;
  profile_start(zmdcstlvec);
  vector_ctor(&zmdcstlvec, 1, cstl_uint32);
  profile_end_ns(zmdcstlvec);

  profile_ratio(zmdcstlvec, stdvec);

  vector_dtor(&zmdcstlvec);
  PASS();
}
TEST benchmark_vector_ctor_n(void)
{
  size_t size = 10000000;

  profile_start(stdvec);
  std::vector<int> stdvec(size);
  profile_end_ms(stdvec);

  vector_t zmdcstlvec;
  profile_start(zmdcstlvec);
  vector_ctor_n(&zmdcstlvec, size, 1, cstl_int32);
  profile_end_ms(zmdcstlvec);

  profile_ratio(zmdcstlvec, stdvec);

  vector_dtor(&zmdcstlvec);
  PASS();
}
TEST benchmark_vector_ctor_n_v(void)
{
  size_t size = 10000000;
  int v = 100;

  profile_start(stdvec);
  std::vector<int> stdvec(size, v);
  profile_end_ms(stdvec);

  vector_t zmdcstlvec;
  profile_start(zmdcstlvec);
  vector_ctor_n_v(&zmdcstlvec, size, &v, 1, cstl_int32);
  profile_end_ms(zmdcstlvec);

  profile_ratio(zmdcstlvec, stdvec);

  vector_dtor(&zmdcstlvec);
  PASS();
}
SUITE(benchmark_vector)
{
  RUN_TEST(benchmark_vector_ctor);
  RUN_TEST(benchmark_vector_ctor_n);
  RUN_TEST(benchmark_vector_ctor_n_v);
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
