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
#include "cstl_types.h"

    /* vector iterator handler */
#define _VECTOR_ITERATOR_COREPOS(it_iter)               ((it_iter)->_t_pos)
#define _VECTOR_ITERATOR_CONTAINER(it_iter)             ((vector_t*)((it_iter)->_pt_container))
#define _VECTOR_ITERATOR_CONTAINER_TYPE(it_iter)     (((meta_t*)((it_iter)->_pt_container))->_t_containertype)
#define _VECTOR_ITERATOR_ITERATOR_TYPE(it_iter)         (((meta_t*)((it_iter)->_pt_container))->_t_iteratortype)
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
#define _ITERATOR_CONTAINER(it_iter)                    ((it_iter)->_pt_container)
#define _ITERATOR_META_TYPE(it_iter)                       ((meta_t*)((it_iter)->_pt_container))
#define _ITERATOR_CONTAINER_TYPE(it_iter)             (((meta_t*)((it_iter)->_pt_container))->_t_containertype)
#define _ITERATOR_ITERATOR_TYPE(it_iter)                 (((meta_t*)((it_iter)->_pt_container))->_t_iteratortype)
#define _ITERATOR_TYPE_INFO(it_iter)                 (((meta_t*)((it_iter)->_pt_container))->_t_typeinfo)
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
        _INPUT_ITERATOR,
        _OUTPUT_ITERATOR,
        _FORWARD_ITERATOR,
        _BIDIRECTIONAL_ITERATOR,
        _RANDOM_ACCESS_ITERATOR,
        _CONTIGUOUS_ITERTOR
        // Extension to the C++ standard. Contiguous ranges
        // are more than random access, they are physically contiguous.
    } iteratortype_t;

    /// iterator_status_flag
    ///
    /// Defines the validity status of an iterator. This is primarily used for
    /// iterator validation in debug builds. These are implemented as OR-able
    /// flags (as opposed to mutually exclusive values) in order to deal with
    /// the nature of iterator status. In particular, an iterator may be valid
    /// but not dereferencable, as in the case with an iterator to container end().
    /// An iterator may be valid but also dereferencable, as in the case with an
    /// iterator to container begin().
    ///
    typedef enum
    {
        /// This is called none and not called invalid because it is not strictly the opposite of invalid.
        isf_none = 0x00,
        /// The iterator is valid, which means it is in the range of [begin, end].
        isf_valid = 0x01,
        /// The iterator is valid and points to the same element it did when created.
        /// For example, if an iterator points to vector::begin() but an element is inserted
        /// at the front, the iterator is valid but not current. Modification of elements
        /// in place do not make iterators non-current
        isf_current = 0x02,
        /// The iterator is dereferencable, which means it is in the range of [begin, end).
        ///  It may or may not be current
        isf_can_dereference = 0x04
    }iterator_status_flag;

    typedef struct _tagiterator
    {
        void* _pt_container;
        _byte_t* _t_pos;
        iterator_status_flag _t_iteratorstatusflag;
    } iterator_t;

    typedef  struct _tagmeta
    {
        containertype_t _t_containertype;
        iteratortype_t _t_iteratortype;
        type_info_t _t_typeinfo;
    }meta_t;

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
    /// reverse_iterator
    ///
    /// From the C++ standard:
    /// Bidirectional and random access iterators have corresponding reverse
    /// iterator adaptors that iterate through the data structure in the
    /// opposite direction. They have the same signatures as the corresponding
    /// iterators. The fundamental relation between a reverse iterator and its
    /// corresponding iterator i is established by the identity:
    ///     &*(reverse_iterator(i)) == &*(i - 1).
    /// This mapping is dictated by the fact that while there is always a pointer
    /// past the end of an array, there might not be a valid pointer before the
    /// beginning of an array.
    ///
    typedef iterator_t reverse_iterator_t;
    typedef output_iterator_t insert_iterator_t;
    typedef input_iterator_t istream_iterator_t;
    typedef output_iterator_t ostream_iterator_t;

    /**
     * Test whether the iterator is valid.
     * @param it_iter      iterator.
     * @return whether iterator is valid.
     */
    extern bool iterator_is_valid(iterator_t* it_iter);

    /**
    * Get pointer that pointed by iterator, but ignore char*.
    * @param it_iter      iterator.
    * @return pointer
    * @remakes it_iter must be valid and must be not end(), otherwise the behavior is undefined.
    */
extern const void* iterator_get_pointer_ignore_cstr(iterator_t* it_iter);

    /**
     * Get pointer that pointed by iterator, but ignore char*.
     * @param it_iter      iterator.
     * @return pointer
     * @remakes it_iter must be valid and must be not end(), otherwise the behavior is undefined.
     */
    extern bool iterator_same_type(iterator_t* it_first, iterator_t* it_second);

    /**
    * Test whether an iterator on another front.
    * @param it_first     first iterator.
    * @param it_second    second iterator.
    * @return whether the first iterator on the second front.
    * @remarks two iterator must be valid and type muse be same, otherwise behavior is undefined.
    */
    extern bool iterator_before(iterator_t* it_first, iterator_t* it_second);

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
    * Test whether the [it_first, it_end) is valid range.
    * @param it_first     first iterator.
    * @param it_end      last iterator.
    * @return whether the [it_first, it_end) is valid range.
    * @remarks two iterator must be valid iterator and iterator type must be valid type, otherwise behavior is undefined.
    */
    extern bool iterator_valid_range(iterator_t* it_first, iterator_t* it_end, iteratortype_t t_type);

    /**
    * Get typeinfo of iterator.
    * @param it_iter      iterator.
    * @return typeinfo pointer of iterator.
    * @remarks iterator must be valid, otherwise behavior is undefined.
    */
#define iterator_get_typeinfo(it_iter) ((type_info_t*)((it_iter)->_pt_container))

    /**
    * Get type style of iterator.
    * @param it_iter      iterator.
    * @return type style pointer of iterator.
    * @remarks iterator must be valid, otherwise behavior is undefined.
    */
#define iterator_get_typestyle(it_iter) (((type_info_t*)((it_iter)->_pt_container))->_pt_type->_t_style)

    /**
    * Get type size of iterator.
    * @param it_iter      iterator.
    * @return type size of iterator.
    * @remarks iterator must be valid, otherwise behavior is undefined.
    */
#define iterator_get_typesize(it_iter)  (((type_info_t*)((it_iter)->_pt_container))->_pt_type->_t_typesize)

    /**
    * Test whether two iterator point to same type element.
    * @param it_first     first iterator.
    * @param it_second    second iterator.
    * @return whether tow iterator point to same type element.
    * @remarks two iterator must be valid, other behavior is undefined.
    */
    extern bool iterator_same_elem_type(iterator_t* it_first, iterator_t* it_second);

    /**
    * Test two iterator are equal or not.
    * @param it_first     first iterator.
    * @param it_second    second iterator.
    * @return whether equal or not.
    * @remakes two iterator must be valid, otherwise the behavior is undefined.
    */
    extern bool iterator_equal(iterator_t* it_first, iterator_t* it_second);

    /**
    * Get value that pointed by iterator.
    * @param it_iter      iterator.
    * @param pv_value     value.
    * @return void
    * @remakes it_iter must be valid and pv_value != NULL, otherwise the behavior is undefined.
    */
    extern void iterator_get_value(input_iterator_t* it_iter, void* pv_value);

    /**
     * Move iterator to next position.
     * @param it_iter      iterator.
     * @remakes it_iter must be valid and must be not end(), otherwise the behavior is undefined.
     */
    extern void iterator_next(forward_iterator_t* forward_iterator);

    /**
    * Move iterator to previous position.
    * @param it_iter      iterator.
    * @remakes it_iter must be valid and must be not end(), otherwise the behavior is undefined.
    */
    extern void iterator_prev(bidirectional_iterator_t* bidirectional_iterator);

    /**
    * Move iterator to next n position.
    * @param it_iter      iterator.
    * @return next n position.
    * @remakes it_iter must be valid and must be not end(), otherwise the behavior is undefined.
    */
    extern void iterator_next_n(forward_iterator_t* random_access_iterator, size_t n_step);

    /**
    * Move iterator to prev n position.
    * @param it_iter      iterator.
    * @return prev n position.
    * @remakes it_iter must be valid and must be not end(), otherwise the behavior is undefined.
    */
    extern void iterator_prev_n(random_access_iterator_t* it_iter, int n_step);

    /**
    * Test first iterator is less than second iterator.
    * @param it_first     first iterator.
    * @param it_second    second iterator.
    * @return whether first iterator less than second iterator or not.
    * @remakes two iterator must be valid, otherwise the behavior is undefined.
    */
    extern bool iterator_less(random_access_iterator_t* it_first, random_access_iterator_t* it_second);

    /**
    * Test first iterator is less than or equal to second iterator.
    * @param it_first     first iterator.
    * @param it_second    second iterator.
    * @return whether first iterator less than or equal to second iterator or not.
    * @remakes two iterator must be valid, otherwise the behavior is undefined.
    */
    extern bool iterator_less_equal(random_access_iterator_t* it_first, random_access_iterator_t* it_second);

    /**
    * Test first iterator is greater than second iterator.
    * @param it_first     first iterator.
    * @param it_second    second iterator.
    * @return whether first iterator greater than second iterator or not.
    * @remakes two iterator must be valid, otherwise the behavior is undefined.
    */
    extern bool iterator_greater(random_access_iterator_t* it_first, random_access_iterator_t* it_second);

    /**
    * Test first iterator is greater than or equal to second iterator.
    * @param it_first     first iterator.
    * @param it_second    second iterator.
    * @return whether first iterator greater than or equal to second iterator or not.
    * @remakes two iterator must be valid, otherwise the behavior is undefined.
    */
    extern bool iterator_greater_equal(random_access_iterator_t* it_first, random_access_iterator_t* it_second);

    /**
    * Element random access.
    * @param it_iter      iterator.
    * @param n_index      index.
    * @return element pointer.
    * @remarks iterator must be valid, otherwise the behavior is undefined.
    */
    extern void* iterator_at(random_access_iterator_t* it_iter, int n_index);

    /**
    * Iterator distance.
    * @param it_first     first iterator.
    * @param it_second    second iterator.
    * @return iterator distance.
    * @remakes two iterator must be valid, otherwise the behavior is undefined.
    */
    extern int iterator_minus(random_access_iterator_t* it_first, random_access_iterator_t* it_second);

    /**
    * Iterator next n for all iterator type.
    * @param it_iter      iterator.
    * @param n_step       step.
    * @return next n iterator.
    * @remarks iterator must be valid, otherwise the behavior is undefined.
    */
    extern void iterator_advance(forward_iterator_t* it_iter, size_t n_step);
    extern void iterator_disadvance(bidirectional_iterator_t* it_iter, size_t n_step);

    /**
    * Iterator distance for all iterator type.
    * @param it_first     first iterator.
    * @param it_second    second iterator.
    * @return iterator distance.
    * @remakes two iterator must be valid, otherwise the behavior is undefined.
    */
    extern int iterator_distance(iterator_t* it_first, iterator_t* it_second);

#ifdef __cplusplus
}
#endif

#endif /* MYCSTL_CSTL_ITERATOR_H_ */
