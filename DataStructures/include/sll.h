/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       1.0                                             *
 ~ Date          04/12/22                                        ~
 ~ Description   Singly Linked List Header                       ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#ifndef __SINGLY_LINKED_LIST__
#define __SINGLY_LINKED_LIST__

#include <stddef.h>

typedef struct sll sll_t;
typedef struct sll_node *iterator_t;
typedef int (*is_match_t)(void *param, void *value);
typedef int (*action_t)(void *param, void *value);

/*
NOTE-
If the user wants to save the values (and not pointers to the values) he needs 
to pass the value in (void *) casting (and not the adresses). 
*/

/*
Description- The SListCreate() function creates a new sll_t type.
Return Value- The function returns a pointer to the new sll_t, in the case 
of failure the returned pointer will be NULL
Time complexity- O(1).
*/
sll_t *SListCreate(void);

/*
Description- The SListInsert() function inserts a new value to the list 
before the position mentioned.
Return Value- The function returns a pointer to the new iterator.
Notes- 
The function uses malloc but fails safly, i.e if the malloc function fails 
the SListInsert function returns the position mentioned, in the case 
of failure the returned pointer will be NULL.
Time complexity- O(1).
*/
iterator_t SListInsert(iterator_t position, void *value);

/*
Description- The SListGetValue() function gets the value of the position 
mentioned.
Return Value- The function returns the value in void pointer type.
Time complexity- O(1).
*/
void *SListGetValue(iterator_t position);

/*
Description- The SListSetValue() function sets the value of the position 
mentioned.
Time complexity- O(1).
*/
void SListSetValue(iterator_t position, void *value);

/*
Description- The SListRemove() function removes the position mentioned 
from the list.
Return Value- The function returns a pointer to the next iterator after 
the removal. When the last iterator removed the return value will be the 
address to the empty list.
Notes-
If the list is empty the SListRemove() function will lead to undefined 
behvior.
Time complexity- O(1).
*/
iterator_t SListRemove(iterator_t position_to_remove);

/*
Description- The SListIteratorNext() function returns the the next 
iterator after position in the list.
Return Value- The function returns a pointer to the next iterator.
Time complexity- O(1).
*/
iterator_t SListIteratorNext(iterator_t position);

/*
Description- The SListIteratorEnd() function returns the the last iterator 
in the list (exclude the dummy iterator that points to NULL).
Return Value- The function returns a pointer to the last iterator.
Time complexity- O(1).
*/
iterator_t SListIteratorEnd(const sll_t *list);

/*
Description- The SListIteratorFirst() function returns the the head 
iterator which is the first iterator in the list.
Return Value- The function returns a pointer to the first iterator.
Time complexity- O(1).
*/
iterator_t SListIteratorFirst(const sll_t *list);

/*
Description- The IsItrEqual() function checks for equality between two 
iterators.
Return Value- The function returns 1 if the iterators are equal and 0 if 
not.
Time complexity- O(1).
*/
int IsItrEqual(iterator_t iterator1, iterator_t iterator2);

/*
Description- The SListForEach() function operates the action_function_ptr 
on every value on the list from the "from" iterator up to the "to" 
iterator (exclude the "to" iterator) base on the parameter mentioned.
Return Value- The function returns the return status of the 
action_function_ptr.
Time complexity- O(n).
*/
int SListForEach(iterator_t from, iterator_t to, action_t action_function_ptr, void *param);

/*
Description- The SListSize() function returns the number of values in the 
list.
Return Value- The function returns the size of the list in size_t type.
Time complexity- O(n).
*/
size_t SListSize(const sll_t *list);

/*
Description- The SListIsEmpty() function checks if the list is empty.
Return Value- The function returns 1 if the list is empty and 0 otherwise.
Time complexity- O(1).
*/
int SListIsEmpty(const sll_t *list);

/*
Description- The SListDestroy() function frees every element in the list 
and the list itself.
Time complexity- O(n).
*/
void SListDestroy(sll_t *list);

/*
Description- The SListFind() function checks for "param" in every value on 
the list from the "from" iterator up to the "to" iterator (exclude the 
"to" iterator) using the cmp_function_ptr.
Return Value- The function returns the iterator which value is matched 
with "param", if there is not value matched the return value is "to" 
operator.
Time complexity- O(n).
*/
iterator_t SListFind(iterator_t from, iterator_t to, is_match_t is_match_function_ptr, void *param);

/*
Description- The SListAppendSList() function connect the src list to the 
end of dest. At the end of the function the src list is empty.
*/
void SListAppendSList(sll_t *dest, sll_t *src);

#endif /* __Singly_Linked_List__ */
