#ifndef MACRO_H
#define MACRO_H

#define OK 1
#define NOT_OK 0

#define CHECK_RETURN(value, reference, return_value) \
    if (value == reference) return (return_value)

#define GET(pointer, type, index) ((type *)pointer)[index]

#define SET(pointer, type, index, value) GET(pointer, type, index) = value

#define SWAP(pointer, type, lhs_index, rhs_index) \
        { \
            type*   _pointer = pointer; \
            type    store = GET(_pointer, type, lhs_index); \
            \
            SET(_pointer, type, lhs_index, GET(_pointer, type, rhs_index)); \
            SET(_pointer, type, rhs_index, store); \
        }

#endif