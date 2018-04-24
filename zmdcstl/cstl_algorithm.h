#ifndef ZMDCSTL_CSTL_ALGORITHM_H_
#define ZMDCSTL_CSTL_ALGORITHM_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include "cstl_iterator.h"

#define cstl_min(a,b) (((a)<(b))?(a):(b))
#define cstl_max(a,b) (((a)>(b))?(a):(b))

// if all same f1=l1 else f1 points to unsame element fist2 also points to unsame element
extern bool cstl_equal(input_iterator_t* first1, input_iterator_t* last1, input_iterator_t* first2);
/**
 *
 * Moves the elements from the range [first, last), to another range ending at d_last.
 * The elements are moved in reverse order (the last element is moved first), but their
 * relative order is preserved. The behavior is undefined if the ending position of
 * d_last is within (first, last]. cstl_move must be used instead of cstl_move_backward in that case.
 *
 * @param first-last
 * the range of the elements to move
 *
 * @param d_last
 * end of the destination range
 *
 * @return
 * Iterator in the destination range, pointing at the last element moved.
 *
 * @remark
 * this function assumes that the initial start-moving d_last is
 */
extern void cstl_move_backward(bidirectional_iterator_t* first, bidirectional_iterator_t* last,
    bidirectional_iterator_t* d_last);
/**
 * Moves the elements in the range [first, last), to another range beginning
 * at d_first. After this operation the elements in the moved-from range will
 * still contain valid values of the appropriate type, but not necessarily the
 * same values as before the move.
 *
 * @param first-last
 * the range of elements to move
 *
 * @param d_first
 * the beginning of the destination range. If d_first is within [first, last),
 * cstl_move_backward must be used instead of move.
 *
 * @return
 * Output iterator to the element past the last element moved (d_first + (last - first))
 */
extern void cstl_move(input_iterator_t* first, input_iterator_t* last, output_iterator_t* d_first);

#ifdef __cplusplus
}
#endif
#endif /* ZMDCSTL_CSTL_ALGORITHM_H_ */
