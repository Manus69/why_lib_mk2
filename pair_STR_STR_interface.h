#ifndef PAIR_STR_STR_INTERFACE_H
#define PAIR_STR_STR_INTERFACE_H

#include "template_interface.h"

typedef struct Pair_STR_STR Pair_STR_STR;

Pair_STR_STR PairInit_STR_STR(char* lhs, char* rhs);
char* PairLhs_STR_STR(Pair_STR_STR pair);
char* PairRhs_STR_STR(Pair_STR_STR pair);


#endif