
#include <stdio.h> /* printf */

#define RED  "\x1B[31m"
#define YEL  "\x1B[33m"
#define RESET "\x1B[0m"

#include "../include/dll.h"

static int PrintIter(void *param, void *value);
static int IntIsMatchFunc(void *param, void *value);

static dll_t *TestCreate()
{
	dll_t *my_list = DListCreate();
	dll_t *temp = my_list;
	DListDestroy(my_list);
	return temp;
}

static int TestInsertBefore()
{
	int status = 0;
	dll_t *my_list = DListCreate();
	dll_iterator_t iter = NULL;
	long a = 1;
	long b = 2;
	long c = 3;
	long d = 4;
	
	status += (1 != (long)DListGetValue(DListInsertBefore(DListIteratorEnd(my_list), (void *)a))); /* 1 */
	
	iter = DListInsertBefore(DListIteratorEnd(my_list), (void *)b); /* 1, 2 */
	status += (2 != (long)DListGetValue(iter));
	status += (1 != (long)DListGetValue(DListIteratorPrev(iter)));
	
	iter = DListInsertBefore(DListIteratorEnd(my_list), (void *)c); /* 1, 2, 3 */
	status += (3 != (long)DListGetValue(iter)); 
	status += (2 != (long)DListGetValue(DListIteratorPrev(iter)));


	iter = DListInsertBefore(DListIteratorNext(DListIteratorFirst(my_list)), (void *)d);
	status += (4 != (long)DListGetValue(iter)); /* 1, 4, 2, 3 */
	status += (1 != (long)DListGetValue(DListIteratorPrev(iter)));
	
	DListDestroy(my_list);
	return status;
}

static int TestPushFront()
{
	int status = 0;
	dll_t *my_list = DListCreate();
	dll_iterator_t iter = NULL;
	long a = 1;
	long b = 2;
	long c = 3;
	
	status += (1 != (long)DListGetValue(DListPushFront(my_list, (void *)a))); /* 1 */ 
	
	iter = DListPushFront(my_list, (void *)b); /* 2 1 */
	status += (2 != (long)DListGetValue(iter));
	status += (1 != (long)DListGetValue(DListIteratorNext(iter)));
	
	iter = DListPushFront(my_list, (void *)c); /* 3 2 1 */
	status += (3 != (long)DListGetValue(iter));
	status += (2 != (long)DListGetValue(DListIteratorNext(iter)));

	DListDestroy(my_list);
	return status;
}

static int TestPushBack()
{
	int status = 0;
	dll_t *my_list = DListCreate();
	dll_iterator_t iter = NULL;
	long a = 1;
	long b = 2;
	long c = 3;
	
	status += (1 != (long)DListGetValue(DListPushBack(my_list, (void *)a))); /* 1 */ 
	
	iter = DListPushBack(my_list, (void *)b); /* 1 2 */
	status += (2 != (long)DListGetValue(iter));
	status += (1 != (long)DListGetValue(DListIteratorPrev(iter)));
	
	iter = DListPushBack(my_list, (void *)c); /* 1 2 3 */
	status += (3 != (long)DListGetValue(iter));
	status += (2 != (long)DListGetValue(DListIteratorPrev(iter)));

	DListDestroy(my_list);
	return status;
}

static int TestSetValue()
{
	int status = 0;
	dll_t *my_list = DListCreate();
	long a = 1;
	long b = 2;
	
	DListInsertBefore(DListIteratorEnd(my_list), (void *)a);
	
	DListSetValue(DListIteratorEnd(my_list), (void *)b); 
	status += (2 != (long)DListGetValue(DListIteratorEnd(my_list))); 
	
	DListDestroy(my_list);
	return status;
}

static int TestRemove()
{
	int status = 0;
	dll_t *my_list = DListCreate();
	dll_iterator_t iter = NULL;
	long a = 1;
	long b = 2;
	long c = 3;
	
	DListInsertBefore(DListIteratorEnd(my_list), (void *)a); /* 1 */
	DListInsertBefore(DListIteratorEnd(my_list), (void *)b); /* 1, 2 */
	DListInsertBefore(DListIteratorEnd(my_list), (void *)c); /* 1, 2, 3 */
	
	iter = DListIteratorNext(DListIteratorFirst(my_list));
	status += !(DListIsIterEqual(DListIteratorPrev(DListIteratorEnd(my_list)), DListRemove(iter))); /* 1, 3 */
	
	iter = DListIteratorPrev(DListIteratorEnd(my_list));
	status += !(DListIsIterEqual(DListIteratorEnd(my_list), DListRemove(iter))); /* 1 */
	
	iter = DListIteratorPrev(DListIteratorEnd(my_list));
	status += !(DListIsIterEqual(DListIteratorEnd(my_list), DListRemove(iter))); /* */ 
	
	
	DListDestroy(my_list);
	return status;
}

static int TestPopFront()
{
	int status = 0;
	dll_t *my_list = DListCreate();
	long a = 1;
	long b = 2;
	long c = 3;
	
	DListPushFront(my_list, (void *)a); /* 1 */ 
	DListPushFront(my_list, (void *)b); /* 2 1 */
	DListPushFront(my_list, (void *)c); /* 3 2 1 */
	
	status += (3 != (long)DListPopFront(my_list)); 
	status += (2 != (long)DListPopFront(my_list));
	status += (1 != (long)DListPopFront(my_list));

	DListDestroy(my_list);
	return status;
}

static int TestPopBack()
{
	int status = 0;
	dll_t *my_list = DListCreate();
	long a = 1;
	long b = 2;
	long c = 3;
	
	DListPushFront(my_list, (void *)a); /* 1 */ 
	DListPushFront(my_list, (void *)b); /* 2 1 */
	DListPushFront(my_list, (void *)c); /* 3 2 1 */
	
	status += (1 != (long)DListPopBack(my_list));
	status += (2 != (long)DListPopBack(my_list));
	status += (3 != (long)DListPopBack(my_list));

	DListDestroy(my_list);
	return status;
}

static int TestSize()
{
	int status = 0;
	dll_t *my_list = DListCreate();
	long a = 1;
	long b = 2;
	
	status += (0 != DListSize(my_list));
	
	DListPushFront(my_list, (void *)a); /* 1 */ 
	status += (1 != DListSize(my_list));
	
	DListPushFront(my_list, (void *)b); /* 2 1 */
	status += (2 != DListSize(my_list));
	
	DListPopBack(my_list); /* 2 */
	status += (1 != DListSize(my_list));
	
	DListPopBack(my_list); /*  */
	status += (0 != DListSize(my_list));
	
	DListDestroy(my_list);
	return status;
}

static int TestIsEmpty()
{
	int status = 0;
	dll_t *my_list = DListCreate();
	long a = 1;
	long b = 2;
	
	status += (1 != DListIsEmpty(my_list));
	
	DListPushFront(my_list, (void *)a); /* 1 */ 
	status += (0 != DListIsEmpty(my_list));
	
	DListPushFront(my_list, (void *)b); /* 2 1 */
	status += (0 != DListIsEmpty(my_list));
	
	DListPopBack(my_list); /* 2 */
	status += (0 != DListIsEmpty(my_list));
	
	DListPopBack(my_list); /*  */
	status += (1 != DListIsEmpty(my_list));
	
	DListDestroy(my_list);
	return status;
}

static void TestForEach()
{
	dll_t *my_list = DListCreate();
	long a = 1;
	long b = 2;
	long c = 3;
	long d = 4;
	
	DListInsertBefore(DListIteratorEnd(my_list), (void *)a); 
	DListInsertBefore(DListIteratorEnd(my_list), (void *)b);
	DListInsertBefore(DListIteratorEnd(my_list), (void *)c); 
	DListInsertBefore(DListIteratorNext(DListIteratorFirst(my_list)), (void *)d); 
	
	DListForEach(DListIteratorFirst(my_list), DListIteratorEnd(my_list), PrintIter, 0);

	DListDestroy(my_list);
}

static int TestFind()
{
	int status = 0;
	dll_t *my_list = DListCreate();
	dll_iterator_t iter = NULL;
	long a = 1;
	long b = 2;
	long c = 3;
	long d = 4;
	
	DListInsertBefore(DListIteratorEnd(my_list), (void *)a); 
	DListInsertBefore(DListIteratorEnd(my_list), (void *)b); 
	DListInsertBefore(DListIteratorEnd(my_list), (void *)c); 
	DListInsertBefore(DListIteratorEnd(my_list), (void *)a);  
	
	iter = DListFind(DListIteratorFirst(my_list), DListIteratorEnd(my_list), IntIsMatchFunc, (void *)a);
	status += (1 != (long)DListGetValue(iter));
	
	iter = DListFind(DListIteratorFirst(my_list), DListIteratorEnd(my_list), IntIsMatchFunc, (void *)d);
	status += !(DListIsIterEqual(DListIteratorEnd(my_list), iter));
	
	DListDestroy(my_list);
	return status;
}

static int TestMultiFind()
{
	int status = 0;
	dll_t *my_list = DListCreate();
	dll_t *result_list = DListCreate();
	long a = 1;
	long b = 2;
	long c = 3;
	long d = 4;
	
	DListInsertBefore(DListIteratorEnd(my_list), (void *)a); 
	DListInsertBefore(DListIteratorEnd(my_list), (void *)b); 
	DListInsertBefore(DListIteratorEnd(my_list), (void *)c); 
	DListInsertBefore(DListIteratorEnd(my_list), (void *)a);  /* 1 2 3 1 */
	
	status += (0 != DListMultifind(DListIteratorFirst(my_list), DListIteratorEnd(my_list), IntIsMatchFunc, result_list, (void *)d));
	status += (0 != DListSize(result_list));

	status += (2 != DListMultifind(DListIteratorFirst(my_list), DListIteratorEnd(my_list), IntIsMatchFunc, result_list, (void *)a));
	status += (2 != DListSize(result_list));
	status += (1 != (long)DListGetValue(DListIteratorFirst(result_list)));
	status += (1 != (long)DListGetValue(DListIteratorNext((DListIteratorFirst(result_list)))));
	
	DListDestroy(my_list);
	DListDestroy(result_list);
	return status;
}

static int TestSplice()
{
	int status = 0;
	dll_t *list_1 = DListCreate();
	dll_t *list_2 = DListCreate();
	dll_iterator_t position_to_insert = NULL;
	long a = 1;
	long b = 2;
	long c = 3;
	long d = 4;
	
	DListInsertBefore(DListIteratorEnd(list_1), (void *)a); 
	DListInsertBefore(DListIteratorEnd(list_1), (void *)b); 
	DListInsertBefore(DListIteratorEnd(list_1), (void *)c); 
	DListInsertBefore(DListIteratorEnd(list_1), (void *)d);  /* 1 2 3 4 */
	
	DListInsertBefore(DListIteratorEnd(list_2), (void *)a); 
	DListInsertBefore(DListIteratorEnd(list_2), (void *)b); /* 1 2 */
	
	position_to_insert =  DListIteratorNext(DListIteratorNext(DListIteratorFirst(list_1)));
	DListSplice(DListIteratorFirst(list_2), DListIteratorEnd(list_2), position_to_insert);
	
	status += (6 != DListSize(list_1)); 
	status += (0 != DListSize(list_2)); 
	
	DListDestroy(list_1);
	DListDestroy(list_2);
	return status;
}

int main()
{
	int counter = 0;
	int fail_counter = 0;
	
	(NULL != TestCreate()) ? ++counter : printf(RED "Test %d failed\n" RESET, ++counter) && ++fail_counter;
	
	(0 == TestInsertBefore()) ? ++counter : printf(RED "Test %d failed\n" RESET, ++counter) && ++fail_counter;	
	(0 == TestPushFront()) ? ++counter : printf(RED "Test %d failed\n" RESET, ++counter) && ++fail_counter;	
	(0 == TestPushBack()) ? ++counter : printf(RED "Test %d failed\n" RESET, ++counter) && ++fail_counter;	
	
	(0 == TestSetValue()) ? ++counter : printf(RED "Test %d failed\n" RESET, ++counter) && ++fail_counter;	
	
	(0 == TestRemove()) ? ++counter : printf(RED "Test %d failed\n" RESET, ++counter) && ++fail_counter;	
	(0 == TestPopFront()) ? ++counter : printf(RED "Test %d failed\n" RESET, ++counter) && ++fail_counter; 
	(0 == TestPopBack()) ? ++counter : printf(RED "Test %d failed\n" RESET, ++counter) && ++fail_counter;	
	
	(0 == TestSize()) ? ++counter : printf(RED "Test %d failed\n" RESET, ++counter) && ++fail_counter;	
	(0 == TestIsEmpty()) ? ++counter : printf(RED "Test %d failed\n" RESET, ++counter) && ++fail_counter;	
	
	(0 == TestFind()) ? ++counter : printf(RED "Test %d failed\n" RESET, ++counter) && ++fail_counter;
	(0 == TestMultiFind()) ? ++counter : printf(RED "Test %d failed\n" RESET, ++counter) && ++fail_counter;	
	
	(0 == TestSplice()) ? ++counter : printf(RED "Test %d failed\n" RESET, ++counter) && ++fail_counter;
	
	
	(0 == fail_counter) ? printf(YEL "All tests passed successfuly :)\n" RESET) : printf(RED ":(\n" RESET); 
	
	printf("TestForEach- print the list (1, 4, 2, 3)-\n");
	TestForEach();

	return 0;
}

static int PrintIter(void *param, void *value)
{
	printf("%lu\n", (long)value);
	(void)param;
	return 0;
}

static int IntIsMatchFunc(void *param, void *value)
{
	return ((long)value == (long)param);
}
