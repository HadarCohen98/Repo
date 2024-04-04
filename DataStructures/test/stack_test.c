
#include "include/stack.h"

#include <stdio.h> /*printf*/

int main()
{
	size_t size = 4;
	size_t element_size = sizeof(int);
	int x = 5;
	int y = 29;
	
	stack_t *my_stack = StackCreate(size, element_size);
	printf("--------initialization-------\n");
	printf("stack is empty? %d\n", StackIsEmpty(my_stack));
	printf("stack capacity- %lu\n", StackCapacity(my_stack));
	printf("stack size- %lu\n", StackSize(my_stack));
	
	printf("--------first push-------\n");
	StackPush(my_stack, &x); 
	printf("stack is empty? %d\n", StackIsEmpty(my_stack));
	printf("stack capacity- %lu\n", StackCapacity(my_stack));
	printf("stack size- %lu\n", StackSize(my_stack));
	printf("stack[0] = %d\n", *(int *)StackPeek(my_stack));
	
	printf("--------second push-------\n");
	StackPush(my_stack, &y); 
	printf("stack capacity- %lu\n", StackCapacity(my_stack));
	printf("stack size- %lu\n", StackSize(my_stack));
	printf("stack[1] = %d\n", *(int *)StackPeek(my_stack));
	
	printf("--------pop-------\n");
	StackPop(my_stack); 
	printf("stack capacity- %lu\n", StackCapacity(my_stack));
	printf("stack size- %lu\n", StackSize(my_stack));
	printf("stack[0] = %d\n", *(int *)StackPeek(my_stack));
	
	StackDestroy(my_stack);
	printf(":)\n");
	return 0; 
}
