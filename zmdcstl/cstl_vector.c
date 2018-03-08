#include "cstl_vector.h"
#include "cstl_types.h"

// map_t<vector_t<int>, list<string>>
vector_t* create_vector(int size, ...)
{
    /* allocate for vector_t and initialize it */
    assert(size <= TYPE_ID_SIZE);

    vector_t*   pvec_vector;
    va_list a_list;

    init_types();

    if ((pvec_vector = (vector_t*)malloc(sizeof(vector_t))) == NULL)
        return NULL;
    pvec_vector->_pby_finish = pvec_vector->_pby_start = pvec_vector->_pby_endofstorage = NULL;

    va_start(a_list, size);
    for (int x = 0; x < size; x++)
        pvec_vector->_t_typeinfo._t_typeids[x] = va_arg(a_list, int);
    pvec_vector->_t_typeinfo._t_typeidsize = size;
    pvec_vector->_t_typeinfo._t_type = _apt_bucket[pvec_vector->_t_typeinfo._t_typeids[0]];
    va_end(a_list);

    return pvec_vector;
}
