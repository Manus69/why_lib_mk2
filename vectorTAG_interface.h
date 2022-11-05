#ifndef VECTOR_TAG_INTERFACE_H
#define VECTOR_TAG_INTERFACE_H

#include "arrayTAG_interface.h"

typedef struct VectorTAG VectorTAG;

VectorTAG* VectorCreateLengthTAG(size_t length);
VectorTAG* VectorCreateTAG();
void VectorDestroyTAG(VectorTAG* vector);
void VectorDestroyAllTAG(VectorTAG* vector, void (*f)(TYPE));
void VectorDestroyElementsTAG(VectorTAG* vector, void (*f)(TYPE));
TYPE VectorGetTAG(const VectorTAG* vector, size_t index);
void VectorSetTAG(const VectorTAG* vector, size_t index, TYPE value);
TYPE VectorBackTAG(const VectorTAG* vector);
size_t VectorRightCapacityTAG(const VectorTAG* vector);
size_t VectorLeftCapacityTAG(const VectorTAG* vector);
int VectorExpandRightTAG(VectorTAG* vector, size_t n_items);
int VectorExpandLeftTAG(VectorTAG* vector, size_t n_items);
int VectorPushBackTAG(VectorTAG* vector, TYPE value);
void VectorMapTAG(const VectorTAG* vector, void (*f)(TYPE));
void VectorApplyTAG(VectorTAG* vector, void (*f)(TYPE*));
TYPE VectorFoldTAG(const VectorTAG* vector, TYPE (*f)(TYPE, TYPE), TYPE initial_value);

#endif