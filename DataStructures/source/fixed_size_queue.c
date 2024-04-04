/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       1.0.0                                           *
 ~ Date          05.12.22                                        ~
 ~ Description   Fixed Size Queue Implemention                   ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include "include/fixed_size_queue.h"

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

struct fsq
{
    queue_t *queue;
    size_t capacity;
    size_t size;
};

fsq_t *FSQCreate(size_t capacity)
{
    fsq_t *fsq = NULL;

    assert(capacity > 0);

    fsq = (fsq_t *)malloc(sizeof(fsq_t));
    if (NULL == fsq)
    {
        return NULL;
    }

    fsq->capacity = capacity;
    fsq->size = 0;
    fsq->queue = QueueCreate();
    if (NULL == fsq->queue)
    {
        free(fsq); fsq = NULL;
        return NULL;
    }

	return fsq;
}

void *FSQPeek(const fsq_t *fsq)
{
	assert(fsq);
	assert(fsq->queue);

    return (QueuePeek(fsq->queue));
}

int FSQEnqueue(fsq_t *fsq, const void *value)
{
	assert(fsq);
	assert(fsq->queue);

    if (fsq->capacity <= fsq->size)
    {
        return 1;
    }

    ++(fsq->size);
	return Enqueue(fsq->queue, value);
}

void *FSQDequeue(fsq_t *fsq)
{
    assert(fsq);
    assert(fsq->queue);
	
	--(fsq->size);
    return Dequeue(fsq->queue);
}

size_t FSQSize(const fsq_t *fsq)
{
	assert(fsq);

	return fsq->size;
}

void FSQDestroy(fsq_t *fsq)
{
	assert(fsq);

	QueueDestroy(fsq->queue); fsq->queue = NULL;
    free(fsq); fsq = NULL;
}

int FSQIsEmpty(const fsq_t *fsq)
{
	assert(fsq);

	return (0 == fsq->size);
}





