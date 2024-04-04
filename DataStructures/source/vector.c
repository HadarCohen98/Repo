
 /* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       0.0.2                                            *
 ~ Date          06.09.22                                         ~
 ~ Description   dynamic vector data structure implementaotion    ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include <stdlib.h> /* malloc, calloc, free */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "include/vector.h"

#define GROWTH_FACTOR 2

struct vector
{
	void *elements;
	size_t size;
	size_t capacity;
	size_t element_size;
};

vector_t *VectorCreate(size_t initial_capacity, size_t element_size)
{
	vector_t *vector = malloc(sizeof(vector_t)); 
	if (NULL == vector)
	{
		return NULL;
	}
	
	assert(0 < initial_capacity);
	assert(0 < element_size);
	
	vector->elements = calloc(initial_capacity, element_size);
	if (NULL == vector->elements)
	{
		free(vector); vector = NULL;
		return NULL;
	}
	
	vector->capacity = initial_capacity;
	vector->size = 0;
	vector->element_size = element_size;
		
	return vector;
}

void *VectorGetAccessToElement(vector_t *vector, size_t index)
{
	assert(vector);
	
	return ((char *)vector->elements + (index * vector->element_size));
}


int VectorAppend(vector_t *vector, const void *value)
{
	int return_status = 0;
	
	assert(vector);
	
	if (vector->size >= vector->capacity)
	{
		size_t new_capacity = vector->size * GROWTH_FACTOR;
		return_status = VectorReserve(vector, new_capacity);
	}

	memcpy((char *)(vector->elements) + (vector->size * vector->element_size), 
			value, 
			vector->element_size);
	
	++(vector->size);	
	
	return return_status; 
}

void VectorRemoveLast(vector_t *vector)
{
	assert(vector);
	
	--(vector->size);
}

int VectorIsEmpty(const vector_t *vector)
{
	assert(vector);
	
	return (0 == vector->size);
}                      

size_t VectorCapacity(const vector_t *vector)
{
	assert(vector);
	
	return (vector->capacity);
}

size_t VectorSize(const vector_t *vector)
{
	assert(vector);
	
	return (vector->size);
}

void VectorDestroy(vector_t *vector)
{
	assert(vector);
	free(vector->elements); vector->elements = NULL;
	free(vector); vector = NULL;
}

int VectorReserve(vector_t *vector, size_t size)
{
	int return_status = 1;
	void *buffer = NULL;
	
	assert(vector);
	
	buffer = realloc(vector->elements, size * vector->element_size);
	if (NULL != buffer)
	{
		vector->elements = buffer;
		vector->capacity = size;
		return_status = 0;
	}
	
	return return_status;
}

int VectorShrink(vector_t *vector)
{
	int return_status = 1;	
	
	assert(vector);
	
	if (vector->size < (vector->capacity) / GROWTH_FACTOR)
	{
		size_t new_capacity = vector->size * GROWTH_FACTOR;
		void *buffer = realloc(vector->elements, new_capacity * vector->element_size);
		
		if (NULL != buffer)
		{
			vector->elements = buffer;
			vector->capacity = new_capacity;
			return_status = 0;
		}
	}
	
	return return_status;
}
