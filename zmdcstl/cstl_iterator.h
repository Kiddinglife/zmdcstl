/*
 * cstl_iterator.h
 *
 *  Created on: 7 Mar. 2018
 *      Author: jackiez
 */

#ifndef MYCSTL_CSTL_ITERATOR_H_
#define MYCSTL_CSTL_ITERATOR_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "cstl_def.h"

/* vector iterator handler */
#define _VECTOR_ITERATOR_COREPOS(it_iter)               ((it_iter)._t_pos._pby_corepos)
#define _VECTOR_ITERATOR_CONTAINER(it_iter)             ((vector_t*)((it_iter)._pt_container))
#define _VECTOR_ITERATOR_CONTAINER_TYPE(it_iter)        ((it_iter)._t_containertype)
#define _VECTOR_ITERATOR_ITERATOR_TYPE(it_iter)         ((it_iter)._t_iteratortype)
/* list iterator handler */
#define _LIST_ITERATOR_COREPOS(it_iter)                 ((it_iter)._t_pos._pby_corepos)
#define _LIST_ITERATOR_CONTAINER(it_iter)               ((list_t*)((it_iter)._pt_container))
#define _LIST_ITERATOR_CONTAINER_TYPE(it_iter)          ((it_iter)._t_containertype)
#define _LIST_ITERATOR_ITERATOR_TYPE(it_iter)           ((it_iter)._t_iteratortype)
/* deque iterator handler */
#define _DEQUE_ITERATOR_MAP_POINTER(it_iter)            ((it_iter)._t_pos._t_dequepos._ppby_mappos)
#define _DEQUE_ITERATOR_FIRST_POS(it_iter)              ((it_iter)._t_pos._t_dequepos._pby_first)
#define _DEQUE_ITERATOR_AFTERLAST_POS(it_iter)          ((it_iter)._t_pos._t_dequepos._pby_afterlast)
#define _DEQUE_ITERATOR_COREPOS(it_iter)                ((it_iter)._t_pos._t_dequepos._pby_corepos)
#define _DEQUE_ITERATOR_CONTAINER(it_iter)              ((deque_t*)((it_iter)._pt_container))
#define _DEQUE_ITERATOR_CONTAINER_TYPE(it_iter)         ((it_iter)._t_containertype)
#define _DEQUE_ITERATOR_ITERATOR_TYPE(it_iter)          ((it_iter)._t_iteratortype)
/* slist iterator handler */
#define _SLIST_ITERATOR_COREPOS(it_iter)                ((it_iter)._t_pos._pby_corepos)
#define _SLIST_ITERATOR_CONTAINER(it_iter)              ((slist_t*)((it_iter)._pt_container))
#define _SLIST_ITERATOR_CONTAINER_TYPE(it_iter)         ((it_iter)._t_containertype)
#define _SLIST_ITERATOR_ITERATOR_TYPE(it_iter)          ((it_iter)._t_iteratortype)
/* avl_tree iterator handler */
#define _AVL_TREE_ITERATOR_COREPOS(it_iter)             ((it_iter)._t_pos._t_treepos._pby_corepos)
#define _AVL_TREE_ITERATOR_TREE(it_iter)                ((_avl_tree_t*)((it_iter)._t_pos._t_treepos._pt_tree))
#define _AVL_TREE_ITERATOR_TREE_POINTER(it_iter)        ((it_iter)._t_pos._t_treepos._pt_tree)
/* rb_tree iterator handler */
#define _RB_TREE_ITERATOR_COREPOS(it_iter)              ((it_iter)._t_pos._t_treepos._pby_corepos)
#define _RB_TREE_ITERATOR_TREE(it_iter)                 ((_rb_tree_t*)((it_iter)._t_pos._t_treepos._pt_tree))
#define _RB_TREE_ITERATOR_TREE_POINTER(it_iter)         ((it_iter)._t_pos._t_treepos._pt_tree)
/* set iterator handler */
#define _SET_ITERATOR_CONTAINER(it_iter)                ((set_t*)((it_iter)._pt_container))
#define _SET_ITERATOR_CONTAINER_TYPE(it_iter)           ((it_iter)._t_containertype)
#define _SET_ITERATOR_ITERATOR_TYPE(it_iter)            ((it_iter)._t_iteratortype)
/* multiset iterator handler */
#define _MULTISET_ITERATOR_CONTAINER(it_iter)           ((multiset_t*)((it_iter)._pt_container))
#define _MULTISET_ITERATOR_CONTAINER_TYPE(it_iter)      ((it_iter)._t_containertype)
#define _MULTISET_ITERATOR_ITERATOR_TYPE(it_iter)       ((it_iter)._t_iteratortype)
/* map iterator handler */
#define _MAP_ITERATOR_CONTAINER(it_iter)                ((map_t*)((it_iter)._pt_container))
#define _MAP_ITERATOR_CONTAINER_TYPE(it_iter)           ((it_iter)._t_containertype)
#define _MAP_ITERATOR_ITERATOR_TYPE(it_iter)            ((it_iter)._t_iteratortype)
/* multimap iterator handler */
#define _MULTIMAP_ITERATOR_CONTAINER(it_iter)           ((multimap_t*)((it_iter)._pt_container))
#define _MULTIMAP_ITERATOR_CONTAINER_TYPE(it_iter)      ((it_iter)._t_containertype)
#define _MULTIMAP_ITERATOR_ITERATOR_TYPE(it_iter)       ((it_iter)._t_iteratortype)
/* hashtable iterator handler */
#define _HASHTABLE_ITERATOR_BUCKETPOS(it_iter)          ((it_iter)._t_pos._t_hashpos._pby_bucketpos)
#define _HASHTABLE_ITERATOR_COREPOS(it_iter)            ((it_iter)._t_pos._t_hashpos._pby_corepos)
#define _HASHTABLE_ITERATOR_HASHTABLE(it_iter)          ((_hashtable_t*)((it_iter)._t_pos._t_hashpos._pt_hashtable))
#define _HASHTABLE_ITERATOR_HASHTABLE_POINTER(it_iter)  ((it_iter)._t_pos._t_hashpos._pt_hashtable)
/* hash_set iterator handler */
#define _HASH_SET_ITERATOR_CONTAINER(it_iter)           ((hash_set_t*)((it_iter)._pt_container))
#define _HASH_SET_ITERATOR_CONTAINER_TYPE(it_iter)      ((it_iter)._t_containertype)
#define _HASH_SET_ITERATOR_ITERATOR_TYPE(it_iter)       ((it_iter)._t_iteratortype)
/* hash_multiset iterator handler */
#define _HASH_MULTISET_ITERATOR_CONTAINER(it_iter)      ((hash_multiset_t*)((it_iter)._pt_container))
#define _HASH_MULTISET_ITERATOR_CONTAINER_TYPE(it_iter) ((it_iter)._t_containertype)
#define _HASH_MULTISET_ITERATOR_ITERATOR_TYPE(it_iter)  ((it_iter)._t_iteratortype)
/* hash_map iterator handler */
#define _HASH_MAP_ITERATOR_CONTAINER(it_iter)           ((hash_map_t*)((it_iter)._pt_container))
#define _HASH_MAP_ITERATOR_CONTAINER_TYPE(it_iter)      ((it_iter)._t_containertype)
#define _HASH_MAP_ITERATOR_ITERATOR_TYPE(it_iter)       ((it_iter)._t_iteratortype)
/* hash_multimap iterator handler */
#define _HASH_MULTIMAP_ITERATOR_CONTAINER(it_iter)      ((hash_multimap_t*)((it_iter)._pt_container))
#define _HASH_MULTIMAP_ITERATOR_CONTAINER_TYPE(it_iter) ((it_iter)._t_containertype)
#define _HASH_MULTIMAP_ITERATOR_ITERATOR_TYPE(it_iter)  ((it_iter)._t_iteratortype)
/* basic_string iterator handler */
#define _BASIC_STRING_ITERATOR_COREPOS(it_iter)         ((it_iter)._t_pos._pby_corepos)
#define _BASIC_STRING_ITERATOR_CONTAINER(it_iter)       ((basic_string_t*)((it_iter)._pt_container))
#define _BASIC_STRING_ITERATOR_CONTAINER_TYPE(it_iter)  ((it_iter)._t_containertype)
#define _BASIC_STRING_ITERATOR_ITERATOR_TYPE(it_iter)   ((it_iter)._t_iteratortype)
/* for all container iterator */
#define _ITERATOR_CONTAINER(it_iter)                    ((it_iter)._pt_container)
#define _ITERATOR_CONTAINER_TYPE(it_iter)               ((it_iter)._t_containertype)
#define _ITERATOR_ITERATOR_TYPE(it_iter)                ((it_iter)._t_iteratortype)
#define _STRING_CONTAINER        _BASIC_STRING_CONTAINER

typedef enum _tagcontainertype
{
  _VECTOR_CONTAINER,
  _LIST_CONTAINER,
  _DEQUE_CONTAINER,
  _SLIST_CONTAINER,
  _MAP_CONTAINER,
  _MULTIMAP_CONTAINER,
  _SET_CONTAINER,
  _MULTISET_CONTAINER,
  _HASH_SET_CONTAINER,
  _HASH_MULTISET_CONTAINER,
  _HASH_MAP_CONTAINER,
  _HASH_MULTIMAP_CONTAINER,
  _BASIC_STRING_CONTAINER
} containertype_t;

/* iterator type */
typedef enum _tagiteratortype
{
  _INPUT_ITERATOR, _OUTPUT_ITERATOR, _FORWARD_ITERATOR, _BIDIRECTIONAL_ITERATOR, _RANDOM_ACCESS_ITERATOR
} iteratortype_t;

typedef struct _tagvector_iterator_t
{

} vector_iterator_t;
typedef struct _taglist_iterator_t
{

} list_iterator_t;

typedef struct _tagiterator
{
  void* _pt_container;
  containertype_t _t_containertype;
  iteratortype_t _t_iteratortype;

  /* flexibility for all containter */
  union
  {
    _byte_t* _pby_corepos; /* for vector list e.g. */
    struct
    { /* for deque */
      _byte_t* _pby_corepos;
      _byte_t* _pby_first;
      _byte_t* _pby_afterlast; /* the node after the last node */
      _byte_t** _ppby_mappos; /* point to the map */
    } _t_dequepos;
    struct
    { /* for avl tree or rb tree */
      _byte_t* _pby_corepos;
      void* _pt_tree; /* point to the avl tree or rb tree*/
    } _t_treepos;
    struct /* for hash table */
    {
      _byte_t* _pby_corepos;
      _byte_t* _pby_bucketpos; /* pointer to vector bucket position */
      void* _pt_hashtable; /* point to hash node */
    } _t_hashpos;
  } _t_pos;
} iterator_t;

typedef struct _tagrange
{
  iterator_t* it_begin;
  iterator_t* it_end;
} range_t;

/* declaration five iterator type */
typedef iterator_t input_iterator_t;
typedef iterator_t output_iterator_t;
typedef input_iterator_t forward_iterator_t;
typedef forward_iterator_t bidirectional_iterator_t;
typedef bidirectional_iterator_t random_access_iterator_t;

/* declaration four iterator adapters */
typedef iterator_t reverse_iterator_t;
typedef output_iterator_t insert_iterator_t;
typedef input_iterator_t istream_iterator_t;
typedef output_iterator_t ostream_iterator_t;

/**
 * Test whether the iterator is valid.
 * @param it_iter      iterator.
 * @return whether iterator is valid.
 */
#define iterator_is_valid(it_iter)\
((it_iter->_t_containertype >= _VECTOR_CONTAINER && it_iter->_t_containertype <= _BASIC_STRING_CONTAINER)\
    && (it_iter->_t_iteratortype >= _INPUT_ITERATOR && it_iter->_t_iteratortype <= _RANDOM_ACCESS_ITERATOR))

/**
 * Get pointer that pointed by iterator, but ignore char*.
 * @param it_iter      iterator.
 * @return pointer
 * @remakes it_iter must be valid and must be not end(), otherwise the behavior is undefined.
 */
#define iterator_same_type(it_first,it_second)\
assert(iterator_is_valid(it_first));\
assert(iterator_is_valid(it_second));\
if (it_first->_t_containertype == it_second->_t_containertype && \
it_first->_t_iteratortype == it_second->_t_iteratortype) \
    return true;\
else \
    return false;

/**
 * Test whether the iterator type of restriction.
 * @param it_iter      iterator.
 * @param t_limittype  restriction type.
 * @return wehter the iterator type of restriction.
 * @remarks the iterator must be valid, otherwise behavior is undefined. restriction type must be valid
 *          iterator type, otherwise behavior is undefined.
 */
extern bool iterator_limit_type(iterator_t* it_iter, iteratortype_t t_limittype);

/**
 * Get pointer that pointed by iterator, but ignore char*.
 * @param it_iter      iterator.
 * @return pointer
 * @remakes it_iter must be valid and must be not end(), otherwise the behavior is undefined.
 */
extern const void* iterator_get_pointer_ignore_cstr(iterator_t* it_iter);

#ifdef __cplusplus
}
#endif

#endif /* MYCSTL_CSTL_ITERATOR_H_ */
