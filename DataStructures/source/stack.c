
 /* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       0.0.1                                            *
 ~ Date          02.10.22                                         ~
 ~ Description   stack implementation                             ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */

#include "include/stack.h"

struct stack
{
    void *stack_array;
    size_t capacity;
    size_t element_size;
    size_t top;
};

stack_t *StackCreate(size_t size, size_t element_size)
{
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
	stack->stack_array = malloc(size * element_size);
	
	if (NULL != stack)
	{
		assert(stack->stack_array);
		stack->capacity = size;
		stack->element_size = element_size;
		stack->top = 0;
	}	
	return stack;
}

void StackPush(stack_t *stack, void *value)
{
	assert(stack);
	
	if (StackSize != StackCapacity)
	{
		memcpy((char *)(stack->stack_array) + (stack->top * stack->element_size), value, stack->element_size);
		++(stack->top);
	}
}

void StackPop(stack_t *stack)
{
	assert(stack);
	--(stack->top);
}

void *StackPeek(const stack_t *stack)
{
	assert(stack);
	return ((char *)stack->stack_array + ((stack->top - 1) * stack->element_size));
}

int StackIsEmpty(const stack_t *stack)
{
	assert(stack);
	return (0 == stack->top);
}

size_t StackCapacity(const stack_t *stack)
{
	assert(stack);
	return (stack->capacity);
}

size_t StackSize(const stack_t *stack)
{
	assert(stack);
	return (stack->top);
}

void StackDestroy(stack_t *stack)
{
	assert(stack);
	free(stack->stack_array);
	free(stack);
}
