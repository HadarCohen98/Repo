/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       1.0                                             *
 ~ Date          04/12/22                                        ~
 ~ Description   Vector Header                                   ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
#ifndef __VECTOR__
#define __VECTOR__

#include <stddef.h>

typedef struct vector vector_t;         

vector_t *VectorCreate(size_t initial_capacity, size_t element_size);

void *VectorGetAccessToElement(vector_t *vector, size_t index);

int VectorAppend(vector_t *vector, const void *value);

void VectorRemoveLast(vector_t *vector);

int VectorIsEmpty(const vector_t *vector);                           

size_t VectorCapacity(const vector_t *vector);

size_t VectorSize(const vector_t *vector);

void VectorDestroy(vector_t *vector);

int VectorReserve(vector_t *vector, size_t size);

int VectorShrink(vector_t *vector);

#endif /* __VECTOR__ */
