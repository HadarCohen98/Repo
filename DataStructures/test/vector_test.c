#include <stdio.h> /* printf */

#include "include/vector.h"

int main()
{
	size_t initial_capacity = 10;
	int value1 = 3;
	int value2 = 7; 
	int value3 = -6; 

	
	vector_t *my_vector = VectorCreate(initial_capacity, sizeof(int));
	printf("return status of IsEmpty- %d\n", VectorIsEmpty(my_vector));
	
	printf("\n------first append------\n"); 
	VectorAppend(my_vector, &value1); 
	printf("vector size- %lu\n", VectorSize(my_vector));
	printf("vector capacity- %lu\n", VectorCapacity(my_vector));
	printf("elements[0] = %d\n", *((int *)VectorGetAccessToElement(my_vector, 0)));
	
	printf("\n------second append------\n"); 
	VectorAppend(my_vector, &value2); 
	printf("vector size- %lu\n", VectorSize(my_vector));
	printf("vector capacity- %lu\n", VectorCapacity(my_vector));
	printf("elements[1] = %d\n", *((int *)VectorGetAccessToElement(my_vector, 1)));
	
	printf("\n------third append------\n"); 
	VectorAppend(my_vector, &value3); 
	printf("vector size- %lu\n", VectorSize(my_vector));
	printf("vector capacity- %lu\n", VectorCapacity(my_vector));
	printf("elements[2] = %d\n", *((int *)VectorGetAccessToElement(my_vector, 2)));
	
	printf("\n------remove last------\n"); 
	VectorRemoveLast(my_vector);
	printf("vector size- %lu\n", VectorSize(my_vector));
	printf("vector capacity- %lu\n", VectorCapacity(my_vector));
	printf("elements[1] = %d\n", *((int *)VectorGetAccessToElement(my_vector, VectorSize(my_vector) - 1)));
	
	printf("\n------is empty------\n"); 
	printf("return status of IsEmpty- %d\n", VectorIsEmpty(my_vector));
	
	printf("\n------reserve------\n"); 
	printf("return status of VectorReserve- %d\n", VectorReserve(my_vector, 20));
	printf("vector size- %lu\n", VectorSize(my_vector));
	printf("vector capacity- %lu\n", VectorCapacity(my_vector));	
	
	printf("\n------shrink------\n"); 
	printf("return status of VectorReserve- %d\n", VectorShrink(my_vector));
	printf("vector size- %lu\n", VectorSize(my_vector));
	printf("vector capacity- %lu\n", VectorCapacity(my_vector));	
	
	VectorDestroy(my_vector);
	return 0;
}
