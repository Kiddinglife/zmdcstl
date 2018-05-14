#include <chrono>
#include <vector>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

#include "greatest.h"

#include "../zmdcstl/cstl_vector.h"

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS()

static size_t size = 5000000;

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
static int func_less_user_defined_type_init0_destroy0_copy0_less(void* in, void* in_)
{
  int a = ((user_defined_type_init0_destroy0_copy0_less*) in)->a;
  int b = ((user_defined_type_init0_destroy0_copy0_less*) in_)->a;
  if (a < b)
    return -1;
  else if (a > b)
    return 1;
  else
    return 0;
}

struct user_defined_type_init_destroy_copy_less
{
    int a;
    int id;
    // no deep copy and so copy function cam be NULL
    int* b;
    char c[32];

    user_defined_type_init_destroy_copy_less()
    {
      id = 0;
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
      if (this == &x)
        return;
      id = x.id;
      a = x.a;
      b = cstl_alloc(int, a);
      //printf("cpy ctor called, x.a=%d,x.b=%p,x.c[0]=%d, this->b=%p\n", x.a, x.b, x.c[0], b);
      cstl_memcpy(b, x.b, a * sizeof(int));
      cstl_memcpy(c, x.c, 32);
      //std::cout << "cpt ctor called, id=" << id << ", b=" << b << std::endl;
    }

    void operator =(const user_defined_type_init_destroy_copy_less &x)
    {
      if (this == &x)
        return;
      //std::cout << "opt= called, id=" << id << "<-x.id=" << x.id;
      a = x.a;
      id = x.id;
      // cannot use this as std earse will call detor of last element ehich causes double free o last element
      // this is something std should improve because we do not need to deep copy all moved elements shadow cpy is enough
      //b = x.b;
      //std::cout << ", free old b=" << b;
      cstl_free(b);
      b = cstl_alloc(int, a);
      //std::cout << ", new b=" << b << std::endl;
      //printf("operator = called, this->b=%p, x.b=%p,\n", b, x.b);
      cstl_memcpy(b, x.b, a * sizeof(int));
      cstl_memcpy(c, x.c, 32);
    }
    void operator =(user_defined_type_init_destroy_copy_less &&x)
    {
      if (this == &x)
        return;
      a = x.a;
      id = x.id;
      b = x.b;
      x.b = 0;
    }
    ~user_defined_type_init_destroy_copy_less()
    {
      //printf("dtor called, id=%d, b=%p\n", id, b);
      cstl_free(b);
      b = 0;
    }
};
static typeid_t user_defined_non_pod_id;

static void func_init_user_defined_type_init_destroy_copy_less(void* in)
{
  ((user_defined_type_init_destroy_copy_less*) in)->b = cstl_alloc(int, 32);
  //printf("init alloc = %x\n", ((user_defined_type_init_destroy_copy_less*) in)->b);
  memset(((user_defined_type_init_destroy_copy_less*) in)->b, 0, 32 * sizeof(int));
  ((user_defined_type_init_destroy_copy_less*) in)->a = 32;
  memset(((user_defined_type_init_destroy_copy_less*) in)->c, 0, 32);
}
static void func_ctor_copy_user_defined_type_init_destroy_copy_less(void* in, void* in_)
{
  //assert(in != in_);
  if (in == in_)
    return;

  ((user_defined_type_init_destroy_copy_less*) in)->b = cstl_alloc(int,
      ((user_defined_type_init_destroy_copy_less* )in_)->a);
  //printf("copy alloc = %x\n", ((user_defined_type_init_destroy_copy_less*) in)->b);
  cstl_memcpy(((user_defined_type_init_destroy_copy_less*) in)->b, ((user_defined_type_init_destroy_copy_less*) in_)->b,
      ((user_defined_type_init_destroy_copy_less*) in_)->a * sizeof(int));
  ((user_defined_type_init_destroy_copy_less*) in)->a = ((user_defined_type_init_destroy_copy_less*) in_)->a;
  cstl_memcpy(((user_defined_type_init_destroy_copy_less*) in)->c, ((user_defined_type_init_destroy_copy_less*) in_)->c,
      32);
}
static void func_ctor_move_user_defined_type_init_destroy_copy_less(void* in, void* in_)
{
  //assert(in != in_);
  if (in == in_)
    return;
  ((user_defined_type_init_destroy_copy_less*) in_)->b = 0;

  ((user_defined_type_init_destroy_copy_less*) in)->b = cstl_alloc(int,
      ((user_defined_type_init_destroy_copy_less* )in_)->a);
  //printf("copy alloc = %x\n", ((user_defined_type_init_destroy_copy_less*) in)->b);
  cstl_memcpy(((user_defined_type_init_destroy_copy_less*) in)->b, ((user_defined_type_init_destroy_copy_less*) in_)->b,
      ((user_defined_type_init_destroy_copy_less*) in_)->a * sizeof(int));
  ((user_defined_type_init_destroy_copy_less*) in)->a = ((user_defined_type_init_destroy_copy_less*) in_)->a;
  cstl_memcpy(((user_defined_type_init_destroy_copy_less*) in)->c, ((user_defined_type_init_destroy_copy_less*) in_)->c,
      32);
}
static void func_opt_assign_copy_user_defined_type_init_destroy_copy_less(void* in, void* in_)
{
  //assert(in != in_);
  if (in == in_)
    return;

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
static void func_opt_assign_move_user_defined_type_init_destroy_copy_less(void* in, void* in_)
{
  //assert(in != in_);
  if (in == in_)
    return;
  ((user_defined_type_init_destroy_copy_less*) in_)->b = 0;

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
static void func_destroy_user_defined_type_init_destroy_copy_less(void* in)
{
  //printf("destroy alloc = %x\n", ((user_defined_type_init_destroy_copy_less*) in)->b);
  cstl_free(((user_defined_type_init_destroy_copy_less* )in)->b);
}
static int func_less_user_defined_type_init_destroy_copy_less(void* in, void* in_)
{
  int a = ((user_defined_type_init0_destroy0_copy0_less*) in)->a;
  int b = ((user_defined_type_init0_destroy0_copy0_less*) in_)->a;
  if (a < b)
    return -1;
  else if (a > b)
    return 1;
  else
    return 0;
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
  vector_dtor(&zmdcstlvec_);

  std::vector<user_defined_type_init_destroy_copy_less> stdvec_(size, v);
  profile_start(std_vector_ctor_vector);
  std::vector<user_defined_type_init_destroy_copy_less> stdvec(stdvec_);
  profile_end_ms(std_vector_ctor_vector);

  profile_ratio(cstl_vector_ctor_vector, std_vector_ctor_vector);
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
TEST benchmark_vector_reserve(void)
{
  user_defined_type_init_destroy_copy_less firstv;
  user_defined_type_init0_destroy0_copy0_less secondv;
  uint32_t v = 100;

  vector_t pvec_vector;
  vector_ctor_n_v(&pvec_vector, size, &firstv, 1, user_defined_non_pod_id);
  profile_start(cstlvec_reserve_non_pod);
  vector_reserve_n(&pvec_vector, vector_capacity(&pvec_vector) + 1);
  profile_end_ms(cstlvec_reserve_non_pod);
  vector_dtor(&pvec_vector);

  std::vector<user_defined_type_init_destroy_copy_less> stdvec_(size, firstv);
  profile_start(stdvec_reserve_non_pod);
  stdvec_.reserve(stdvec_.capacity() + 1);
  profile_end_ms(stdvec_reserve_non_pod);

  profile_ratio(cstlvec_reserve_non_pod, stdvec_reserve_non_pod);
  printf("\n");

  vector_t pvec_vector1;
  vector_ctor_n_v(&pvec_vector1, size, &secondv, 1, user_defined_pod_id);
  profile_start(cstlvec_reserve_pod);
  vector_reserve_n(&pvec_vector1, vector_capacity(&pvec_vector1) + 1);
  profile_end_ms(cstlvec_reserve_pod);
  vector_dtor(&pvec_vector1);

  std::vector<user_defined_type_init0_destroy0_copy0_less> stdvec1(size, secondv);
  profile_start(stdvec_reserve_pod);
  stdvec1.reserve(stdvec1.capacity() + 1);
  profile_end_ms(stdvec_reserve_pod);

  profile_ratio(cstlvec_reserve_pod, stdvec_reserve_pod);
  printf("\n");

  vector_t pvec_vector2;
  vector_ctor_n_v(&pvec_vector2, size, &v, 1, cstl_uint32);
  profile_start(cstlvec_reserve_ctype);
  vector_reserve_n(&pvec_vector2, vector_capacity(&pvec_vector2) + 1);
  profile_end_ms(cstlvec_reserve_ctype);
  vector_dtor(&pvec_vector2);

  std::vector<uint32_t> stdvec2(size, v);
  profile_start(stdvec_reserve_ctype);
  stdvec2.reserve(stdvec2.capacity() + 1);
  profile_end_ms(stdvec_reserve_ctype);

  profile_ratio(cstlvec_reserve_ctype, stdvec_reserve_ctype);
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
  printf("\n");
  RUN_TEST(benchmark_vector_reserve);
  printf("\n");
}

TEST how_std_vector_opt_assign_works(void)
{
  std::vector<int> nums1 { 3, 1, 4, 6, 5, 9 };
  std::vector<int> nums2;
  std::vector<int> nums3;

  // copy assignment copies data from nums1 to nums2
  nums2 = nums1;
  printf("cpy assign: nums1 capacity = %lu, data = %p\n", nums1.capacity(), nums1.data());

  // move assignment moves data from nums1 to nums3,
  // modifying both nums1 and nums3
  printf("move assign: nums1 capacity = %lu, data = %p\n", nums1.capacity(), nums1.data());
  auto tmp = std::move(nums1);
  printf("move assign: nums1 capacity = %lu, data = %p\n", nums1.capacity(), nums1.data());
  nums3 = tmp;
  printf("move assign: nums1 capacity = %lu, data = %p\n", nums1.capacity(), nums1.data());
  printf("move assign: nums3 capacity = %lu, data = %p\n", nums3.capacity(), nums3.data());
  PASS();
}

TEST how_std_fill_n_works(void)
{
  user_defined_type_init_destroy_copy_less v1;
  user_defined_type_init_destroy_copy_less v2;
  user_defined_type_init_destroy_copy_less v3;
  std::vector<user_defined_type_init_destroy_copy_less> v { v1, v2 };
  std::fill_n(v.begin(), 1, v3); // fill_n will internally call opt assign
  PASS();
}
TEST how_std_vector_erase_works(void)
{
  user_defined_type_init_destroy_copy_less v1;
  std::vector<user_defined_type_init_destroy_copy_less> myvector;
  myvector.reserve(10); // reserve void memory alloc
  for (int i = 1; i <= 5; i++)
  {
    v1.id = i;
    myvector.push_back(v1);
  }
  v1.id = 0;
  // 12378
  // 1 3 4 4
  std::cout << myvector.size() << std::endl;
  // earse willuse move if  move opt= is given
  // otherwise it will use copy ctor thas is much slower
  auto pos = myvector.erase(myvector.begin() + 1, myvector.begin() + 2);
  std::cout << "pos: " << pos - myvector.begin() << ", val: " << pos->id << std::endl;
  std::cout << myvector.size() << std::endl;
  PASS();
}
TEST how_vector_erase_element_in_loop(void)
{
  user_defined_type_init_destroy_copy_less v1;
  std::vector<user_defined_type_init_destroy_copy_less> myvector;
  myvector.reserve(10); // reserve void memory alloc
  for (int i = 1; i <= 5; i++)
  {
    v1.id = i;
    myvector.push_back(v1);
  }
  v1.id = 0;
  for (auto it = myvector.begin(); it != myvector.end();)
  {
    if (it->id == 3)
    {
      std::cout << "pos:" << it - myvector.begin() << ", v: " << it->id << std::endl;
      it = myvector.erase(it); //
      std::cout << "pos:" << it - myvector.begin(); 			//pos:2, v : 3
      if (it == myvector.end())
        std::cout << ", end no value: " << std::endl;
      else
        std::cout << ", v: " << it->id << std::endl; 			//	pos : 2, v : 4
      // as you can see memory pos never change but the value in the memory changes as we do shit elements
    }
    else
      it++;
  }
  PASS();
}
TEST how_std_move_and_move_backwards_work(void)
{
  std::vector<int> src { 0, 1, 2, 3, 4 };
  std::vector<int> dest { 5, 6, 7, 8 };

  std::cout << "src: ";
  for (const auto &s : src)
  {
    std::cout << s << ' ';
  }
  std::cout << "\ndest: ";
  for (const auto &s : dest)
  {
    std::cout << s << ' ';
  }
  std::cout << '\n';

  auto itr = std::move_backward(src.begin() + 1, src.end() - 1, src.end());
  // this can apprive iter is pointing to the second 1
  std::cout << *itr << "\n"; // print 1
  itr++;
  std::cout << *(itr) << "\n"; // print 2

  std::cout << "src: ";
  for (const auto &s : src)
  {
    std::cout << s << ' ';
  }
  std::cout << "\ndest: ";
  for (const auto &s : dest)
  {
    std::cout << s << ' ';
  }
  std::cout << '\n';
  PASS();
}

// memory access ordering is fixed no matter little endian or big endian
// inta; int b; a must be in the front of b
// but this "front" may be in right side of when loading from mepry to register in little endian system
// while in left side of when loading from mepry to register in big endian system
// as little endian cpu will reverse byte orders.
// printf(%x) will show hex codes in register it may not be same to the order in memory
// bit operation is always doen on register level, in order words, on value expression
typedef struct
{
    //int dd;
    int a :3;
    int b :2;
    int c :3;
    int d;
} bit;
TEST test_printf_wrong_type(void)
{
  unsigned short a = 10;
  // a= 0000 1010 after ~, a= 2base: 1111 0101 = 10base: -11, cast to %u unsigned int type,
  // ~a = 1111 1111 1111 0101, then print it to a very large number
  printf("~a = %u\n", ~a);
  // b = 1000 0000
  char b = 128;
  int c = b;
  printf("c=%d\n", c);
  PASS();
}
TEST test_bit_field(void)
{
  // 10011001
  bit s = {0};
  char *c = (char*) &s;
  std::cout << "sizeof(bit) = " << sizeof(bit) << endl;
  *c = 0x89;
  for(int i = 0; i < sizeof(bit); i++)
    printf("c[%d]: %x\n",i, (unsigned char)c[i]);
  printf("bit: %x\n", s);
  std::cout << s.a << endl << s.b << endl << s.c << endl;
  int a = -1;
  printf("%x\n", a);
  PASS();
}
int main(int argc, char **argv)
{
  init_types(0);

  user_defined_pod_id = register_type(sizeof(user_defined_type_init0_destroy0_copy0_less),
  CSTL_ALIGN_OF(user_defined_type_init0_destroy0_copy0_less), 0, 0, 0, 0, 0, 0, 0,
      func_less_user_defined_type_init0_destroy0_copy0_less);

  user_defined_non_pod_id = register_type(sizeof(user_defined_type_init_destroy_copy_less),
  CSTL_ALIGN_OF(user_defined_type_init_destroy_copy_less), func_destroy_user_defined_type_init_destroy_copy_less,
      func_init_user_defined_type_init_destroy_copy_less, 0, func_ctor_copy_user_defined_type_init_destroy_copy_less,
      func_ctor_move_user_defined_type_init_destroy_copy_less,
      func_opt_assign_copy_user_defined_type_init_destroy_copy_less,
      func_opt_assign_move_user_defined_type_init_destroy_copy_less,
      func_less_user_defined_type_init_destroy_copy_less);

  /* command-line options, initialization. */
  GREATEST_MAIN_BEGIN();
  printf("elements size used in all test cases: 5M\n");

  /* Individual tests can be run directly in main, outside of suites.*/
  //RUN_TEST(how_std_vector_opt_assign_works);
  //RUN_TEST(how_std_fill_n_works);
  //RUN_TEST(how_std_move_and_move_backwards_work);
  //RUN_TEST(how_std_vector_erase_works);
  //RUN_TEST(how_vector_erase_element_in_loop);
  RUN_TEST(test_bit_field);
  /* Tests can also be gathered into test suites. */
  //RUN_SUITE(benchmark_vector);

  GREATEST_MAIN_END(); /* display results */
  destroy_types();
}
