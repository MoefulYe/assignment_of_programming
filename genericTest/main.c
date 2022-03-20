#define GET_TYPENAME(type) _Generic((type),\
    int: "int",\
    char: "char",\
    float: "float",\
    double: "double",\
    long double: "long double",\
    default: "default")
