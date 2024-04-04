
 /* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       0.0.1                                            *
 ~ Date          23.10.22                                         ~
 ~ Description   Priority queue impl using sll                    ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
#include <assert.h> /* assert */

#include "include/priority_queue.h"

priority_queue_t *PQCreate(cmp_func_t priority_func)
{
	assert(priority_func);
	return (SDListCreate(priority_func));
}

void PQDestroy(priority_queue_t *priority_queue)
{
	assert(priority_queue);
	SDListDestroy(priority_queue); priority_queue = NULL;
}

int PQEnqueue(priority_queue_t *priority_queue, void *value)
{
	assert(priority_queue);
	return (NULL == SDListInsert(priority_queue, value));
}

void *PQDequeue(priority_queue_t *priority_queue)
{
	assert(priority_queue);
	return SDListPopFront(priority_queue);
}

void *PQPeek(const priority_queue_t *priority_queue)
{
	assert(priority_queue);
	return (SDListGetValue(SDListIteratorFirst(priority_queue)));
}

void PQClear(priority_queue_t *priority_queue)
{
	assert(priority_queue);
	
	while (!PQIsEmpty(priority_queue))
	{
		SDListPopFront(priority_queue);
	}
}

void *PQErase(priority_queue_t *priority_queue, is_match_t is_match_function_p, 
			  void *param)
{
	sdll_iterator_t found_iter = NULL;
	void *found_iter_value = NULL;
	
	assert(priority_queue);
	assert(is_match_function_p);
	
	found_iter = SDListFindIf(SDListIteratorFirst(priority_queue),
						   	  SDListIteratorEnd(priority_queue),
							  is_match_function_p, 
							  param);
							
	if (!SDListIsIterEqual(SDListIteratorEnd(priority_queue), found_iter))
	{
		found_iter_value = SDListGetValue(found_iter);
		SDListRemove(found_iter);
	}
	
	return found_iter_value;
}

size_t PQSize(const priority_queue_t *priority_queue)
{
	assert(priority_queue);
	return (SDListSize(priority_queue));
}

int PQIsEmpty(const priority_queue_t *priority_queue)
{
	assert(priority_queue);
	return (SDListIsEmpty(priority_queue));
}

