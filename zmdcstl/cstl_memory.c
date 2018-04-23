/*
 * cstl_memory.c
 *
 *  Created on: 6 Mar. 2018
 *      Author: jackiez
 */

#include "cstl_memory.h"
#include "cstl_types.h"
#include "cstl_iterator.h"

#include "cstl_vector.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4146)  // unary minus operator applied to unsigned type, result still unsigned
#endif

 //TODO call container-specific impl

void* align(size_t alignment, size_t size, void** ptr, size_t* space)
{
	if (*space >= size)
	{
		char* ptrAligned = (char*)(((size_t)(*ptr) + (alignment - 1)) & -alignment);
		size_t offset = (size_t)(ptrAligned - (char*)(*ptr));
		if ((*space - size) >= offset) // Have to implement this in terms of subtraction instead of addition in order to handle possible overflow.
		{
			*ptr = ptrAligned;
			*space -= offset;
			return ptrAligned;
		}
	}
	return NULL;
}

void* align_advance(size_t alignment, size_t size, void* ptr, size_t space, void** ptrAdvanced /*=null*/,
	size_t* spaceReduced /*=null*/)
{
	if (space >= size)
	{
		char* ptrAligned = (char*)(((size_t)ptr + (alignment - 1)) & -alignment);
		size_t offset = (size_t)(ptrAligned - (char*)ptr);
		if ((space - size) >= offset) // Have to implement this in terms of subtraction instead of addition in order to handle possible overflow.
		{
			if (ptrAdvanced)
				*ptrAdvanced = (ptrAligned + size);
			if (spaceReduced)
				*spaceReduced = (space - (offset + size));
			return ptrAligned;
		}
	}
	return NULL;
}

void destruct(forward_iterator_t* first, forward_iterator_t* last)
{
	assert(iterator_is_valid(first) && iterator_is_valid(last));
	ufun_t dtor = _ITERATOR_TYPE_INFO_TYPE(first)->_t_typedestroy;
	if (dtor)
	{
		iterator_pre_t next = _ITERATOR_META_TYPE(first)->iterator_next;
		iterator_dref_t dref = _ITERATOR_META_TYPE(first)->iterator_dref;
		iterator_equal_t equal = _ITERATOR_META_TYPE(first)->iterator_equal;
		bool ret;
		for (; !equal(first, last); next(first))
		{
			dtor(dref(first), &ret);
		}
	}
}
void destruct_n(forward_iterator_t* first, int n)
{
	assert(iterator_is_valid(first));
	ufun_t dtor = _ITERATOR_TYPE_INFO_TYPE(first)->_t_typedestroy;
	if (dtor)
	{
		iterator_pre_t next = _ITERATOR_META_TYPE(first)->iterator_next;
		iterator_dref_t dref = _ITERATOR_META_TYPE(first)->iterator_dref;
		bool ret = false;
		for (; n > 0; n--, next(first))
			dtor(dref(first), &ret);
	}
}
void destruct_at(input_iterator_t* destination)
{
	assert(iterator_is_valid(destination));
	type_t* type = _ITERATOR_TYPE_INFO_TYPE(destination);
	if (type->_t_typedestroy)
	{
		bool ret;
		type->_t_typedestroy(destination->_t_pos, &ret);
	}
}
void destruct_at_vec(type_t* type, _byte_t* destination)
{
	if (type->_t_typedestroy)
	{
		bool ret;
		type->_t_typedestroy(destination, &ret);
	}
}

void uninitialized_default_fill_n(forward_iterator_t* destination, size_t n)
{
	assert(iterator_is_valid(destination));
	bool ret = false;
	type_t* type = _ITERATOR_TYPE_INFO_TYPE(destination);
	ufun_t dctor = type->_t_typeinit;
	if (dctor)
	{
		for (; n > 0; n--)
		{
			dctor(destination->_t_pos, &ret);
			iterator_next(destination);
		}
	}
	else
	{
		for (; n > 0; n--, iterator_next(destination))
			memset(destination->_t_pos, 0, type->_t_typesize);
	}
}
void uninitialized_fill_n(forward_iterator_t* destination, const void* value, int n)
{
	assert(iterator_is_valid(destination));
	type_t* type = _ITERATOR_TYPE_INFO_TYPE(destination);
	for (; n > 0; n--)
	{
		if (type->_t_typecopy)
		{
			bool ret = false;
			type->_t_typecopy(destination->_t_pos, value, &ret);
			assert(ret);
		}
		else
		{
			cstl_memcpy(destination->_t_pos, value, type->_t_typesize);
		}
		iterator_next(destination);
	}
}

void uninitialized_default_fill(forward_iterator_t* first, forward_iterator_t* last)
{
	assert(iterator_is_valid(first) && iterator_is_valid(last));
	bool ret = false;
	type_t* type = _ITERATOR_TYPE_INFO_TYPE(first);
	for (; !iterator_equal(first, last); iterator_next(first))
	{
		if (type->_t_typeinit)
			type->_t_typeinit(first->_t_pos, &ret);
		else
			memset(first->_t_pos, 0, type->_t_typesize);
	}
}
void uninitialized_fill(forward_iterator_t* first, forward_iterator_t* last, const void* value)
{
	assert(iterator_is_valid(first) && iterator_is_valid(last));
	type_t* type = _ITERATOR_TYPE_INFO_TYPE(first);
	if (type->_t_typecopy)
	{
		bool ret = false;
		for (; !iterator_equal(first, last); iterator_next(first))
			type->_t_typecopy(first->_t_pos, value, &ret);
	}
	else
	{
		for (; !iterator_equal(first, last); iterator_next(first))
			cstl_memcpy(first->_t_pos, value, type->_t_typesize);
	}
}

void uninitialized_copy(input_iterator_t* first, input_iterator_t* last, forward_iterator_t* result)
{
	assert(iterator_is_valid(first) && iterator_is_valid(last) && iterator_is_valid(result));
	assert(iterator_same_elem_type(first, last) && iterator_same_elem_type(first, result));

	type_t* type = _ITERATOR_TYPE_INFO_TYPE(first);
	bfun_t cpy = type->_t_typecopy;

	iterator_pre_t next = _ITERATOR_META_TYPE(first)->iterator_next;
	iterator_dref_t dref = _ITERATOR_META_TYPE(first)->iterator_dref;
	iterator_equal_t equal = _ITERATOR_META_TYPE(first)->iterator_equal;

	iterator_pre_t result_next = _ITERATOR_META_TYPE(result)->iterator_next;
	iterator_dref_t result_dref = _ITERATOR_META_TYPE(result)->iterator_dref;

	if (!cpy)
	{
		size_t size = type->_t_typesize;
		if (_ITERATOR_TYPE(first) == _RANDOM_ACCESS_ITERATOR &&
			_ITERATOR_TYPE(result) == _RANDOM_ACCESS_ITERATOR)
		{
			size = last->_t_pos - first->_t_pos;
			cstl_memcpy(result_dref(result), dref(first), size);
			result->_t_pos += size;
		}
		else
		{
			while (!equal(first, last))
			{
				cstl_memcpy(result_dref(result), dref(first), size);
				next(first);
				result_next(result);
			}
		}
	}
	else
	{
		bool is_assign = false;
		while (!equal(first, last))
		{
			cpy(result_dref(result), dref(first), &is_assign);
			next(first);
			result_next(result);
		}
	}
}
void uninitialized_copy_n(input_iterator_t* first, size_t n, forward_iterator_t* result)
{
	assert(iterator_is_valid(first) && iterator_is_valid(result));

	type_t* type = _ITERATOR_TYPE_INFO_TYPE(first);
	bfun_t cpy = type->_t_typecopy;

	iterator_pre_t next = _ITERATOR_META_TYPE(first)->iterator_next;
	iterator_dref_t dref = _ITERATOR_META_TYPE(first)->iterator_dref;

	iterator_pre_t result_next = _ITERATOR_META_TYPE(result)->iterator_next;
	iterator_dref_t result_dref = _ITERATOR_META_TYPE(result)->iterator_dref;

	if (!cpy)
	{
		size_t tsize = type->_t_typesize;
		if (_ITERATOR_TYPE(first) == _RANDOM_ACCESS_ITERATOR &&
			_ITERATOR_TYPE(result) == _RANDOM_ACCESS_ITERATOR)
		{
			n *= tsize;
			cstl_memcpy(result_dref(result), dref(first), n);
			result->_t_pos += n;
		}
		else
		{
			for (; n > 0; n--)
			{
				cstl_memcpy(result_dref(result), dref(first), tsize);
				next(first);
				result_next(result);
			}
		}
	}
	else
	{
		bool is_assign = false;
		for (; n > 0; n--)
		{
			cpy(result_dref(result), dref(first), &is_assign);
			next(first);
			result_next(result);
		}
	}
}

void fill_n(output_iterator_t* from, size_t n, void* val)
{
	assert(iterator_is_valid(from));

	type_t* type = _ITERATOR_TYPE_INFO_TYPE(from);
	bfun_t cpyctor = type->_t_typecopy;

	if (_ITERATOR_TYPE(from) == _RANDOM_ACCESS_ITERATOR)
	{
		_byte_t*  destPosition = from->_t_pos;
		_byte_t* e = destPosition + type->_t_typesize * n;
		from->_t_pos = e;
		switch (type->_t_typeid)
		{
		case cstl_int8:
			fill_n_char((char*)destPosition, n, *(char*)val);
			break;
		case cstl_uint8:
			fill_n_uchar((unsigned char*)destPosition, n, *(unsigned char*)val);
			break;
		case cstl_int16:
			fill_n_int16((int16_t*)destPosition, n, *(int16_t*)val);
			break;
		case cstl_uint16:
			fill_n_uint16((uint16_t*)destPosition, n, *(uint16_t*)val);
			break;
		case cstl_int32:
			fill_n_int32((int32_t*)destPosition, n, *(int32_t*)val);
			break;
		case cstl_uint32:
			fill_n_uint32((uint32_t*)destPosition, n, *(uint32_t*)val);
			break;
		case cstl_int64:
			fill_n_int64((int64_t*)destPosition, n, *(int64_t*)val);
			break;
		case cstl_uint64:
			fill_n_uint64((uint64_t*)destPosition, n, *(uint64_t*)val);
			break;
		case cstl_void_pt:
			fill_n_uint64((uint64_t*)destPosition, n, *(uint64_t*)val);
			break;
		default:
		{
			size_t tsize = type->_t_typesize;
			if (cpyctor)
			{ // heap-allocation inside this struct
				bool is_copy_assign = true;
				for (; destPosition != e; destPosition += tsize)
					cpyctor(destPosition, val, &is_copy_assign);
			}
			else
			{ // pod struct
				for (; destPosition != e; destPosition += tsize)
					cstl_memcpy(destPosition, val, tsize);
			}
		}
		break;
		}
	}
	else
	{
		iterator_pre_t next = _ITERATOR_META_TYPE(from)->iterator_next;
		iterator_dref_t dref = _ITERATOR_META_TYPE(from)->iterator_dref;
		if (cpyctor)
		{
			bool is_copy_assign = true;
			for (; n > 0; n--)
			{
				cpyctor(dref(from), val, &is_copy_assign);
				next(from);
			}
		}
		else
		{
			size_t tsize = type->_t_typesize;
			for (; n > 0; n--)
			{
				cstl_memcpy(dref(from), val, tsize);
				next(from);
			}
		}
	}
}

char* fill_n_char(char* first, size_t n, char c)
{
	return (char*)memset(first, (char)c, n) + n;
}

unsigned char* fill_n_uchar(unsigned char* first, size_t n, unsigned char c)
{
	return (unsigned char*)memset(first, (unsigned char)c, n) + n;
}

#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__ICL) // ICL = Intel compiler
bool* fill_n_bool(bool* first, size_t n, bool b)
{
	return (bool*)memset(first, (char)b, n) + n;
}
#endif

#if(defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG)) && (defined(EA_PROCESSOR_X86) || defined(EA_PROCESSOR_X86_64))
#if defined(EA_PROCESSOR_X86_64)
uint64_t* fill_n_uint64(uint64_t* first, size_t n, uint64_t c)
{
	uintptr_t count = (uintptr_t)(n);
	uint64_t value = (uint64_t)(c);
	__asm__ __volatile__("cld\n\t"
		"rep stosq\n\t"
		: "+c" (count), "+D" (first), "=m" (first)
		: "a" (value)
		: "cc");
	return first; // first is updated by the code above.
}
int64_t* fill_n_int64(int64_t* first, size_t n, int64_t c)
{
	uintptr_t count = (uintptr_t)(n);
	int64_t value = (int64_t)(c);
	__asm__ __volatile__("cld\n\t"
		"rep stosq\n\t"
		: "+c" (count), "+D" (first), "=m" (first)
		: "a" (value)
		: "cc");
	return first; // first is updated by the code above.
}
#endif  // #if defined(EA_PROCESSOR_X86_64)
uint32_t* fill_n_uint32(uint32_t* first, size_t n, uint32_t c)
{
	uintptr_t count = (uintptr_t)(n);
	uint32_t value = (uint32_t)(c);
	__asm__ __volatile__("cld\n\t"
		"rep stosl\n\t"
		: "+c" (count), "+D" (first), "=m" (first)
		: "a" (value)
		: "cc");
	return first; // first is updated by the code above.
}
int32_t* fill_n_int32(int32_t* first, size_t n, int32_t c)
{
	uintptr_t count = (uintptr_t)(n);
	int32_t value = (int32_t)(c);
	__asm__ __volatile__("cld\n\t"
		"rep stosl\n\t"
		: "+c" (count), "+D" (first), "=m" (first)
		: "a" (value)
		: "cc");
	return first; // first is updated by the code above.
}
uint16_t* fill_n_uint16(uint16_t* first, size_t n, uint16_t c)
{
	uintptr_t count = (uintptr_t)(n);
	uint16_t value = (uint16_t)(c);
	__asm__ __volatile__("cld\n\t"
		"rep stosw\n\t"
		: "+c" (count), "+D" (first), "=m" (first)
		: "a" (value)
		: "cc");
	return first; // first is updated by the code above.
}
int16_t* fill_n_int16(int16_t* first, size_t n, int16_t c)
{
	uintptr_t count = (uintptr_t)(n);
	int16_t value = (int16_t)(c);
	__asm__ __volatile__("cld\n\t"
		"rep stosw\n\t"
		: "+c" (count), "+D" (first), "=m" (first)
		: "a" (value)
		: "cc");
	return first; // first is updated by the code above.
}
#elif defined(EA_COMPILER_MICROSOFT) && (defined(EA_PROCESSOR_X86) || defined(EA_PROCESSOR_X86_64))
#if defined(EA_PROCESSOR_X86_64)
uint64_t* fill_n_uint64(uint64_t* first, size_t n, uint64_t c)
{
	__stosq(first, (uint64_t)c, n);
	return first + n;
}
int64_t* fill_n_int64(int64_t* first, size_t n, int64_t c)
{
	__stosq((uint64_t*)first, (uint64_t)c, n);
	return first + n;
}
#endif
uint32_t* fill_n_uint32(uint32_t* first, size_t n, uint32_t c)
{
	__stosd((unsigned long*)first, (unsigned long)c, (size_t)n);
	return first + n;
}
int32_t* fill_n_int32(int32_t* first, size_t n, int32_t c)
{
	__stosd((unsigned long*)first, (unsigned long)c, (size_t)n);
	return first + n;
}
uint16_t* fill_n_uint16(uint16_t* first, size_t n, uint16_t c)
{
	__stosw(first, (uint16_t)c, (size_t)n);
	return first + n;
}
int16_t* fill_n_int16(int16_t* first, size_t n, int16_t c)
{
	__stosw((uint16_t*)first, (uint16_t)c, (size_t)n);
	return first + n;
}
#endif

void fill(forward_iterator_t * it_first, forward_iterator_t * it_end, void * val)
{
	assert(iterator_is_valid(it_first) && iterator_is_valid(it_end));

	type_t* type = _ITERATOR_TYPE_INFO_TYPE(it_first);
	bfun_t cpyctor = type->_t_typecopy;
  _byte_t* e = it_end->_t_pos;
  _byte_t* first = it_first->_t_pos;

	if (_ITERATOR_TYPE(it_first) == _RANDOM_ACCESS_ITERATOR)
	{
		switch (type->_t_typeid) {
		case cstl_int8:
			fill_char((char*)first, (char*)e, *(char*)val);
			break;
		case cstl_uint8:
			fill_uchar((unsigned char*)first, e, *(unsigned char*)val);
			break;
		case cstl_int16:
			fill_int16((int16_t*)first, (int16_t*)e, *(int16_t*)val);
			break;
		case cstl_uint16:
			fill_uint16((uint16_t*)first, (uint16_t*)e, *(uint16_t*)val);
			break;
		case cstl_int32:
			fill_int32((int32_t*)first, (int32_t*)e, *(int32_t*)val);
			break;
		case cstl_uint32:
			fill_uint32((uint32_t*)first, (uint32_t*)e, *(uint32_t*)val);
			break;
		case cstl_int64:
			fill_int64((int64_t*)first, (int64_t*)e, *(int64_t*)val);
			break;
		case cstl_uint64:
			fill_uint64((uint64_t*)first, (uint64_t*)e, *(uint64_t*)val);
			break;
		case cstl_void_pt:
			fill_uint64((uint64_t*)first, (uint64_t*)e, *(uint64_t*)val);
			break;
		default:
			if (cpyctor)
			{ // heap-allocation inside this struct
				bool is_copy_assign = true;
				size_t tsize = type->_t_typesize;
				for (; first != e; first += tsize)
					cpyctor(first, val, &is_copy_assign);
			}
			else
			{ // pod struct
				size_t tsize = type->_t_typesize;
				for (; first != e; first += tsize)
					cstl_memcpy(first, val, tsize);
			}
			break;
		}
	}
	else
	{
		iterator_pre_t next = _ITERATOR_META_TYPE(it_first)->iterator_next;
		iterator_dref_t dref = _ITERATOR_META_TYPE(it_first)->iterator_dref;
		iterator_equal_t equal = _ITERATOR_META_TYPE(it_first)->iterator_equal;
		if (cpyctor)
		{
			bool assign = true;
			while (!equal(it_first, it_end))
			{
				cpyctor(dref(it_first), val, &assign);
				next(it_first);
			}
		}
		else
		{
			size_t tsize = type->_t_typesize;
			while (!equal(it_first, it_end))
			{
				cstl_memcpy(dref(it_first), val, tsize);
				next(it_first);
		}
	}
}
	}

void fill_char(char* first, char* last, char c) // It's debateable whether we should use 'char& c' or 'char c' here.
{
	memset(first, (unsigned char)c, last - first);
}
void fill_uchar(unsigned char* first, unsigned char* last, unsigned char c)
{
	memset(first, (unsigned char)c, last - first);
}
#if(defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG)) && (defined(EA_PROCESSOR_X86) || defined(EA_PROCESSOR_X86_64))
#if defined(EA_PROCESSOR_X86_64)
void fill_uint64(uint64_t* first, uint64_t* last, uint64_t c)
{
	uintptr_t count = (uintptr_t)(last - first);
	uint64_t value = (uint64_t)(c);
	__asm__ __volatile__("cld\n\t"
		"rep stosq\n\t"
		: "+c" (count), "+D" (first), "=m" (first)
		: "a" (value)
		: "cc");
}
void fill_int64(int64_t* first, int64_t* last, int64_t c)
{
	uintptr_t count = (uintptr_t)(last - first);
	int64_t value = (int64_t)(c);
	__asm__ __volatile__("cld\n\t"
		"rep stosq\n\t"
		: "+c" (count), "+D" (first), "=m" (first)
		: "a" (value)
		: "cc");
}
#endif
void fill_uint32(uint32_t* first, uint32_t* last, uint32_t c)
{
	uintptr_t count = (uintptr_t)(last - first);
	uint32_t value = (uint32_t)(c);
	__asm__ __volatile__("cld\n\t"
		"rep stosl\n\t"
		: "+c" (count), "+D" (first), "=m" (first)
		: "a" (value)
		: "cc");
}
void fill_int32(int32_t* first, int32_t* last, int32_t c)
{
	uintptr_t count = (uintptr_t)(last - first);
	int32_t value = (int32_t)(c);
	__asm__ __volatile__("cld\n\t"
		"rep stosl\n\t"
		: "+c" (count), "+D" (first), "=m" (first)
		: "a" (value)
		: "cc");
}
void fill_uint16(uint16_t* first, uint16_t* last, uint16_t c)
{
	uintptr_t count = (uintptr_t)(last - first);
	uint16_t value = (uint16_t)(c);
	__asm__ __volatile__("cld\n\t"
		"rep stosw\n\t"
		: "+c" (count), "+D" (first), "=m" (first)
		: "a" (value)
		: "cc");
}
void fill_int16(int16_t* first, int16_t* last, int16_t c)
{
	uintptr_t count = (uintptr_t)(last - first);
	int16_t value = (int16_t)(c);
	__asm__ __volatile__("cld\n\t"
		"rep stosw\n\t"
		: "+c" (count), "+D" (first), "=m" (first)
		: "a" (value)
		: "cc");
}
#elif defined(EA_COMPILER_MICROSOFT) && (defined(EA_PROCESSOR_X86) || defined(EA_PROCESSOR_X86_64))
#if defined(EA_PROCESSOR_X86_64)
void fill_uint64(uint64_t* first, uint64_t* last, uint64_t c)
{
	__stosq(first, (uint64_t)c, (size_t)(last - first));
}
void fill_int64(int64_t* first, int64_t* last, int64_t c)
{
	__stosq((uint64_t*)first, (uint64_t)c, (size_t)(last - first));
}
#endif
void fill_uint32(uint32_t* first, uint32_t* last, uint32_t c)
{
	__stosd((unsigned long*)first, (unsigned long)c, (size_t)(last - first));
}
void fill_int32(int32_t* first, int32_t* last, int32_t c)
{
	__stosd((unsigned long*)first, (unsigned long)c, (size_t)(last - first));
}
void fill_uint16(uint16_t* first, uint16_t* last, uint16_t c)
{
	__stosw(first, (uint16_t)c, (size_t)(last - first));
}
void fill_int16(int16_t* first, int16_t* last, int16_t c)
{
	__stosw((uint16_t*)first, (uint16_t)c, (size_t)(last - first));
}
#endif

#ifdef _MSC_VER
#pragma warning(pop)
#endif
