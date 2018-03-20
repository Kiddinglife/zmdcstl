
#include "greatest.h"
#include "../zmdcstl/cstl_alloc.h"
#include "../zmdcstl/cstl_vector.h"

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
  destroy_types();

  GREATEST_MAIN_END(); /* display results */
}
