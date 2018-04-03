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
      //b = (int*)malloc(a*sizeof(int));
      memset(b, 0, a * sizeof(int));
      //printf("default ctor called, b=%p\n", b);
      memset(c, 0, 32);
      c[0] = 100;
    }
    user_defined_type_init_destroy_copy_less(const user_defined_type_init_destroy_copy_less& x)
    {
      a = x.a;
      b = cstl_alloc(int, a);
      //b = (int*)malloc(a*sizeof(int));
      //printf("cpy ctor called, x.a=%d,x.b=%p,x.c[0]=%d, this->b=%p\n", x.a, x.b, x.c[0], b);
      cstl_memcpy(b, x.b, a * sizeof(int));
      cstl_memcpy(c, x.c, 32);
    }
    void operator =(const user_defined_type_init_destroy_copy_less &x)
    {
      a = x.a;
      //printf("operator = called, this->b=%p, x.b=%p,\n", b, x.b);
      //b = x.b;
      // cannot use this as std earse will call detor of last element ehich causes double free o last element
      // this is something std should improve because we do not need to deep copy all moved elements shadow cpy is enough
      cstl_free(b);
      b = cstl_alloc(int, a);
      //b = (int*)malloc(a*sizeof(int));
      //printf("operator = called, this->b=%p, x.b=%p,\n", b, x.b);
      cstl_memcpy(b, x.b, a * sizeof(int));
      cstl_memcpy(c, x.c, 32);
    }
    ~user_defined_type_init_destroy_copy_less()
    {
      //printf("dtor called, b=%p\n", b);
      //free(b);
      cstl_free(b);
    }
};
static typeid_t user_defined_non_pod_id;
static void func_init_user_defined_type_init_destroy_copy_less(const void* in, void* out)
{
  user_defined_type_init0_destroy0_copy0_less* to = ((user_defined_type_init0_destroy0_copy0_less*) in);
  to->b = cstl_alloc(int, 100);
  //printf("init alloc = %p\n", to->b);
  memset(to->b, 0, 32 * sizeof(int));
  to->a = 100;
  memset(to->c, 0, 32);
  to->c[0] = 100;
}
static void func_copy_user_defined_type_init_destroy_copy_less(const void* in, const void* in_, void* out)
{
  user_defined_type_init0_destroy0_copy0_less* to = ((user_defined_type_init0_destroy0_copy0_less*) in);
  user_defined_type_init0_destroy0_copy0_less* from = ((user_defined_type_init0_destroy0_copy0_less*) in_);
  to->b = cstl_alloc(int, from->a);
  //printf("copy alloc = %p\n", to->b);
  cstl_memcpy(to->b, from->b, from->a * sizeof(int));
  to->a = from->a;
  cstl_memcpy(to->c, from->c, 32);
}
static void func_destroy_user_defined_type_init_destroy_copy_less(const void* in, void* out)
{
  //printf("destroy alloc = %p\n", to->b);
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

#define profile_start(id) \
auto start##id = std::chrono::steady_clock::now()
#define profile_end_ms(id) \
auto end##id = std::chrono::steady_clock::now();\
auto elapsed##id = \
std::chrono::duration<double, std::milli>(end##id - start##id).count() ;\
std::cout << #id << ":" << elapsed##id<< "ms, "
#define profile_ratio(id1,id2) \
std::cout << "ratio: " << (elapsed##id1)/(elapsed##id2) << " ";

size_t size = 1000000;

TEST benchmark_vector_ctor(void)
{
  profile_start(zmdcstlvec);
  vector_t zmdcstlvec;
  vector_ctor(&zmdcstlvec, 1, user_defined_non_pod_id);
  //vector_dtor(&zmdcstlvec);
  profile_end_ms(zmdcstlvec);
  vector_dtor(&zmdcstlvec);

  profile_start(stdvec);
  std::vector<user_defined_type_init_destroy_copy_less> stdvec;
  //stdvec.~vector();// cannot explicately call dtor because when excute ends, it will call dtor automatically
  profile_end_ms(stdvec);

  profile_ratio(zmdcstlvec, stdvec);

  printf("\n");
  PASS();
}
TEST benchmark_vector_ctor_n(void)
{

  profile_start(zmdcstlvec);
  vector_t zmdcstlvec;
  vector_ctor_n(&zmdcstlvec, size, 1, user_defined_non_pod_id);
  profile_end_ms(zmdcstlvec);
  vector_dtor(&zmdcstlvec);

  profile_start(stdvec);
  std::vector<user_defined_type_init_destroy_copy_less> stdvec(size);
  profile_end_ms(stdvec);

  profile_ratio(zmdcstlvec, stdvec);

  printf("\n");
  PASS();
}

TEST benchmark_vector_ctor_n_v(void)
{
  user_defined_type_init_destroy_copy_less v;

  profile_start(vec_ctor_n_v_non_pod);
  vector_t zmdcstlvec;
  vector_ctor_n_v(&zmdcstlvec, size, &v, 1, user_defined_non_pod_id);
  profile_end_ms(vec_ctor_n_v_non_pod);
  vector_dtor(&zmdcstlvec);

  profile_start(stdvec_n_v_non_pod);
  std::vector<user_defined_type_init_destroy_copy_less> stdvec(size, v);
  profile_end_ms(stdvec_n_v_non_pod);

  profile_ratio(vec_ctor_n_v_non_pod, stdvec_n_v_non_pod);
  printf("\n");

  user_defined_type_init0_destroy0_copy0_less v1;

  profile_start(vec_ctor_n_v_pod);
  vector_t zmdcstlvec1;
  vector_ctor_n_v(&zmdcstlvec1, size, &v, 1, user_defined_pod_id);
  profile_end_ms(vec_ctor_n_v_pod);
  vector_dtor(&zmdcstlvec1);

  profile_start(stdvec_n_v_pod);
  std::vector<user_defined_type_init0_destroy0_copy0_less> stdvec1(size, v1);
  profile_end_ms(stdvec_n_v_pod);

  profile_ratio(vec_ctor_n_v_pod, stdvec_n_v_pod);
  printf("\n");

  unsigned int v2 = 100;
  profile_start(vec_ctor_n_v_ctype);
  vector_t zmdcstlvec2;
  vector_ctor_n_v(&zmdcstlvec2, size, &v2, 1, cstl_uint32);
  profile_end_ms(vec_ctor_n_v_ctype);
  vector_dtor(&zmdcstlvec2);

  profile_start(stdvec_n_v_ctype);
  std::vector<unsigned int> stdvec2(size, v2);
  profile_end_ms(stdvec_n_v_ctype);

  profile_ratio(vec_ctor_n_v_ctype, stdvec_n_v_ctype);

  printf("\n");
  PASS();
}
TEST benchmark_vector_ctor_vector(void)
{
  user_defined_type_init_destroy_copy_less v;

  vector_t zmdcstlvec_;
  vector_ctor_n_v(&zmdcstlvec_, size, &v, 1, user_defined_non_pod_id);
  profile_start(cstl_vector_ctor_vector);
  vector_t zmdcstlvec;
  vector_ctor_vector(&zmdcstlvec, &zmdcstlvec_);
  profile_end_ms(cstl_vector_ctor_vector);
  vector_dtor(&zmdcstlvec);

  std::vector<user_defined_type_init_destroy_copy_less> stdvec_(size, v);
  profile_start(std_vector_ctor_vector);
  std::vector<user_defined_type_init_destroy_copy_less> stdvec(stdvec_);
  profile_end_ms(std_vector_ctor_vector);

  profile_ratio(cstl_vector_ctor_vector, std_vector_ctor_vector);

  vector_dtor(&zmdcstlvec_);

  printf("\n");
  PASS();
}
TEST benchmark_vector_ctor_range(void)
{
  user_defined_type_init_destroy_copy_less v;

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
  vector_dtor(&zmdcstlvec);
  vector_dtor(&zmdcstlvec_);

  std::vector<user_defined_type_init_destroy_copy_less> stdvec_(size, v);
  profile_start(stdvec);
  std::vector<user_defined_type_init_destroy_copy_less> stdvec(stdvec_.begin(), stdvec_.end());
  profile_end_ms(stdvec);

  profile_ratio(zmdcstlvec, stdvec);

  printf("\n");
  PASS();
}
TEST benchmark_vector_ctor_range_n(void)
{
  user_defined_type_init_destroy_copy_less v;

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
  vector_dtor(&zmdcstlvec);
  vector_dtor(&zmdcstlvec_);

  std::vector<user_defined_type_init_destroy_copy_less> stdvec_(size, v);
  profile_start(stdvec);
  std::vector<user_defined_type_init_destroy_copy_less> stdvec(stdvec_.begin(), stdvec_.end());
  profile_end_ms(stdvec);

  profile_ratio(zmdcstlvec, stdvec);

  printf("\n");
  PASS();
}
TEST benchmark_vector_erase(void)
{
  vector_t zmdcstlvec;
  vector_ctor_n(&zmdcstlvec, size, 1, user_defined_non_pod_id);
  profile_start(zmdcstlvec);
  random_access_iterator_t position;
  vector_begin(&zmdcstlvec, &position);
  vector_erase(&position, true);
  profile_end_ms(zmdcstlvec);
  vector_dtor(&zmdcstlvec);

  std::vector<user_defined_type_init_destroy_copy_less> stdvec(size);
  profile_start(stdvec);
  stdvec.erase(stdvec.begin());
  profile_end_ms(stdvec);

  profile_ratio(zmdcstlvec, stdvec);

  printf("\n");
  PASS();
}
TEST benchmark_vector_swap(void)
{
  vector_t zmdcstlvec;
  vector_t zmdcstlvec1;
  vector_ctor_n(&zmdcstlvec, size, 1, cstl_uint32);
  vector_ctor_n(&zmdcstlvec1, size, 1, cstl_uint32);
  profile_start(cstlvec_swap_ctype);
  vector_swap(&zmdcstlvec, &zmdcstlvec1);
  profile_end_ms(cstlvec_swap_ctype);
  vector_dtor(&zmdcstlvec);
  vector_dtor(&zmdcstlvec1);

  std::vector<unsigned int> stdvec(size);
  std::vector<unsigned int> stdvec1(size);
  profile_start(stdvec_swap_ctype);
  stdvec.swap(stdvec1);
  profile_end_ms(stdvec_swap_ctype);

  profile_ratio(cstlvec_swap_ctype, stdvec_swap_ctype);

  printf("\n");
  PASS();
}
SUITE(benchmark_vector)
{
  RUN_TEST(benchmark_vector_ctor);
  printf("\n");
  RUN_TEST(benchmark_vector_ctor_n);
  printf("\n");
  RUN_TEST(benchmark_vector_ctor_n_v);
  printf("\n");
  RUN_TEST(benchmark_vector_ctor_range);
  printf("\n");
  RUN_TEST(benchmark_vector_ctor_range_n);
  printf("\n");
  RUN_TEST(benchmark_vector_ctor_vector);
  printf("\n");
  RUN_TEST(benchmark_vector_erase);
  printf("\n");
  RUN_TEST(benchmark_vector_swap);
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
