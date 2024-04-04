
 /* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       0.0.1                                            *
 ~ Date          12.10.22                                         ~
 ~ Description   queue implementation using sll                   ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include <assert.h> /* assert */

#include "include/queue.h"

queue_t *QueueCreate(void)
{
	return SListCreate();
}

void *QueuePeek(const queue_t *queue)
{
	assert(queue);
	return (SListGetValue(SListIteratorFirst(queue)));
}

int Enqueue(queue_t *queue, const void *value)
{
	assert(queue);
	return (NULL == SListInsert(SListIteratorEnd(queue), (void *)value));
}

void *Dequeue(queue_t *queue)
{
	void *return_value = QueuePeek(queue);
	assert(queue);
	SListRemove(SListIteratorFirst(queue));
	return return_value;
}

size_t QueueSize(const queue_t *queue)
{
	assert(queue);
	return SListSize(queue);
}

void QueueDestroy(queue_t *queue)
{
	assert(queue);
	SListDestroy(queue);
}

int QueueIsEmpty(const queue_t *queue)
{
	assert(queue);
	return SListIsEmpty(queue);
}

void QueueAppend(queue_t *dest, queue_t *src)
{
	assert(dest);
	assert(src);
	SListAppendSList(dest, src);
}




