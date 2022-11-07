#ifndef PAIR_T_X_INTERFACE_H
#define PAIR_T_X_INTERFACE_H

#include "template_interface.h"

typedef struct Pair_T_X Pair_T_X;

Pair_T_X PairInit_T_X(TYPE lhs, XYPE rhs);
TYPE PairLhs_T_X(Pair_T_X pair);
XYPE PairRhs_T_X(Pair_T_X pair);


#endif