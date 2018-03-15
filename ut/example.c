#include "greatest.h"

#include "../zmdcstl/cstl_alloc.h"

/* A test runs various assertions, then calls PASS(), FAIL(), or SKIP(). */
TEST test_cstl_alloc_free(void)
{
    int* x;
    for (int i = 0; i < 1000000; i++)
    {
        x = (int*) cstl_alloc(int, 2);
        *x = 100;
        *(x + 1) = 200;
        cstl_free(x);
    }
    PASS()
    ;
}

/* Suites can group multiple tests with common setup. */
SUITE(suit_cstl_alloc)
{
    RUN_TEST(test_cstl_alloc_free);
}

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS()
;

int main(int argc, char **argv)
{
    GREATEST_MAIN_BEGIN()
    ; /* command-line options, initialization. */

    /* Individual tests can be run directly in main, outside of suites. */
    /* RUN_TEST(x_should_equal_1); */

    /* Tests can also be gathered into test suites. */
    RUN_SUITE(suit_cstl_alloc);

    GREATEST_MAIN_END()
    ; /* display results */
}
