#include "cstl_vector.h"
#include "cstl_types.h"

bool vector_is_inited(const vector_t* cpvec_vector)
{
    if (cpvec_vector == NULL)
        return false;
    if (cpvec_vector->_t_typeinfo._pt_type == NULL)
        return false;
    if (cpvec_vector->_t_typeinfo._pt_type->_t_style <= ctype
        && cpvec_vector->_t_typeinfo._pt_type->_t_style >= invalidtype)
        return false;
    if (cpvec_vector->_pby_start == NULL && cpvec_vector->_pby_finish == NULL && cpvec_vector->_pby_endofstorage == NULL)
        return true;
    if (cpvec_vector->_pby_start != NULL && cpvec_vector->_pby_finish != NULL && cpvec_vector->_pby_endofstorage != NULL
        && cpvec_vector->_pby_finish >= cpvec_vector->_pby_start
        && cpvec_vector->_pby_endofstorage >= cpvec_vector->_pby_start
        && cpvec_vector->_pby_endofstorage >= cpvec_vector->_pby_finish)
        return true;
    return false;
}

bool vector_iterator_valid(const vector_t* cpvec_vector, vector_iterator_t* it_iter)
{
    if (vector_is_inited(cpvec_vector) &&
        _VECTOR_ITERATOR_ITERATOR_TYPE(it_iter) == _RANDOM_ACCESS_ITERATOR &&
        _VECTOR_ITERATOR_CONTAINER_TYPE(it_iter) == _VECTOR_CONTAINER &&
        _VECTOR_ITERATOR_CONTAINER(it_iter) == cpvec_vector &&
        _VECTOR_ITERATOR_COREPOS(it_iter) >= cpvec_vector->_pby_start &&
        _VECTOR_ITERATOR_COREPOS(it_iter) <= cpvec_vector->_pby_finish)
        return true;
    return false;
}

void create_vector_iterator(vector_iterator_t* it_iter)
{
    _VECTOR_ITERATOR_COREPOS(it_iter) = NULL;
    _ITERATOR_CONTAINER(it_iter) = NULL;
    _VECTOR_ITERATOR_CONTAINER_TYPE(it_iter) = _VECTOR_CONTAINER;
    _VECTOR_ITERATOR_ITERATOR_TYPE(it_iter) = _RANDOM_ACCESS_ITERATOR;
}

/**
 * Get the iterator that reference next data.
 */
void vector_iterator_next(vector_iterator_t* it_iter)
{
    assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_iter), it_iter));
    _VECTOR_ITERATOR_COREPOS(it_iter) += _GET_VECTOR_TYPE_SIZE(_VECTOR_ITERATOR_CONTAINER(it_iter));
    assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_iter), it_iter));
}

// map_t<vector_t<int>, list<string>>
vector_t* create_vector(int size, ...)
{
    /* allocate for vector_t and initialize it */
    assert(size <= TYPE_ID_SIZE);

    vector_t* pvec_vector;
    va_list a_list;

    init_types();

    if ((pvec_vector = (vector_t*)malloc(sizeof(vector_t))) == NULL)
        return NULL;
    pvec_vector->_pby_finish = pvec_vector->_pby_start = pvec_vector->_pby_endofstorage = NULL;

    va_start(a_list, size);
    for (int x = 0; x < size; x++)
        pvec_vector->_t_typeinfo._t_typeids[x] = va_arg(a_list, int);
    pvec_vector->_t_typeinfo._t_typeidsize = size;
    pvec_vector->_t_typeinfo._pt_type = _apt_bucket[pvec_vector->_t_typeinfo._t_typeids[0]];
    va_end(a_list);

    return pvec_vector;
}

void vector_end(const vector_t* cpvec_vector, vector_iterator_t* it_end)
{
    assert(cpvec_vector != NULL);
    assert(vector_is_inited(cpvec_vector));
    _VECTOR_ITERATOR_CONTAINER_TYPE(it_end) = _VECTOR_CONTAINER;
    _VECTOR_ITERATOR_ITERATOR_TYPE(it_end) = _RANDOM_ACCESS_ITERATOR;
    _ITERATOR_CONTAINER(it_end) = cpvec_vector;
    _VECTOR_ITERATOR_COREPOS(it_end) = cpvec_vector->_pby_finish;
}

void vector_end_again(vector_iterator_t* it_end)
{
    assert(it_end != NULL);
    assert((vector_t*)it_end->_pt_container != NULL);
    assert(vector_is_inited((vector_t*)it_end->_pt_container));
    _VECTOR_ITERATOR_COREPOS(it_end) = ((vector_t*)it_end->_pt_container)->_pby_finish;
}

bool vector_iterator_equal(vector_iterator_t* it_first, vector_iterator_t* it_second)
{
    assert(iterator_same_type(it_first, it_second));
    assert(_VECTOR_ITERATOR_CONTAINER(it_first) == _VECTOR_ITERATOR_CONTAINER(it_second));
    assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_first), it_first));
    assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_second), it_second));
    return _VECTOR_ITERATOR_COREPOS(it_first) == _VECTOR_ITERATOR_COREPOS(it_second);
}

void vector_iterator_get_value(vector_iterator_t* it_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_iter), it_iter));
    assert((void*)it_iter->_t_pos != _VECTOR_ITERATOR_CONTAINER(it_iter)->_pby_finish);
    size_t size = 0;
    //if (_VECTOR_ITERATOR_CONTAINER(it_iter)->_t_typeinfo._pt_type->_t_typeid == cstr)
    //{
    // TODO
    //}
    //else
    {
        size = _GET_VECTOR_TYPE_SIZE(_VECTOR_ITERATOR_CONTAINER(it_iter));
        _GET_VECTOR_TYPE_COPY_FUNCTION(_VECTOR_ITERATOR_CONTAINER(it_iter))(pv_value, _VECTOR_ITERATOR_COREPOS(it_iter), &size);
        assert(size);
    }
}
