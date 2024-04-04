/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       1.0                                             *
 ~ Date          04/12/22                                        ~
 ~ Description   Queue Header                                    ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#ifndef __QUEUE__
#define __QUEUE__

#include <stddef.h>

#include "sll.h"

typedef sll_t queue_t;

/*
Description- The QueueCreate() function create a new queue_t type.
Return Value- The function returns a pointer to the new queue_t.
Notes- 
The function uses malloc, hence can fail (in the case of failure the returned pointer will be NULL).
*/
queue_t *QueueCreate(void);

/*
Description- The QueuePeek() function get the value of the first element entered the queue (the head of the list).
Return Value- The function returns the value in void pointer type.
*/
void *QueuePeek(const queue_t *queue);

/*
Description- The Enqueue() function insert a new value to the queue (before the tail of the list).
Return Value- The function uses malloc, hence can fail, the reutrn value is 0 in case of success and 1 if the function fails.
*/
int Enqueue(queue_t *queue, const void *value);

/*
Description- The Dequeue() function removes the first element entered the queue.
Return Value- The function returns the value of the new first element of the queue.
Notes-
If the queue is empty the Dequeue() function will lead to undefined behvior and probably segmentation fault.
*/
void *Dequeue(queue_t *queue);

/*
Description- The QueueSize() function return the number of values in the queue.
Return Value- The function return the size of the queue in size_t tpye.
*/
size_t QueueSize(const queue_t *queue);

/*
Description- The QueueDestroy() function free the list and the queue itself.
*/
void QueueDestroy(queue_t *queue);

/*
Description- The QueueIsEmpty() function checks if the queue is empty (i.e the head iterator of the list point to NULL).
Return Value- The function return 1 if the list is empty and 0 otherwise.
*/
int QueueIsEmpty(const queue_t *queue);

/*
Description- The QueueAppend() function concat the src queue to the dest queue, i.e the last element of dest will point to the first element of src. 
src will become an empty list.
*/
void QueueAppend(queue_t *dest, queue_t *src);

#endif /* __QUEUE__ */
