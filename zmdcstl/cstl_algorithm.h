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
extern bool equal(input_iterator_t* first1, input_iterator_t* last1, input_iterator_t* first2);
extern bool equal_from_continus(_byte_t* first1, _byte_t* last1, input_iterator_t* first2);

#ifdef __cplusplus
}
#endif
#endif /* ZMDCSTL_CSTL_ALGORITHM_H_ */
