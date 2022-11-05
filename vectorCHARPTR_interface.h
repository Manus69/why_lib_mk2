#ifndef VECTOR_CHARPTR_INTERFACE_H
#define VECTOR_CHARPTR_INTERFACE_H

#include "arrayCHARPTR_interface.h"

typedef struct VectorCHARPTR VectorCHARPTR;

VectorCHARPTR* VectorCreateLengthCHARPTR(size_t length);
VectorCHARPTR* VectorCreateCHARPTR();
void VectorDestroyCHARPTR(VectorCHARPTR* vector);
void VectorDestroyAllCHARPTR(VectorCHARPTR* vector);
char* VectorGetCHARPTR(const VectorCHARPTR* vector, size_t index);
void VectorSetCHARPTR(const VectorCHARPTR* vector, size_t index, char* value);
char* VectorBackCHARPTR(const VectorCHARPTR* vector);
size_t VectorRightCapacityCHARPTR(const VectorCHARPTR* vector);
size_t VectorLeftCapacityCHARPTR(const VectorCHARPTR* vector);
int VectorExpandRightCHARPTR(VectorCHARPTR* vector, size_t n_items);
int VectorExpandLeftCHARPTR(VectorCHARPTR* vector, size_t n_items);
int VectorPushBackCHARPTR(VectorCHARPTR* vector, char* value);
void VectorMapCHARPTR(const VectorCHARPTR* vector, void (*f)(char*));
void VectorApplyCHARPTR(VectorCHARPTR* vector, void (*f)(char**));
char* VectorFoldCHARPTR(const VectorCHARPTR* vector, char* (*f)(char*, char*), char* initial_value);

#endif