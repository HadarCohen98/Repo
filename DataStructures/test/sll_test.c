#include <stdio.h> /* printf */

#include "include/sll.h"

static int PrintIter(void *param, void *value);
static int IntCmpFunc(void *param, void *value);

int main()
{
	long x = 3;
	long y = 666;
	long z = -90;
	long a = 5;
	
	iterator_t first_iter = NULL;
	iterator_t second_iter = NULL;
	iterator_t third_iter = NULL;
	iterator_t fourth_iter = NULL;
	iterator_t after_remove = NULL;
	iterator_t after_remove1 = NULL;
	iterator_t is_iter_find = NULL;
	 
	sll_t *my_list = SListCreate();
	printf("is empty? %d\n", SListIsEmpty(my_list));
	printf("the size is- %lu\n", SListSize(my_list));

	printf("\n---------first insertion---------\n");
	printf("---------before End---------\n");
	first_iter = SListInsert(SListIteratorEnd(my_list), (void *)x);
	printf("the new element is- %ld\n", (long)SListGetValue(first_iter));
	printf("is empty? %d\n", SListIsEmpty(my_list));
	printf("the size is- %lu\n", SListSize(my_list));
	
	x = 5;
	printf("x changed, does iter changes as well?- %ld\n", (long)SListGetValue(first_iter));
	printf("\n---------second insertion---------\n");
	printf("---------after First, before End---------\n");
	second_iter = SListInsert(SListIteratorEnd(my_list), (void *)y);
	printf("the new element is- %ld\n", (long)SListGetValue(second_iter));
	printf("is empty? %d\n", SListIsEmpty(my_list));
	printf("the size is- %lu\n", SListSize(my_list));
	
	printf("\n---------third insertion---------\n");
	printf("---------after First, before Second---------\n");
	third_iter = SListInsert(second_iter, (void *)z);
	printf("the new element is- %ld\n", (long)SListGetValue(third_iter));
	printf("is empty? %d\n", SListIsEmpty(my_list));
	printf("the size is- %lu\n", SListSize(my_list));
	
	printf("\n---------remove second (third insertion)---------\n");
	after_remove = SListRemove(third_iter);
	printf("after remove- %ld\n", (long)SListGetValue(after_remove));
	printf("is empty? %d\n", SListIsEmpty(my_list));
	printf("the size is- %lu\n", SListSize(my_list));
	
	printf("\n---------fourth insertion---------\n");
	printf("---------before End---------\n");
	fourth_iter = SListInsert(SListIteratorEnd(my_list), (void *)a);
	printf("the new element is- %ld\n", (long)SListGetValue(fourth_iter));
	printf("is empty? %d\n", SListIsEmpty(my_list));
	printf("the size is- %lu\n", SListSize(my_list));
	
	printf("\n---------for each test (print list)---------\n");
	SListForEach(SListIteratorFirst(my_list), SListIteratorEnd(my_list), PrintIter, 0);
	
	printf("\n---------find test---------\n");
	is_iter_find = SListFind(SListIteratorFirst(my_list), SListIteratorEnd(my_list), IntCmpFunc, (void *)z);
	if (NULL != SListIteratorNext(is_iter_find))
	{
		printf("is iter find- %ld\n", (long)SListGetValue(is_iter_find));
	}
	else
	{
		printf("value not found\n");
	}
	
	is_iter_find = SListFind(SListIteratorFirst(my_list), SListIteratorEnd(my_list), IntCmpFunc, (void *)y);
	if (NULL != SListIteratorNext(is_iter_find))
	{
		printf("is iter find- %ld\n", (long)SListGetValue(is_iter_find));
	}
	else
	{
		printf("value not found\n");
	}
	
	printf("\n---------remove 666---------\n");
	after_remove1 = SListRemove(second_iter);
	printf("after remove- %ld\n", (long)SListGetValue(after_remove1));
	printf("is empty? %d\n", SListIsEmpty(my_list));
	printf("the size is- %lu\n", SListSize(my_list));

	printf("\n---------for each test (print list)---------\n");
	SListForEach(SListIteratorFirst(my_list), SListIteratorEnd(my_list), PrintIter, 0);
	SListDestroy(my_list);
	printf(":)\n");
	return 0;
}


static int PrintIter(void *param, void *value)
{
	printf("%lu\n", (long)value);
	(void)param;
	return 0;
}

static int IntCmpFunc(void *param, void *value)
{
	return ((long)value == (long)param);
}
	 
