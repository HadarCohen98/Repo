#include <stdio.h> /* printf */
#include <assert.h> /* assert */

#include "../../utils/colors.h"
#include "include/priority_queue.h"	

static int Priority(void *param, void *value);
static int IntIsMatchFunc(void *param, void *value);

priority_queue_t *TestCreate(void);
int TestEnqueue(void);
int TestDequeue(void);
int TestSize(void);
int TestIsEmpty(void);
int TestClear(void);
int TestErase(void);


int main()
{
	size_t fail_counter = 0;
	
	(NULL != TestCreate()) ? 1 : ++fail_counter;
	(0 == TestEnqueue()) ? 1 : ++fail_counter;
	(0 == TestDequeue()) ? 1 : ++fail_counter;
	(0 == TestSize()) ? 1 : ++fail_counter;
	(0 == TestIsEmpty()) ? 1 : ++fail_counter;
	(0 == TestClear()) ? 1 : ++fail_counter;
	(0 == TestErase()) ? 1 : ++fail_counter;
	

	(0 == fail_counter) ? printf(YEL "All tests passed successfuly :)\n" RESET) : printf(RED ":(\n" RESET); 
	return 0;
}


priority_queue_t *TestCreate(void)
{
	priority_queue_t *my_pqueue = PQCreate(Priority);
	priority_queue_t *temp = my_pqueue;
	SDListDestroy(my_pqueue);
	return temp;
}

int TestEnqueue(void)
{
	int status = 0;
	priority_queue_t *my_pqueue = PQCreate(Priority);
	long a = 1;
	long b = 5;
	long c = 10;
	long d = 4;
	
	(0 == PQEnqueue(my_pqueue, (void *)b)) ? 1 : (printf(RED "TestEnqueue failed in line %d\n" RESET, __LINE__ ), ++status);
	(0 == PQEnqueue(my_pqueue, (void *)a)) ? 1 : (printf(RED "TestEnqueue failed in line %d\n" RESET, __LINE__ ), ++status);
	(0 == PQEnqueue(my_pqueue, (void *)c)) ? 1 : (printf(RED "TestEnqueue failed in line %d\n" RESET, __LINE__ ), ++status);
	(0 == PQEnqueue(my_pqueue, (void *)d)) ? 1 : (printf(RED "TestEnqueue failed in line %d\n" RESET, __LINE__ ), ++status);
	
	(a == (long)PQPeek(my_pqueue)) ? 1 : (printf(RED "TestEnqueue failed in line %d\n" RESET, __LINE__ ), ++status);
	
	SDListDestroy(my_pqueue);
	return status;
}

int TestDequeue(void)
{
	int status = 0;
	priority_queue_t *my_pqueue = PQCreate(Priority);
	long a = 1;
	long b = 5;
	long c = 10;
	long d = 4;
	
	PQEnqueue(my_pqueue, (void *)a);
	PQEnqueue(my_pqueue, (void *)b);
	PQEnqueue(my_pqueue, (void *)c);
	PQEnqueue(my_pqueue, (void *)d);
	
	(a == (long)PQDequeue(my_pqueue)) ? 1 : (printf(RED "TestDequeue failed in line %d\n" RESET, __LINE__ ), ++status);
	(d == (long)PQDequeue(my_pqueue)) ? 1 : (printf(RED "TestDequeue failed in line %d\n" RESET, __LINE__ ), ++status);
	(b == (long)PQDequeue(my_pqueue)) ? 1 : (printf(RED "TestDequeue failed in line %d\n" RESET, __LINE__ ), ++status);
	(c == (long)PQDequeue(my_pqueue)) ? 1 : (printf(RED "TestDequeue failed in line %d\n" RESET, __LINE__ ), ++status);
	
	SDListDestroy(my_pqueue);
	return status;
}

int TestSize(void)
{
	int status = 0;
	priority_queue_t *my_pqueue = PQCreate(Priority);
	long a = 1;
	long b = 5;
	long c = 10;
	
	(0 == PQSize(my_pqueue)) ? 1 : (printf(RED "TestSize failed in line %d\n" RESET, __LINE__ ), ++status);
	
	PQEnqueue(my_pqueue, (void *)a);
	(1 == PQSize(my_pqueue)) ? 1 : (printf(RED "TestSize failed in line %d\n" RESET, __LINE__ ), ++status);
	
	PQEnqueue(my_pqueue, (void *)b);
	(2 == PQSize(my_pqueue)) ? 1 : (printf(RED "TestSize failed in line %d\n" RESET, __LINE__ ), ++status);
	
	PQDequeue(my_pqueue);
	(1 == PQSize(my_pqueue)) ? 1 : (printf(RED "TestSize failed in line %d\n" RESET, __LINE__ ), ++status);	
	
	PQEnqueue(my_pqueue, (void *)c);
	(2 == PQSize(my_pqueue)) ? 1 : (printf(RED "TestSize failed in line %d\n" RESET, __LINE__ ), ++status);		
	
	PQDequeue(my_pqueue);
	(1 == PQSize(my_pqueue)) ? 1 : (printf(RED "TestSize failed in line %d\n" RESET, __LINE__ ), ++status);	
	
	PQDequeue(my_pqueue);
	(0 == PQSize(my_pqueue)) ? 1 : (printf(RED "TestSize failed in line %d\n" RESET, __LINE__ ), ++status);
	
	SDListDestroy(my_pqueue);
	return status;
}

int TestIsEmpty(void)
{
	int status = 0;
	priority_queue_t *my_pqueue = PQCreate(Priority);
	long a = 1;
	long b = 5;
		
	(1 == PQIsEmpty(my_pqueue)) ? 1 : (printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ ), ++status);
	
	PQEnqueue(my_pqueue, (void *)a);
	(0 == PQIsEmpty(my_pqueue)) ? 1 : (printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ ), ++status);
	
	PQEnqueue(my_pqueue, (void *)b);
	(0 == PQIsEmpty(my_pqueue)) ? 1 : (printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ ), ++status);
	
	PQDequeue(my_pqueue);
	(0 == PQIsEmpty(my_pqueue)) ? 1 : (printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ ), ++status);	
	
	PQDequeue(my_pqueue);
	(1 == PQIsEmpty(my_pqueue)) ? 1 : (printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ ), ++status);	
	
	SDListDestroy(my_pqueue);
	return status;
}

int TestClear(void)
{
	int status = 0;
	priority_queue_t *my_pqueue = PQCreate(Priority);
	long a = 1;
	long b = 5;
	long c = 10;
	long d = 4;
	
	PQEnqueue(my_pqueue, (void *)a);
	PQEnqueue(my_pqueue, (void *)b);
	PQEnqueue(my_pqueue, (void *)c);
	PQEnqueue(my_pqueue, (void *)d);
	
	(0 == PQIsEmpty(my_pqueue)) ? 1 : (printf(RED "TestClear failed in line %d\n" RESET, __LINE__ ), ++status);
	
	PQClear(my_pqueue);
	(1 == PQIsEmpty(my_pqueue)) ? 1 : (printf(RED "TestClear failed in line %d\n" RESET, __LINE__ ), ++status); 
	
	SDListDestroy(my_pqueue);
	return status;
}

int TestErase(void)
{
	int status = 0;
	priority_queue_t *my_pqueue = PQCreate(Priority);
	long a = 1;
	long b = 5;
	long c = 10;
	long d = 4;
	
	PQEnqueue(my_pqueue, (void *)a);
	PQEnqueue(my_pqueue, (void *)b);
	PQEnqueue(my_pqueue, (void *)c);
	PQEnqueue(my_pqueue, (void *)d);
	
	(4 == PQSize(my_pqueue)) ? 1 : (printf(RED "TestErase failed in line %d\n" RESET, __LINE__ ), ++status);

	PQErase(my_pqueue, IntIsMatchFunc, (void *)b);
	(3 == PQSize(my_pqueue)) ? 1 : (printf(RED "TestErase failed in line %d\n" RESET, __LINE__ ), ++status);
	
	(a == (long)PQPeek(my_pqueue)) ? 1 : (printf(RED "TestErase failed in line %d\n" RESET, __LINE__ ), ++status);
	PQDequeue(my_pqueue);
	
	(d == (long)PQPeek(my_pqueue)) ? 1 : (printf(RED "TestErase failed in line %d\n" RESET, __LINE__ ), ++status);
	PQDequeue(my_pqueue);
	
	(c == (long)PQPeek(my_pqueue)) ? 1 : (printf(RED "TestErase failed in line %d\n" RESET, __LINE__ ), ++status);
	PQDequeue(my_pqueue);
	
	SDListDestroy(my_pqueue);
	return status;
}

static int Priority(void *param, void *value)
{
	assert(param);
	assert(value);
	return ((long)param - (long)value);
}

static int IntIsMatchFunc(void *param, void *value)
{
	return ((long)value == (long)param);
}
