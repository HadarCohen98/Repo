#include <stdio.h> /* printf */
#include <assert.h>

#include "include/sorted_list.h"
#include "../../utils/colors.h"

static sdll_t *TestCreate(void);
static int TestInsert(void);
static int TestRemove(void);
static int TestPopFront(void);
static int TestPopBack(void);
static int TestSize(void);
static int TestIsEmpty(void);
static int TestForEach(void);
static int TestFindIf(void);
static int TestFind(void);
static int TestMerge(void);


static int CmpInt(void *param, void *value);
static int AddToIter(void *param, void *value);
static int IntIsMatchFunc(void *param, void *value);

int main()
{
	size_t fail_counter = 0;
	
	(NULL != TestCreate()) ? 1 : (printf(RED "TestCreate failed\n" RESET), ++fail_counter);
	
	(0 != TestInsert()) ? 1 : (printf(RED "TestInsert failed\n" RESET), ++fail_counter);	
	
	(0 != TestRemove()) ? 1 : (printf(RED "TestRemove failed\n" RESET), ++fail_counter);	
	(0 != TestPopFront()) ? 1 : (printf(RED "TestPopFront failed\n" RESET), ++fail_counter); 
	(0 != TestPopBack()) ? 1 : (printf(RED "TestPopBack failed\n" RESET), ++fail_counter);	
	
	(0 != TestSize()) ? 1 : (printf(RED "TestSize failed\n" RESET), ++fail_counter);	
	(0 != TestIsEmpty()) ? 1 : (printf(RED "TestIsEmpty failed\n" RESET), ++fail_counter);	
	
	(0 != TestForEach()) ? 1 : (printf(RED "TestForEach failed\n" RESET), ++fail_counter);
	
	(0 != TestFindIf()) ? 1 : (printf(RED "TestFindIf failed\n" RESET), ++fail_counter);
	(0 != TestFind()) ? 1 : (printf(RED "TestFind failed\n" RESET), ++fail_counter);
	
	(0 != TestMerge()) ? 1 : (printf(RED "TestMerge failed\n" RESET), ++fail_counter);
	
	
	(0 == fail_counter) ? printf(YEL "All tests passed successfuly :)\n" RESET) : printf(RED ":(\n" RESET); 
	
	return 0;
}

static sdll_t *TestCreate(void)
{
	sdll_t *my_list = SDListCreate(CmpInt);
	sdll_t *temp = my_list;
	SDListDestroy(my_list);
	return temp;
}

static int TestInsert(void)
{
	int status = 0;
	sdll_t *my_list = SDListCreate(CmpInt);
	sdll_iterator_t iter = NULL;
	long a = 1;
	long b = 2;
	long d = 4;
	
	(1 != (long)SDListGetValue(SDListInsert(my_list, (void *)a))) ? printf("in line %d\n", __LINE__ - 2), ++status : 1;
	
	iter = SDListInsert(my_list, (void *)b);
	(2 != (long)SDListGetValue(iter)) ? printf("in line %d\n", __LINE__ - 2), ++status : 1;
	(1 != (long)SDListGetValue(SDListIteratorPrev(iter))) ? printf("in line %d\n", __LINE__ - 2), ++status : 1;
	
	iter = SDListInsert(my_list, (void *)d); 
	(4 != (long)SDListGetValue(iter)) ? printf("in line %d\n", __LINE__ - 2) : ++status;
	(2 != (long)SDListGetValue(SDListIteratorPrev(iter))) ? printf("in line %d\n", __LINE__ - 2), ++status : 1;

	SDListDestroy(my_list);
	return status;
}

static int TestRemove(void)
{
	int status = 0;
	sdll_t *my_list = SDListCreate(CmpInt);
	sdll_iterator_t iter = NULL;
	long a = 1;
	long b = 2;
	long c = 3;
	
	SDListInsert(my_list, (void *)a); 
	SDListInsert(my_list, (void *)b);
	SDListInsert(my_list, (void *)c); 
	
	iter = SDListIteratorPrev(SDListIteratorEnd(my_list));
	!(SDListIsIterEqual(SDListIteratorEnd(my_list), SDListRemove(iter))) ? printf("in line %d\n", __LINE__ - 2) : ++status;
	
	iter = SDListIteratorPrev(SDListIteratorEnd(my_list));
	!(SDListIsIterEqual(SDListIteratorEnd(my_list), SDListRemove(iter))) ? printf("in line %d\n", __LINE__ - 2) : ++status; 
	
	SDListDestroy(my_list);
	return status;
}

static int TestPopFront(void)
{
	int status = 0;
	sdll_t *my_list = SDListCreate(CmpInt);
	long a = 1;
	long b = 2;
	long c = 3;
	
	SDListInsert(my_list, (void *)a);
	SDListInsert(my_list, (void *)b); 
	SDListInsert(my_list, (void *)c); 
	
	(1 != (long)SDListPopFront(my_list)) ? printf("in line %d\n", __LINE__ - 2) : ++status;
	(2 != (long)SDListPopFront(my_list)) ? printf("in line %d\n", __LINE__ - 2) : ++status;
	(3 != (long)SDListPopFront(my_list)) ? printf("in line %d\n", __LINE__ - 2) : ++status;

	SDListDestroy(my_list);
	return status;
}

static int TestPopBack(void)
{
	int status = 0;
	sdll_t *my_list = SDListCreate(CmpInt);
	long a = 1;
	long b = 2;
	long c = 3;
	
	SDListInsert(my_list, (void *)a); 
	SDListInsert(my_list, (void *)b);
	SDListInsert(my_list, (void *)c);
	
	(3 != (long)SDListPopBack(my_list)) ? printf("in line %d\n", __LINE__ - 2) : ++status;
	(2 != (long)SDListPopBack(my_list)) ? printf("in line %d\n", __LINE__ - 2) : ++status;
	(1 != (long)SDListPopBack(my_list)) ? printf("in line %d\n", __LINE__ - 2) : ++status;

	SDListDestroy(my_list);
	return status;
}

static int TestSize(void)
{
	int status = 0;
	sdll_t *my_list = SDListCreate(CmpInt);
	long a = 1;
	long b = 2;
	
	(0 != SDListSize(my_list)) ? printf("in line %d\n", __LINE__ - 2) : ++status;
	
	SDListInsert(my_list, (void *)a);
	(1 != SDListSize(my_list)) ? printf("in line %d\n", __LINE__ - 2) : ++status;
	
	SDListInsert(my_list, (void *)b); 
	(2 != SDListSize(my_list)) ? printf("in line %d\n", __LINE__ - 2) : ++status;
	
	SDListPopBack(my_list); 
	(1 != SDListSize(my_list)) ? printf("in line %d\n", __LINE__ - 2) : ++status;
	
	SDListPopBack(my_list); 
	(0 != SDListSize(my_list))? printf("in line %d\n", __LINE__ - 2) : ++status;
	
	SDListDestroy(my_list);
	return status;
}

static int TestIsEmpty(void)
{
	int status = 0;
	sdll_t *my_list = SDListCreate(CmpInt);
	long a = 1;
	long b = 2;
	
	(1 != SDListIsEmpty(my_list)) ? printf("in line %d\n", __LINE__ - 2) : ++status;
	
	SDListInsert(my_list, (void *)a); 
	(0 != SDListIsEmpty(my_list)) ? printf("in line %d\n", __LINE__ - 2) : ++status;
	
	SDListInsert(my_list, (void *)b); 
	(0 != SDListIsEmpty(my_list)) ? printf("in line %d\n", __LINE__ - 2) : ++status;
	
	SDListPopBack(my_list); 
	(0 != SDListIsEmpty(my_list)) ? printf("in line %d\n", __LINE__ - 2) : ++status;
	
	SDListPopBack(my_list); 
	(1 != SDListIsEmpty(my_list)) ? printf("in line %d\n", __LINE__ - 2) : ++status;
	
	SDListDestroy(my_list);
	return status;
}

static int TestForEach(void)
{
	int status = 0;
	sdll_t *my_list = SDListCreate(CmpInt);
	long a = 1;
	long b = 2;
	long c = 3;
	long d = 4;
	
	SDListInsert(my_list, (void *)a); 
	SDListInsert(my_list, (void *)b); 
	SDListInsert(my_list, (void *)c); 
	
	
	(1 != SDListForEach(SDListIteratorFirst(my_list), SDListIteratorEnd(my_list), AddToIter, (void *)d)) ? printf(RED "TestForEach failed in line %d," RESET, __LINE__ - 2) : ++status;
	
	SDListDestroy(my_list);
	return status;
}

static int TestFindIf(void)
{
	int status = 0;
	sdll_t *my_list = SDListCreate(CmpInt);
	sdll_iterator_t iter = NULL;
	long a = 1;
	long b = 2;
	long c = 3;
	long d = 4;
	
	SDListInsert(my_list, (void *)a); 
	SDListInsert(my_list, (void *)b); 
	SDListInsert(my_list, (void *)c); 
	SDListInsert(my_list, (void *)a); 
	
	iter = SDListFindIf(SDListIteratorFirst(my_list), SDListIteratorEnd(my_list), IntIsMatchFunc, (void *)b);
	(2 != (long)SDListGetValue(iter)) ? printf(RED "TestFindIf failed in line %d\n" RESET, __LINE__ ) : ++status;
	
	iter = SDListFindIf(SDListIteratorFirst(my_list), SDListIteratorEnd(my_list), IntIsMatchFunc, (void *)d);
	!(SDListIsIterEqual(SDListIteratorEnd(my_list), iter)) ? printf(RED "TestFindIf failed in line %d\n" RESET, __LINE__ ) : ++status;
	
	SDListDestroy(my_list);
	return status;
}

static int TestFind(void)
{
	int status = 0;
	sdll_t *my_list = SDListCreate(CmpInt);
	sdll_iterator_t iter = NULL;
	long a = 1;
	long b = 2;
	long c = 3;
	long d = 4;
	
	SDListInsert(my_list, (void *)a); 
	SDListInsert(my_list, (void *)b); 
	SDListInsert(my_list, (void *)c); 
	SDListInsert(my_list, (void *)a); 
	
	iter = SDListFind(SDListIteratorFirst(my_list), SDListIteratorEnd(my_list), my_list, (void *)d);
	!(SDListIsIterEqual(SDListIteratorEnd(my_list), iter))? printf(RED "TestFind failed in line %d\n" RESET, __LINE__ ) : ++status;
	
	iter = SDListFind(SDListIteratorFirst(my_list), SDListIteratorEnd(my_list), my_list, (void *)a);
	!(SDListIsIterEqual(SDListIteratorFirst(my_list), iter)) ? printf(RED "TestFind failed in line %d\n" RESET, __LINE__ ) : ++status;

	SDListDestroy(my_list);
	return status;
}

static int TestMerge(void)
{
	int status = 0;
	sdll_t *list_1 = SDListCreate(CmpInt);
	sdll_t *list_2 = SDListCreate(CmpInt);
	long a = 1;
	long b = 2;
	long c = 3;
	long d = 4;
	
	SDListInsert(list_1, (void *)a); 
	SDListInsert(list_1, (void *)b); 
	SDListInsert(list_1, (void *)c); 
	SDListInsert(list_1, (void *)d); 
	
	SDListInsert(list_2, (void *)a); 
	SDListInsert(list_2, (void *)b); 
	
	SDListSMerge(SDListIteratorFirst(list_2), SDListIteratorEnd(list_2), list_1);
	
	(6 != SDListSize(list_1)) ? printf("in line %d\n", __LINE__) : ++status;
	(0 != SDListSize(list_2)) ? printf("in line %d\n", __LINE__) : ++status; 
	(1 != (long)SDListPopFront(list_1)) ? printf("in line %d\n", __LINE__) : ++status;
	(1 != (long)SDListPopFront(list_1)) ? printf("in line %d\n", __LINE__) : ++status;
	(2 != (long)SDListPopFront(list_1)) ? printf("in line %d\n", __LINE__) : ++status;
	(2 != (long)SDListPopFront(list_1)) ? printf("in line %d\n", __LINE__) : ++status;
	(3 != (long)SDListPopFront(list_1)) ? printf("in line %d\n", __LINE__) : ++status;
	(4 != (long)SDListPopFront(list_1)) ? printf("in line %d\n", __LINE__) : ++status;
	
	SDListDestroy(list_1);
	SDListDestroy(list_2);
	return status;
}

static int CmpInt(void *param, void *value)
{
	assert(param);
	assert(value);
	return ((long)param - (long)value);
}

static int AddToIter(void *param, void *value)
{
	int counter = 0;	
	++counter;
	(void)param;
	(void)value;
	return counter;
}


static int IntIsMatchFunc(void *param, void *value)
{
	return ((long)value == (long)param);
}
