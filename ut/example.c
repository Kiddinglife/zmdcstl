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
        ASSERT_EQ(*x, 100)
        ;
        ASSERT_EQ(*(x+1), 200)
        ;
        cstl_free(x);
    }
    PASS()
    ;
}
SUITE(test_cstl_alloc)
{
    RUN_TEST(test_cstl_alloc_free);
}

#include "../zmdcstl/cstl_vector.h"
TEST test_vector_ctor_scalar_type(void)
{
    vector_t pvec_vector;
    vector_ctor(&pvec_vector, 1, cstl_uint32);
    ASSERT_EQ(pvec_vector._pby_finish, NULL )
    ;
    ASSERT_EQ(pvec_vector._pby_start, NULL )
    ;
    ASSERT_EQ(pvec_vector._pby_endofstorage, NULL )
    ;
    ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER )
    ;
    ASSERT_EQ(pvec_vector.meta._t_iteratortype, _RANDOM_ACCESS_ITERATOR )
    ;
    ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeids[0], cstl_uint32)
    ;
    ASSERT_EQ(pvec_vector.meta._t_typeinfo._pt_type, _apt_bucket[pvec_vector.meta._t_typeinfo._t_typeids[0]])
    ;
    ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1)
    ;
    vector_dtor(&pvec_vector);

    PASS()
    ;
}
TEST test_vector_ctor_n_scalar_type(void)
{
    vector_t pvec_vector;
    vector_ctor_n(&pvec_vector, 1, 1, cstl_uint32);
    ASSERT_EQ(pvec_vector._pby_start, pvec_vector._pby_finish)
    ;;
    ASSERT_EQ(pvec_vector._pby_endofstorage - pvec_vector._pby_start, pvec_vector.meta._t_typeinfo._pt_type->_t_typesize)
    ;
    ASSERT_FALSE(pvec_vector._pby_endofstorage == NULL)
    ;
    ASSERT_EQ(pvec_vector.meta._t_containertype, _VECTOR_CONTAINER )
    ;
    ASSERT_EQ(pvec_vector.meta._t_iteratortype, _RANDOM_ACCESS_ITERATOR )
    ;
    ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeids[0], cstl_uint32)
    ;
    ASSERT_EQ(pvec_vector.meta._t_typeinfo._pt_type, _apt_bucket[pvec_vector.meta._t_typeinfo._t_typeids[0]])
    ;
    ASSERT_EQ(pvec_vector.meta._t_typeinfo._t_typeidsize, 1)
    ;
    vector_dtor(&pvec_vector);

    PASS()
    ;
}

SUITE(test_vector)
{
    RUN_TEST(test_vector_ctor_scalar_type);
    RUN_TEST(test_vector_ctor_n_scalar_type);
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
    RUN_SUITE(test_cstl_alloc);
    RUN_SUITE(test_vector);

    GREATEST_MAIN_END()
    ; /* display results */
}
