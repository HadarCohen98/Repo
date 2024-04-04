/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       1.0.0                                             *
 ~ Date          05.12.22                                        ~
 ~ Description   DLL Header                                      ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#ifndef __DOUBLY_LINKED_LIST__
#define __DOUBLY_LINKED_LIST__

#include <stddef.h> /* size_t */

typedef struct dll dll_t;
typedef struct dll_node *dll_iterator_t;
typedef int (*is_match_t)(void *param, void *value);
typedef int (*action_t)(void *param, void *value);

dll_t *DListCreate(void);
/*
Description- The DListCreate() function creates a new doubly linked list 
of dll_t type.
Return Value- The function returns a pointer to the new dll_t, in the case 
of failure the returned pointer will be NULL.
Time complexity- O(1).
*/

void DListDestroy(dll_t *list);
/*
Description- The DListDestroy() function frees every element in the list 
and the list itself.
Time complexity- O(n).
*/

dll_iterator_t DListIteratorNext(dll_iterator_t position);
/*
Description- The DListIteratorNext() function returns the the next 
iterator after position in the list.
Return Value- The function returns the next iterator.
Time complexity- O(1).
*/

dll_iterator_t DListIteratorPrev(dll_iterator_t position);
/*
Description- The DListIteratorPrev() function returns the the previous 
iterator before position in the list.
Return Value- The function returns the previous iterator.
Time complexity- O(1).
*/

dll_iterator_t DListIteratorFirst(const dll_t *list);
/*
Description- The DListIteratorFirst() function returns the the first 
iterator in the list.
Return Value- The function returns the first iterator. If the 
list is empty the function will return NULL.
Time complexity- O(1).
*/

dll_iterator_t DListIteratorEnd(const dll_t *list);
/*
Description- The DListIteratorEnd() function returns the the last iterator 
in the list.
Return Value- The function returns the last iterator.
Time complexity- O(1).
*/

dll_iterator_t DListInsertBefore(dll_iterator_t position, void *value);
/*
Description- The DListInsertBefore() function inserts a new value to the 
list before the position mentioned.
Return Value- The function returns the new iterator.
Notes- 
The function uses malloc but fails safly, i.e if the malloc function fails 
the DListInsertBefore function returns the position mentioned.
Time complexity- O(1).
*/

dll_iterator_t DListPushFront(dll_t *list, void *value);
/*
Description- The DListPushFront() function inserts a new value to the 
front of the list. The new value will be in the first iterator of the list.
Return Value- The function returns the new iterator.
Time complexity- O(1).
*/

dll_iterator_t DListPushBack(dll_t *list, void *value);
/*
Description- The DListPushBack() function inserts a new value to the end 
of the list. 
Return Value- The function returns the new iterator.
Time complexity- O(1).
*/

void *DListPopFront(dll_t *list);
/*
Description- The DListPopFront() function removes the first iterator from 
the list.
Return Value- The function returns the value of the iterator that was 
removed.
Time complexity- O(1).
*/

void *DListPopBack(dll_t *list);
/*
Description- The DListPopBack() function removes the last iterator from 
the list.
Return Value- The function returns the value of the iterator that was 
removed.
Time complexity- O(1).
*/

dll_iterator_t DListRemove(dll_iterator_t position_to_remove);
/*
Description- The DListRemove() function removes the position mentioned 
from the list.
Return Value- The function returns a pointer to the next iterator after 
the removal. If the list is empty the SListRemove() function will lead to 
undefined behvior.
Time complexity- O(1).
*/

void *DListGetValue(dll_iterator_t position);
/*
Description- The DListGetValue() function gets the value of the position 
mentioned.
Return Value- The function returns the value in void pointer type.
Time complexity- O(1).
*/

void DListSetValue(dll_iterator_t position, void *value);
/*
Description- The DListSetValue() function sets the value of the position 
mentioned.
Time complexity- O(1).
*/

int DListIsIterEqual(dll_iterator_t iterator_1, dll_iterator_t iterator_2);
/*
Description- The DListIsIterEqual() function checks for equality between 
two iterators.
Return Value- The function returns 1 if the iterators are equal and 0 if 
not.
Time complexity- O(1).
*/

size_t DListSize(const dll_t *list);
/*
Description- The DListSize() function counts the number of values in the 
list.
Return Value- The function returns the size of the list in size_t type.
Time complexity- O(n).
*/

int DListIsEmpty(const dll_t *list);
/*
Description- The DListIsEmpty() function checks if the list is empty.
Return Value- The function return 1 if the list is empty and 0 otherwise.
Time complexity- O(1).
*/

int DListForEach(dll_iterator_t from, dll_iterator_t to, 
				 action_t action_function_ptr, void *param);
/*
Description- The DListForEach() function operates the action_function_ptr 
on every value on the list from the "from" iterator up to the "to" 
iterator (exclude the "to" iterator) base on the parameter mentioned.
Return Value- The function returns the return status of the 
action_function_ptr.
Time complexity- O(n).
*/

dll_iterator_t DListFind(dll_iterator_t from, dll_iterator_t to, 
						 is_match_t is_match_function_ptr, void *param);
/*
Description- The DListFind() function checks for "param" in every value on 
the list from the "from" iterator up to the "to" iterator (exclude the 
"to" iterator) using the is_match_function_ptr.
Return Value- The function return the iterator which value is matched with 
"param", if there is not value matched the return value is NULL.
Time complexity- O(n).
*/

void DListSplice(dll_iterator_t from, dll_iterator_t to, dll_iterator_t position);
/*
Description- The DListSplice() function connects one list to another. the 
iterators from "from" to "to" in one list will be inserted before 
"position" in other list.
Time complexity- O(1).
*/

size_t DListMultifind(dll_iterator_t from, dll_iterator_t to, is_match_t is_match_function_ptr, dll_t *found_items, void *param);
/*
Description- The DListMultifind() function checks for "param" in every 
value on the list from the "from" iterator up to the "to" iterator 
(exclude the "to" iterator) using the is_match_function_ptr.
The list "found_items" will contain all the values found by the function 
is_match_function_ptr.
Return Value- The function return how many times param is found in the list.
Time complexity- O(n).
*/

#endif /* __DOUBLY_LINKED_LIST__ */

