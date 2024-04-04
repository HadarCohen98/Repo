 /* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       1.0.0                                            *
 ~ Date          03.12.22                                         ~
 ~ Description   Priority Queue Heap Implementation               ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include "include/pq_heap.h"
#include "include/heap.h"

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

struct pq_heap
{
	heap_t *heap;
};


/* API Functions */
pq_heap_t *PQHeapCreate(cmp_func_t priority_func)
{
    pq_heap_t *pq_heap = NULL;
	
    assert(priority_func);

    pq_heap = (pq_heap_t *)malloc(sizeof(pq_heap_t));
	if (NULL == pq_heap)
    {
        return NULL;
    }
    
    pq_heap->heap = HeapCreate(priority_func);
    if (NULL == pq_heap->heap)
    {
        free(pq_heap); pq_heap = NULL;
        return NULL;
    }

    return (pq_heap);
}

void PQHeapDestroy(pq_heap_t *pq_heap)
{
	assert(pq_heap);
    assert(pq_heap->heap);

	HeapDestroy(pq_heap->heap); pq_heap->heap = NULL;
    free(pq_heap); pq_heap = NULL;
}

int PQHeapEnqueue(pq_heap_t *pq_heap, void *value)
{
	assert(pq_heap);
    assert(pq_heap->heap);

	return HeapPush(pq_heap->heap, value);
}

void *PQHeapDequeue(pq_heap_t *pq_heap)
{
	assert(pq_heap);
    assert(pq_heap->heap);

	return HeapPop(pq_heap->heap);
}

void *PQHeapPeek(const pq_heap_t *pq_heap)
{
	assert(pq_heap);
    assert(pq_heap->heap);

	return (HeapPeek(pq_heap->heap));
}

void PQHeapClear(pq_heap_t *pq_heap)
{
	assert(pq_heap);
	
	while (!PQHeapIsEmpty(pq_heap))
	{
		PQHeapDequeue(pq_heap);
	}
}


void *PQHeapErase(pq_heap_t *pq_heap, 
                  int (*is_match)(const void *param, 
                                  const void *value), 
                  void *param)
{
	assert(pq_heap);
	assert(pq_heap->heap);
    assert(is_match);

	return HeapRemove(pq_heap->heap, is_match, param);
}

size_t PQHeapSize(const pq_heap_t *pq_heap)
{
	assert(pq_heap);
    assert(pq_heap->heap);

	return (HeapSize(pq_heap->heap));
}

int PQHeapIsEmpty(const pq_heap_t *pq_heap)
{
	assert(pq_heap);
    assert(pq_heap->heap);

	return (HeapIsEmpty(pq_heap->heap));
}

