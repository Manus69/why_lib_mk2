#include "pair_T_X.h"
#include "pair_T_X_interface.h"

Pair_T_X PairInit_T_X(TYPE lhs, XYPE rhs)
{
    Pair_T_X pair;

    pair.lhs = lhs;
    pair.rhs = rhs;

    return pair;
}

TYPE PairLhs_T_X(Pair_T_X pair)
{
    return pair.lhs;
}

XYPE PairRhs_T_X(Pair_T_X pair)
{
    return pair.rhs;
}