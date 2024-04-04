
 /* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Hadar Cohen                                      ~
 * Version       0.0.1                                            *
 ~ Date          19.10.22                                         ~
 ~ Description   Doubly linked list impl                          ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "include/dll.h"

struct dll_node
{
    void *value;
    struct dll_node *next;
    struct dll_node *prev;
};

typedef struct dll_node node_t;

struct dll
{
    node_t *head;
    node_t *tail;
};


dll_t *DListCreate(void)
{
	dll_t *list = (dll_t *)malloc(sizeof(dll_t));
	node_t *dummy_head = NULL;
	node_t *dummy_tail = NULL;
	
	if (NULL == list)
	{
		return NULL;
	}
	
	dummy_head = malloc(sizeof(node_t));
	dummy_tail = malloc(sizeof(node_t));
	if ((NULL == dummy_head) && (NULL == dummy_tail))
	{
		free(list); list = NULL;
		free(dummy_head); dummy_head = NULL;
		free(dummy_tail); dummy_tail = NULL;
		return NULL;
	}
	
	dummy_head->prev = NULL;
	dummy_tail->next = NULL;
	
	dummy_tail->prev = dummy_head;
	dummy_head->next = dummy_tail;
	dummy_tail->value = list;
	
	list->tail = dummy_tail;
	list->head = dummy_head;
		
	return list;
}

void DListDestroy(dll_t *list)
{
	dll_iterator_t runner = NULL;
	
	assert(list);
	
	runner = list->head;
	while (NULL != DListIteratorNext(runner))
	{
		runner = DListIteratorNext(runner);	
		free(runner->prev); runner->prev = NULL; 
	}
	
	free(runner); runner = NULL;
	free(list); list = NULL;
}

dll_iterator_t DListIteratorNext(dll_iterator_t position)
{
	assert(position);
	
	return (position->next);
}

dll_iterator_t DListIteratorPrev(dll_iterator_t position)
{
	assert(position);
	
	return (position->prev);
}

dll_iterator_t DListIteratorFirst(const dll_t *list)
{
	assert(list);
	
	return (list->head->next);
}

dll_iterator_t DListIteratorEnd(const dll_t *list)
{
	assert(list);
	
	return (list->tail);
}

dll_iterator_t DListInsertBefore(dll_iterator_t position, void *value)
{
	node_t *new_node = malloc(sizeof(node_t));
	
	assert(position);
	
	if (NULL != new_node)
	{
		DListSetValue(new_node, value);
		new_node->next = position;
		new_node->prev = DListIteratorPrev(position);
		
		position->prev = new_node;
		new_node->prev->next = new_node;
	}
		
	return new_node;
}

dll_iterator_t DListPushFront(dll_t *list, void *value)
{
	assert(list);
	
	return (DListInsertBefore(DListIteratorFirst(list), value));
}

dll_iterator_t DListPushBack(dll_t *list, void *value)
{
	assert(list);
	
	return (DListInsertBefore(DListIteratorEnd(list), value));
}

dll_iterator_t DListRemove(dll_iterator_t position_to_remove)
{
	node_t *next_node = NULL;
	
	assert(position_to_remove);
	assert(position_to_remove->next);
	assert(position_to_remove->prev);
	
	next_node = DListIteratorNext(position_to_remove);
	position_to_remove->prev->next = DListIteratorNext(position_to_remove);
	position_to_remove->next->prev = DListIteratorPrev(position_to_remove);
	
	free(position_to_remove); position_to_remove = NULL;
	return next_node;
}

void *DListPopFront(dll_t *list)
{
	void *popped = NULL;
	assert(list);
	
	popped = DListGetValue(DListIteratorFirst(list));
	DListRemove(DListIteratorFirst(list));
	return (popped);
}

void *DListPopBack(dll_t *list)
{
	void *popped = NULL;
	assert(list);
	
	popped = DListGetValue(DListIteratorEnd(list)->prev);
	DListRemove(DListIteratorEnd(list)->prev);
	return (popped);
}

void *DListGetValue(dll_iterator_t position)
{
	assert(position);
	
	return (position->value);
}

void DListSetValue(dll_iterator_t position, void *value)
{
	assert(position);
	
	position->value = value;
}

int DListIsIterEqual(dll_iterator_t iterator_1, dll_iterator_t iterator_2)
{
	assert(iterator_1);
	assert(iterator_2);
	
	return (iterator_1 == iterator_2);
}

size_t DListSize(const dll_t *list)
{
	size_t size = 0;
	dll_iterator_t runner = NULL;
	
	assert(list);
	
	runner = DListIteratorNext(list->head);
	while (NULL != DListIteratorNext(runner))
	{
		++size;
		runner = DListIteratorNext(runner);
	}
	
	return size;
}

int DListIsEmpty(const dll_t *list)
{
	assert(list);
	
	return (0 == DListSize(list));
}

int DListForEach(dll_iterator_t from, dll_iterator_t to, 
				 action_t action_function_ptr, void *param)
{
	int func_status = 0;
	dll_iterator_t runner = NULL;
	
	assert(from);
	assert(to);
	assert(action_function_ptr);
	
	runner = from;
	while (!DListIsIterEqual(runner,to) && (0 == func_status))
	{
		func_status = action_function_ptr(param, DListGetValue(runner));
		runner = DListIteratorNext(runner);
	}
	
	return func_status;
}

dll_iterator_t DListFind(dll_iterator_t from, dll_iterator_t to, 
						 is_match_t is_match_function_ptr, void *param)
{
	assert(from);
	assert(to);
	assert(is_match_function_ptr);

	while (!DListIsIterEqual(from, to) && 
		   0 == is_match_function_ptr(param, DListGetValue(from)))
	{
		from = DListIteratorNext(from);
	}
	
	return from;
}

void DListSplice(dll_iterator_t from, dll_iterator_t to, dll_iterator_t position)
{
	dll_iterator_t prev_from = NULL;
	
	assert(from);
	assert(to);
	prev_from = DListIteratorPrev(from);
	
	position->prev->next = from;
	from->prev = DListIteratorPrev(position);
	to->prev->next = position;
	position->prev = DListIteratorPrev(to);
	prev_from->next = to;
	to->prev = prev_from;	
}

size_t DListMultifind(dll_iterator_t from, dll_iterator_t to, is_match_t is_match_function_ptr, dll_t *found_items, void *param)
{
	size_t fount_items_counter = 0;
	
	assert(from);
	assert(to);
	assert(is_match_function_ptr);
	assert(found_items);
	
	while (!DListIsIterEqual(from, to))
	{
		if (1 == is_match_function_ptr(DListGetValue(from), param))
		{
			++fount_items_counter;
			DListPushBack(found_items, DListGetValue(from));
		}
		
		from = DListIteratorNext(from);
	}
	
	return fount_items_counter;
}
