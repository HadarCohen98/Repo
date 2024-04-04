
 /* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       1.0.0                                            *
 ~ Date          01.12.22                                         ~
 ~ Description   Heap implementation                              ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include "include/heap.h"
#include "include/vector.h"

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */
#include <sys/types.h> /*ptrdiff_t */

#define INIT_CAPACITY 10
#define WORD_SIZE sizeof(size_t)

struct heap
{
    vector_t *vector;
    cmp_func_t cmp_func_p;
};

static void *HeapGetElement(const heap_t *heap, size_t index);
static void HeapifyUp(heap_t *heap, size_t end_idx);
static void HeapifyDown(heap_t *heap, size_t start_idx);
static void HeapSwapElements(void **a, void **b);
static ptrdiff_t HeapFindIndex(heap_t *heap, 
                             int (*is_match)(const void *param, 
                                             const void *value),
                             const void *param,
                             ptrdiff_t start_idx); 


/* API Functions */
heap_t *HeapCreate(cmp_func_t cmp_func_p)
{
    heap_t *heap = NULL;

    assert(cmp_func_p);

    heap = (heap_t *)malloc(sizeof(heap_t));
    if (NULL == heap)
    {
        return NULL;
    }

    heap->vector = VectorCreate(INIT_CAPACITY, WORD_SIZE);
    if (NULL == heap->vector)
    {
        free(heap); heap = NULL;
        return NULL;
    }

    heap->cmp_func_p = cmp_func_p;

    return heap;
}

void HeapDestroy(heap_t *heap)
{
    assert(heap);
    assert(heap->vector);

    VectorDestroy(heap->vector); heap->vector = NULL;
    free(heap); heap = NULL;
}

status_t HeapPush(heap_t *heap, void *value)
{
    assert(heap);
    assert(heap->vector);

    if (FAILURE == VectorAppend(heap->vector, &value))
    {
        return MEMORY_ALLOCATION_ERROR;
    }

    HeapifyUp(heap, HeapSize(heap) - 1);
    return SUCCESS;
}

void *HeapPop(heap_t *heap)
{
    void *data_removed = NULL;
    
    assert(heap);
    assert(heap->vector);

    data_removed = HeapPeek(heap);

    HeapSwapElements(HeapGetElement(heap, 0), 
                     HeapGetElement(heap, HeapSize(heap) - 1));
    
    VectorRemoveLast(heap->vector);
    HeapifyDown(heap, 0);

    return data_removed;
}

void *HeapPeek(const heap_t *heap)
{
    assert(heap);

    return *(void**)HeapGetElement(heap, 0);
}

size_t HeapSize(const heap_t *heap)
{
    assert(heap);
    assert(heap->vector);

    return VectorSize(heap->vector);
}

int HeapIsEmpty(const heap_t *heap)
{
    assert(heap);
    assert(heap->vector);

    return VectorIsEmpty(heap->vector);
}

void *HeapRemove(heap_t *heap, 
                 int (*is_match)(const void *param, 
                                 const void *value), 
                 const void *param)
{

    ptrdiff_t index_to_remove = 0;
    void *removed_data = 0;

    assert(heap);
    assert(heap->vector);
    assert(is_match);

    index_to_remove = HeapFindIndex(heap, is_match, param, 0);
    removed_data = *(void **)VectorGetAccessToElement(heap->vector, index_to_remove);

    if (-1 == index_to_remove)
    {
        return NULL;
    }

    if (!HeapIsEmpty(heap))
    {
        HeapSwapElements(HeapGetElement(heap, index_to_remove),
                         HeapGetElement(heap, HeapSize(heap) - 1));
    }

    VectorRemoveLast(heap->vector);
    HeapifyDown(heap, 0);

    return removed_data;
}

/* Static Functions */
static void *HeapGetElement(const heap_t *heap, size_t index)
{
    assert(heap);
    assert(heap->vector);

    return VectorGetAccessToElement(heap->vector, index);
}

static void HeapifyUp(heap_t *heap, size_t index)
{
    size_t parent_idx = (index - 1) / 2;
    void **node = HeapGetElement(heap, index);
    void **node_parent = HeapGetElement(heap, parent_idx);

    assert(heap->cmp_func_p);

    if (0 != index)
    {
        if (0 < heap->cmp_func_p(*node, *node_parent))
        {
            HeapSwapElements(node, node_parent);
            HeapifyUp(heap, parent_idx);
        }
    }
}

static void HeapifyDown(heap_t *heap, size_t start_idx)
{
    size_t right_child_idx = (2 * start_idx + 2);
    size_t left_child_idx = (2 * start_idx + 1);
    void **node = HeapGetElement(heap, start_idx);
    void **right_child = HeapGetElement(heap, right_child_idx);
    void **left_child = HeapGetElement(heap, left_child_idx);
    
    assert(heap->cmp_func_p);

    if ((right_child_idx < (HeapSize(heap))))
    {
        if (0 > heap->cmp_func_p(*node, *right_child))
        {
            if (0 > heap->cmp_func_p(*left_child, *right_child))
            {
                HeapSwapElements(node, right_child);
                HeapifyDown(heap, right_child_idx);
            }
            else
            {
                HeapSwapElements(node, left_child);
                HeapifyDown(heap, left_child_idx);
            }
        }
    }

    if ((left_child_idx < (HeapSize(heap))))
    {
        if (0 > heap->cmp_func_p(*node, *left_child))
        {
            HeapSwapElements(node, left_child);
            HeapifyDown(heap, left_child_idx);
        }
    }   
}

static void HeapSwapElements(void **a, void **b)
{
    void *temp = *a;
    *a = *b;
    *b = temp;
}

static ptrdiff_t HeapFindIndex(heap_t *heap, 
                        int (*is_match)(const void *param, 
                                        const void *value),
                        const void *param,
                        ptrdiff_t start_idx)
{

    assert(heap->cmp_func_p);

    if ((size_t)start_idx >= HeapSize(heap))
    {
        return -1;
    }

    if (1 != is_match(param, *(void**)HeapGetElement(heap, start_idx)))
    {
        return HeapFindIndex(heap, 
                            is_match, 
                            param,
                            start_idx + 1);
    }
    
    return start_idx;
}