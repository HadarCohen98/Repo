/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       1.0                                             *
 ~ Date          04/12/22                                        ~
 ~ Description   Sorted List Header                              ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
#ifndef __SORTED_LIST__
#define __SORTED_LIST__

#include "dll.h"

typedef struct sdll sdll_t;

typedef dll_iterator_t sdll_iterator_t;

/*The return value of action_function_ptr must be int.
If the user wants to use function that doesn't return int he'll need to 
use wrap that function in another function that will return int.*/
typedef int (*cmp_func_t)(void *param, void *value);


/*
Description- The SDListCreate() function creates sorted list of sdll_t type. 
The sorting of the list is based on cmp_func_p. 
The compare function must return int and recieve param and value. 
Return Value- The function returns a pointer to the new sorted list.
In the case of failure the returned pointer will be NULL.
Time Complexity- O(1).
*/
sdll_t *SDListCreate(cmp_func_t cmp_func_p);

/*
Description- The SDListDestroy() function frees every element in the list
and the list itself. The freed elements are set to NULL.
Time Complexity- O(n).
*/
void SDListDestroy(sdll_t *slist);

/*
Description- The SDListIteratorNext() function looks for the the iterator 
after "position" in the list.
Return Value- The function returns the next iterator.
Time Complexity- O(1).
*/
sdll_iterator_t SDListIteratorNext(sdll_iterator_t position);

/*
Description- The SDListIteratorPrev() function looks for the the iterator 
before "position" in the list.
Return Value- The function returns the previous node.
Time Complexity- O(1).
*/
sdll_iterator_t SDListIteratorPrev(sdll_iterator_t position);

/*
Description- The SDListIteratorFirst() function looks for the the first 
iterator in "slist".
Return Value- The function returns the first iterator. 
If the list is empty the function will return NULL.
Time Complexity- O(1).
*/
sdll_iterator_t SDListIteratorFirst(const sdll_t *slist);

/*
Description- The SDListIteratorEnd() function looks for the the last 
iterator in "slist".
Return Value- The function returns the last iterator.
Time Complexity- O(1).
*/
sdll_iterator_t SDListIteratorEnd(const sdll_t *slist);

/*
Description- The SDListInsert() function inserts a new value to "slist" 
in the right position (according to the sorting of slist).
Return Value- The function returns the new iterator. If the insertion faild
the return value will be NULL.
Time Complexity- worst case- O(n), best case- O(1).
*/
sdll_iterator_t SDListInsert(sdll_t *slist, void *value); 

/*
Description- The SDListPopFront() function removes the first node from "slist".
Return Value- The function returns the value of the node that was removed.
Time Complexity- O(1).
*/
void *SDListPopFront(sdll_t *slist);

/*
Description- The SDListPopBack() function removes the last node from "slist".
Return Value- The function returns the value of the node that was removed.
Time Complexity- O(1).
*/
void *SDListPopBack(sdll_t *slist);

/*
Description- The SDListRemove() function removes the iterator in
"position_to_remove" from the list.
Return Value- The function returns the next iterator after the removal of 
"position_to_remove". 
If the list is empty SDListRemove() will lead to undefined behvior.
Time Complexity- O(1).
*/
sdll_iterator_t SDListRemove(sdll_iterator_t position_to_remove);

/*
Description- The SDListGetValue() function gets the value of the iterator in
"position".
Return Value- The function returns the value in void pointer type.
Time Complexity- O(1).
*/
void *SDListGetValue(sdll_iterator_t position);

/*
Description- The SDListIsIterEqual() function checks for equality between 
iterator_1 and iterator_2.
Return Value- The function returns 1 if the iterators are equal and 0 if not.
Time Complexity- O(1).
*/
int SDListIsIterEqual(sdll_iterator_t iterator_1, sdll_iterator_t iterator_2);

/*
Description- The SDListSize() function returns the number of nodes in "slist".
Return Value- The function return the size of the list in size_t type.
Time Complexity- O(n).
*/
size_t SDListSize(const sdll_t *slist);

/*
Description- The SDListIsEmpty() function checks if "slist" is empty.
Return Value- The function return 1 if the list is empty and 0 otherwise.
Time Complexity- O(n).
*/
int SDListIsEmpty(const sdll_t *slist);

/*
Description- The SDListForEach() function operate "action_function_ptr" on 
every node in the list from the "from" iterator up to the "to" iterator 
(exclude the "to" iterator). 
The use of "param" is defined in the action_function_ptr.
Return Value- The function returns the return status of "action_function_ptr".
Time Complexity- O(n).
*/
int SDListForEach(sdll_iterator_t from, sdll_iterator_t to, 
				  action_t action_function_ptr, void *param);

/*
Description- The SDListFindIf() function checks for "param" in every value in 
the list from the "from" iterator up to the "to" iterator (exclude the "to" 
iterator) using "is_match_function_ptr".
Return Value- The function return the iterator which value is matched with 
"param", if there is not such value the return value is "to".
Time Complexity- O(n).
*/
sdll_iterator_t SDListFindIf(sdll_iterator_t from, sdll_iterator_t to, 
							 is_match_t is_match_function_ptr, void *param);

/*
Description- The SDListSMerge() function merges iterators from "to" to "from"
(excluding "to") into another list. The two lists must have the same sorting
function. The iterators [from, to) are removed from their original list.
Time Complexity- O(n+m). Where n is the number of elements in "slist" and m is
the number of elements between from and to (not including "to").
*/
void SDListSMerge(sdll_iterator_t from, sdll_iterator_t to, sdll_t *slist);


/*
Description- The SDListFind() function checks for "param" in every value in 
the list from the "from" iterator up to the "to" iterator (exclude the "to" 
iterator) using the sorting function of "slist".
Return Value- The function return the iterator which value is matched with 
"param", if there is not such value the return value is "to".
Time Complexity- O(n).
*/
sdll_iterator_t SDListFind(sdll_iterator_t from, sdll_iterator_t to, 
						   sdll_t *slist, void *param);

#endif /* __SORTED_LIST__ */
