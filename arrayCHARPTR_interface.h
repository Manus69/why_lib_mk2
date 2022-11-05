#ifndef ARRAY_CHARPTR_INTERFACE_H
#define ARRAY_CHARPTR_INTERFACE_H

typedef struct ArrayCHARPTR ArrayCHARPTR;

ArrayCHARPTR* ArrayCreateCHARPTR(size_t length);
void ArrayDestroyCHARPTR(ArrayCHARPTR* array);
void ArrayDestroyDataCHARPTR(ArrayCHARPTR* array);
void ArrayDestroyAllCHARPTR(ArrayCHARPTR* array);
size_t ArrayLengthCHARPTR(const ArrayCHARPTR* array);
char* ArrayGetCHARPTR(const ArrayCHARPTR* array, size_t index);
void ArraySetCHARPTR(ArrayCHARPTR* array, size_t index, char* value);
int ArrayExpandRightCHARPTR(ArrayCHARPTR* array, size_t extra_items);
int ArrayExpandLeftCHARPTR(ArrayCHARPTR* array, size_t extra_items);

#endif