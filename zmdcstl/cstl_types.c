#include "cstl_types.h"
#include "cstl_alloc.h"
#include "cstl_types_builtin.h"

/** local constant declaration and local macro section **/
type_register_t _g_type_register = { 0 };

inline static const char* gettypename(typeid_t tid)
{
    switch (tid)
    {
    case cstl_int8:
        return "cstl_int8";
        break;
    case cstl_uint8:
        return "cstl_uint8";
        break;
    case cstl_int16:
        return "cstl_int16";
        break;
    case cstl_uint16:
        return "cstl_int16";
        break;
    case cstl_int32:
        return "cstl_int16";
        break;
    case cstl_uint32:
        return "cstl_int16";
        break;
    case cstl_int64:
        return "cstl_int16";
        break;
    case cstl_uint64:
        return "cstl_int16";
        break;
    case cstl_float:
        return "cstl_float";
        break;
    case cstl_double:
        return "cstl_double";
        break;

        //@TODO register cstl types
    case cstl_vector:
        return "cstl_double";
        break;
    default:
        return "error: type id does not exit";
        break;
    }
    return "error: type id does not exit";
}

const char* print_type_name(typeid_t typeid)
{
    const char* str = gettypename(typeid);
    assert(str != NULL);
    return str;
}

void print_type_names(typeid_t typeids[], size_t size)
{
    char buff[256];
    char* buf = buff;
    int n;
    int maxbsize = 256;
    for (int i = 0; i < size; i++)
    {
        n = snprintf(buf, maxbsize, "%s, ", gettypename(i));
        buf += n;
        maxbsize -= n;
    }
    puts(buff);
}

typeid_t register_type(size_t typesize, size_t typealign, ufun_t type_init,
    bfun_t type_copy, ufun_t type_destroy, bfun_t type_less)
{
    type_t* pt_type = cstl_alloc(type_t, 1);
    pt_type->_t_typeid = _g_type_register._registered_size;
    pt_type->_t_typesize = typesize;
    pt_type->_t_typealign = typealign;
    pt_type->_t_typeinit = type_init;
    pt_type->_t_typecopy = type_copy;
    pt_type->_t_typeless = type_less;
    pt_type->_t_typedestroy = type_destroy;
    _g_type_register._ptr_types[_g_type_register._registered_size] = pt_type;
    _g_type_register._registered_size++;
    return (typeid_t)(_g_type_register._registered_size - 1);
}

void destroy_types()
{
    if (_g_type_register._ptr_types)
    {
        for (int i = 0; i < _g_type_register._total_size; i++)
        {
            if (_g_type_register._ptr_types[i])
                cstl_free(_g_type_register._ptr_types[i]);
        }
        cstl_free(_g_type_register._ptr_types);
        _g_type_register._ptr_types = 0;
    }
}
void init_types(size_t usertypesize)
{
    if (_g_type_register._ptr_types)
        return;

    if (usertypesize == 0)
        usertypesize = TYPE_REGISTER_BUCKET_COUNT;

    _g_type_register._total_size = usertypesize + (size_t)default_types_size;
    _g_type_register._ptr_types = cstl_alloc(type_t*,
        _g_type_register._total_size);
    register_type(sizeof(char), CSTL_ALIGN_OF(char), NULL, NULL, NULL,
        _type_less_char);
    register_type(sizeof(unsigned char), CSTL_ALIGN_OF(unsigned char), NULL, NULL,
        NULL, _type_less_uchar);
    register_type(sizeof(short), CSTL_ALIGN_OF(short), NULL, NULL, NULL,
        _type_less_short);
    register_type(sizeof(unsigned short), CSTL_ALIGN_OF(unsigned short), NULL,
        NULL, NULL, _type_less_ushort);
    register_type(sizeof(int), CSTL_ALIGN_OF(int), NULL, NULL, NULL,
        _type_less_int);
    register_type(sizeof(unsigned int), CSTL_ALIGN_OF(unsigned int), NULL, NULL,
        NULL, _type_less_uint);
    register_type(sizeof(int64_t), CSTL_ALIGN_OF(int64_t), NULL, NULL, NULL,
        _type_less_long_long);
    register_type(sizeof(uint64_t), CSTL_ALIGN_OF(uint64_t), NULL, NULL, NULL,
        _type_less_ulong_long);
    register_type(sizeof(float), CSTL_ALIGN_OF(float), NULL, NULL, NULL,
        _type_less_float);
    register_type(sizeof(double), CSTL_ALIGN_OF(double), NULL, NULL, NULL,
        _type_less_double);
    register_type(sizeof(void*), CSTL_ALIGN_OF(void*), NULL, NULL, NULL,
        _type_less_pointer);

    //@TODO register cstl types

    for (int i = _g_type_register._registered_size;
        i < _g_type_register._total_size; i++)
        _g_type_register._ptr_types[i] = NULL;
}

void print_registered_types()
{
    init_types(0);
    for (int i = 0; i < _g_type_register._registered_size; i++)
    {
        if (_g_type_register._ptr_types[i])
        {
            printf("type name: %s, type style:%s, type size: %d\n",
                gettypename(_g_type_register._ptr_types[i]->_t_typeid),
                _g_type_register._ptr_types[i]->_t_typecopy ? "pod" : "non-pod",
                _g_type_register._ptr_types[i]->_t_typesize);
        }
    }
}

bool type_info_is_same(const type_info_t* pt_first, const type_info_t* pt_second)
{
    if (pt_first->_t_typeidsize != pt_second->_t_typeidsize)
        return false;
    unsigned char* firstp = TYPE_INFO_TYPE_PTR_IDS(pt_first);
    unsigned char* secondp = TYPE_INFO_TYPE_PTR_IDS(pt_second);
    for (int i = 0; i < pt_first->_t_typeidsize; i++)
    {
        if (firstp[i] != secondp[i])
            return false;
    }
    return true;
}
