
 /* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       0.0.1                                            *
 ~ Date          06.09.22                                         ~
 ~ Description   singly linked list implementation                ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include <stdlib.h> /* malloc, calloc, free */
#include <assert.h> /* assert */

#include "include/sll.h"

static void UpdateTail(sll_t *sll, iterator_t tail);

struct sll_node
{
    void *value;
    iterator_t next;
};

struct sll
{
    iterator_t head;
    iterator_t tail;
};

typedef struct sll_node node_t;

sll_t *SListCreate(void)
{
	sll_t *list = malloc(sizeof(sll_t)); 
	if (NULL == list)
	{
		return NULL;
	}
	
	list->head = (iterator_t)malloc(sizeof(node_t));
	if (NULL == list->head)
	{
		free(list); list = NULL;
		return NULL;
	}
	
	list->head->next = NULL;
	list->head->value = list;
	list->tail = list->head;

	return list;	
}

iterator_t SListInsert(iterator_t position, void *value)
{
	node_t *new_position = (node_t *)malloc(sizeof(node_t));
	if (NULL == new_position)
	{
		return NULL;
	}
	
	assert(position);
	
	new_position->value = SListGetValue(position);
	new_position->next = SListIteratorNext(position);
	
	SListSetValue(position, value);
	position->next = new_position;
		
	if (NULL == new_position->next)
	{	
		UpdateTail(new_position->value, new_position);
	}
	
	return position;
}

void *SListGetValue(iterator_t position)
{
	assert(position);
	
	return (position->value);
}

void SListSetValue(iterator_t position, void *value)
{
	assert(position);
	
	position->value = value;
}

iterator_t SListRemove(iterator_t position_to_remove)
{
	if (NULL != position_to_remove->next)
	{
		iterator_t temp = position_to_remove->next;
		
		SListSetValue(position_to_remove, temp->value);
		position_to_remove->next = temp->next;
		free(temp); temp = NULL;
		
		if (NULL == position_to_remove->next)
		{
			UpdateTail(position_to_remove->value, position_to_remove);
		}
	}
	
	return position_to_remove;
}

iterator_t SListIteratorNext(iterator_t position)
{
	assert(position);
	
	return (position->next);
}

iterator_t SListIteratorEnd(const sll_t *list)
{
	assert(list);
	
	return (list->tail);	
}

iterator_t SListIteratorFirst(const sll_t *list)
{
	assert(list);
	
	return (list->head);
}

int IsItrEqual(iterator_t iterator1, iterator_t iterator2)
{
	assert(iterator1);
	assert(iterator2);
	
	return (iterator1 == iterator2);
}

int SListForEach(iterator_t from, iterator_t to, 
				 action_t action_function_ptr, void *param)
{
	int func_status = 0;
	iterator_t runner = NULL;
	
	assert(from);
	assert(to);
	assert(action_function_ptr);
	
	runner = from;
	
	while (!(IsItrEqual(runner,to)) && (0 == func_status))
	{
		func_status = action_function_ptr(param, SListGetValue(runner));
		runner = SListIteratorNext(runner);
	}
	
	return func_status;
}

size_t SListSize(const sll_t *list)
{
	size_t size = 0;
	iterator_t runner = NULL;
	
	assert(list);
	
	runner = list->head;
	
	while (NULL != SListIteratorNext(runner))
	{
		++size;
		runner = SListIteratorNext(runner);
	}
	
	return size;
}

int SListIsEmpty(const sll_t *list)
{
	assert(list);

	return (NULL == list->head->next);
}

void SListDestroy(sll_t *list)		
{
	assert(list);
	
	while(!SListIsEmpty(list))
	{
		SListRemove(SListIteratorFirst(list));
	}


	free(SListIteratorFirst(list));
	free(list);	list = NULL;
}

iterator_t SListFind(iterator_t from, iterator_t to, is_match_t 
					 is_match_function_ptr, void *param) 	
{
	iterator_t runner = from;

	assert(from);
	assert(to);
	assert(is_match_function_ptr);	
	
	while (!(IsItrEqual(runner,to)) && 
		  (!is_match_function_ptr(runner->value, param)))
	{
		runner = SListIteratorNext(runner);
	}

	return runner;
}

void SListAppendSList(sll_t *dest, sll_t *src)
{	
	node_t *new_dummy = (node_t *)malloc(sizeof(node_t));
	
	assert(dest);
	assert(src);
	
	new_dummy->value = src;
	new_dummy->next = NULL;	
	
	dest->tail->next = src->head;
	SListRemove(dest->tail);
	
	src->tail->value = dest;
	dest->tail = src->tail;
	dest->tail->value = dest;
	
	src->head = new_dummy;
	src->tail = new_dummy;
}

static void UpdateTail(sll_t *sll, iterator_t tail)
{
	sll->tail = tail;
}
