#include "cstl_types.h"
#include "cstl_types_builtin.h"

static const char* g_buildin_type_str[TYPE_REGISTER_BUCKET_COUNT] = { "int8t", "uint8t", "int16t", "uint16t", "int32t",
        "uint32t", "int64t", "uint64t", "floatt", "doublet", "voidpointert", "vector_tt", "list_tt", "map_tt",
        "hash_tt",
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL,
        NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL,
        NULL, NULL, NULL, NULL,
        NULL, NULL, NULL };

static const char* g_type_style_str[] = { "_TYPE_STYLE_POD", "_TYPE_STYLE_CSTL", "_TYPE_STYLE_USER_DEFINED",
        "_TYPE_STYLE_USER_DEFINED", "_TYPE_STYLE_INVALID", };

#ifndef CSTL_ALIGN_OF
#if   defined(_MSC_VER) && (_MSC_VER < 1700)
// Workaround for this VS 2010 compiler bug: https://connect.microsoft.com/VisualStudio/feedback/details/682695
#define CSTL_ALIGN_OF(...) ( (sizeof(__VA_ARGS__)*0) + (__alignof(__VA_ARGS__)) )
#elif !defined(__GNUC__) || (__GNUC__ >= 3) // GCC 2.x doesn't do __alignof correctly all the time.
#define CSTL_ALIGN_OF __alignof
#else
#define CSTL_ALIGN_OF(type) ((size_t)offsetof(struct{ char c; type m; }, m))
#endif
#endif

/* the pt_type, pt_node and t_pos must be defined before use those macro */
#define register_type_start() type_t* pt_type
#define register_type(realtype, type, tstyle)\
    pt_type = (type_t*)malloc(sizeof(type_t));\
    pt_type->_t_typeid = _registered_type_count;\
    pt_type->_t_typesize = sizeof(realtype);\
    pt_type->_t_typealign = CSTL_ALIGN_OF(realtype);\
    pt_type->_t_style = tstyle;\
    pt_type->_t_typeinit = _type_init_##type;\
    pt_type->_t_typecopy = _type_copy_##type;\
    pt_type->_t_typeless = _type_less_##type;\
    pt_type->_t_typedestroy = _type_destroy_##type;\
    _apt_bucket[_registered_type_count] = pt_type;\
    _registered_type_count++

/** local constant declaration and local macro section **/
static bool _t_isinit = false; /* is initializate for c and cstl built in types */
static unsigned char _registered_type_count = 0;
type_t* _apt_bucket[TYPE_REGISTER_BUCKET_COUNT] = { 0 };

const char* print_type_name(typeid_t typeid)
{
    const char* str = g_buildin_type_str[typeid];
    assert(str != NULL);
    return str;
}
const char* print_type_names(typeid_t typeids[], size_t size)
{
    static char buff[256];
    char* buf = buff;
    int n;
    int maxbsize = 256;
    for (int i = 0; i < size; i++)
    {
        assert(g_buildin_type_str[i] != NULL);
        n = snprintf(buf, maxbsize, "%s, ", g_buildin_type_str[i]);
        buf += n;
        maxbsize -= n;
    }
    return (const char*) buff;
}

void init_types(void)
{
    if (_t_isinit)
        return;

    register_type_start();
    register_type(char, char, _TYPE_STYLE_POD);
    register_type(char, uchar, _TYPE_STYLE_POD);
    register_type(short, short, _TYPE_STYLE_POD);
    register_type(unsigned short, ushort, _TYPE_STYLE_POD);
    register_type(int, int, _TYPE_STYLE_POD);
    register_type(unsigned int, uint, _TYPE_STYLE_POD);
    register_type(int64_t, long_long, _TYPE_STYLE_POD);
    register_type(uint64_t, ulong_long, _TYPE_STYLE_POD);
    register_type(float, float, _TYPE_STYLE_POD);
    register_type(double, double, _TYPE_STYLE_POD);
    register_type(void*, pointer, _TYPE_STYLE_POD);

    //@TODO register cstl types

    for (int i = _registered_type_count; i < TYPE_REGISTER_BUCKET_COUNT; i++)
    {
        _apt_bucket[i] = NULL;
    }
    _t_isinit = true;
}

void show_registered_types()
{
    init_types();
    printf("total type number: %d\n", _registered_type_count);
    for (int i = 0; i < _registered_type_count; i++)
    {
        if (_apt_bucket[i])
        {
            printf("type name: %s, type style:%s, type size: %d\n", g_buildin_type_str[_apt_bucket[i]->_t_typeid],
                    g_type_style_str[_apt_bucket[i]->_t_style], _apt_bucket[i]->_t_typesize);
        }
    }
}

bool type_info_is_same(const type_info_t* pt_first, const type_info_t* pt_second)
{
    assert(pt_first != NULL);
    assert(pt_second != NULL);
    if (pt_first == pt_second)
        return true;
    if (pt_first->_t_typeidsize != pt_second->_t_typeidsize)
        return false;
    for (int i = 0; i < pt_first->_t_typeidsize; i++)
    {
        if (pt_first->_t_typeids[i] != pt_second->_t_typeids[i])
            return false;
    }
    return pt_first->_pt_type == pt_second->_pt_type;
}
