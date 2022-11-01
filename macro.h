#ifndef MACRO_H
#define MACRO_H

#define OK 1
#define NOT_OK 0

#define CHECK_RETURN(_value, _reference, _return_value) \
    if ((_value) == (_reference)) return (_return_value)

#define GET(_pointer, _type, _index) ((_type *)_pointer)[_index]

#define SET(_pointer, _type, _index, _value) GET(_pointer, _type, _index) = _value

#define SWAP(_pointer, _type, _lhs_index, _rhs_index) \
{ \
    _type*   __pointer = _pointer; \
    _type    __store = GET(__pointer, _type, _lhs_index); \
    \
    SET(__pointer, _type, _lhs_index, GET(__pointer, _type, _rhs_index)); \
    SET(__pointer, _type, _rhs_index, _store); \
}

#endif