#ifndef VECTOR_TAG_INTERFACE_H
#define VECTOR_TAG_INTERFACE_H

#include "arrayTAG_interface.h"

typedef struct VectorTAG VectorTAG;

VectorTAG* VectorCreateLengthTAG(size_t length);
VectorTAG* VectorCreateTAG();
void VectorDestroyTAG(VectorTAG* vector);
void VectorDestroyAllTAG(VectorTAG* vector);
TYPE VectorGetTAG(const VectorTAG* vector, size_t index);
void VectorSetTAG(const VectorTAG* vector, size_t index, TYPE value);
TYPE VectorBackTAG(const VectorTAG* vector);
size_t VectorRightCapacityTAG(const VectorTAG* vector);
size_t VectorLeftCapacityTAG(const VectorTAG* vector);
int VectorExpandRightTAG(VectorTAG* vector, size_t n_items);
int VectorExpandLeftTAG(VectorTAG* vector, size_t n_items);
int VectorPushBackTAG(VectorTAG* vector, TYPE value);
void VectorApplyTAG(const VectorTAG* vector, void (*f)(TYPE));


#endif