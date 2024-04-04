/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       1.0                                             *
 ~ Date          04/12/22                                        ~
 ~ Description   Priority Queue Header                           ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#ifndef __PRIORITY_QUEUE__
#define __PRIORITY_QUEUE__

#include "sorted_list.h"

#include <stddef.h> /* size_t */

 /* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Priority queue is a data structure that differs from a normal  ~
 * queue in that it has an additional layer that describes        /
 / the priority of each member. The priority assigned to each     *
 * element determines the order of its exit from the queue.       /
 / ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
 
typedef sdll_t priority_queue_t;

/*
Description- The PQCreate() function create priority queue of priority_queue_t 
type. The priorotizing of the queue is based on "priority_func". 
The compare function must return int and recieve param and value. 
Return Value- The function returns a pointer to the new priority_queue_t. 
If the function fails the return value will be NULL.
Time Complexity- O(1).
*/
priority_queue_t *PQCreate(cmp_func_t priority_func);

/*
Description- The PQDestroy() function free every element in the queue and the 
queue itself.
Time Complexity- O(n).
*/
void PQDestroy(priority_queue_t *priority_queue);

/*
Description- The PQEnqueue() function insert a new value to "priority_queue" 
in the right position (according to the priority function of the queue).
Return Value- In the case of success the function return 0, otherwise it 
returns 1.
Time Complexity- worst case O(n), best case O(1) depend on the priority.
*/
int PQEnqueue(priority_queue_t *priority_queue, void *value);

/*
Description- The PQDequeue() function removes the first element in 
"priority_queue". 
Return Value- The function returns the value of the removed element.
Notes-
If the list is empty the PQDequeue() function will lead to undefined behvior.
Time Complexity- O(1).
*/
void *PQDequeue(priority_queue_t *priority_queue);

/*
Description- The PQPeek() function get the value of the first element in the 
queue.
Return Value- The function returns the value in void pointer type.
Time Complexity- O(1).
*/
void *PQPeek(const priority_queue_t *priority_queue);

/*
Description- The PQClear() function removes all the elements in 
"priority_queue". After the function call the queue will be empty. 
Time Complexity- O(n).
*/
void PQClear(priority_queue_t *priority_queue);

/*
Description- The PQErase() function removes the element in "priority_queue" 
that matches "param" by the definition of "is_match_function_p". 
If there is not such element the function do nothing.
Return Value- The function return the value that was removed. If there isn't a 
value that matches param the return value will be thr dummy node.
Notes-
The is_match_function_p must be a boolean function.
If the list is empty the PQErase() function will lead to undefined behvior and 
probably segmentation fault.
Time Complexity- O(n).
*/
void *PQErase(priority_queue_t *priority_queue, is_match_t is_match_function_p, void *param);

/*
Description- The PQSize() function conuts the number of elements in 
"priority_queue".
Return Value- The function return the size of the queue in size_t type.
Time Complexity- O(n).
*/
size_t PQSize(const priority_queue_t *priority_queue);

/*
Description- The PQIsEmpty() function checks if "priority_queue" is empty.
Return Value- The function return 1 if the list is empty and 0 otherwise.
Time Complexity- O(n).
*/
int PQIsEmpty(const priority_queue_t *priority_queue);

#endif /* __PRIORITY_QUEUE__ */
