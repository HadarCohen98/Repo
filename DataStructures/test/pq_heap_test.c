
#include <stdio.h> /* printf */
#include <assert.h> /* assert */

#include "../../utils/colors.h"
#include "include/pq_heap.h"	

static int Priority(const void *a, const void *b);
static int IntIsMatchFunc(const void *param, const void *value);

int TestCreateAndDestroy(void);
int TestEnqueue(void);
int TestDequeue(void);
int TestSizeAndIsEmpty(void);
int TestClear(void);
int TestErase(void);


int main()
{
	size_t fail_counter = 0;
	
	(0 == TestCreateAndDestroy()) ? 1 : ++fail_counter;
	(0 == TestEnqueue()) ? 1 : ++fail_counter;
	(0 == TestDequeue()) ? 1 : ++fail_counter;
	(0 == TestSizeAndIsEmpty()) ? 1 : ++fail_counter;
	(0 == TestClear()) ? 1 : ++fail_counter;
	(0 == TestErase()) ? 1 : ++fail_counter;
	

	(0 == fail_counter) ? printf(YEL "All tests passed successfuly :)\n" RESET) : printf(RED ":(\n" RESET); 
	return 0;
}


int TestCreateAndDestroy(void)
{
	int status = 0;
	pq_heap_t *pq_heap = PQHeapCreate(Priority);
	if (NULL == pq_heap)
	{
		printf(RED "TestCreateAndDestroy failed in line %d\n" RESET, 
		__LINE__ );
		printf(RED "HeapCreate returns NULL\n" RESET); 
		++status;
	} 
	
	printf("DO NOT FORGET TO CHECK VLG\n");
	
	PQHeapDestroy(pq_heap); pq_heap = NULL;
	return status;	
}

int TestEnqueue(void)
{
	int status = 0;
	pq_heap_t *pq_heap = PQHeapCreate(Priority);
	long a = 1;
	long b = 5;
	long c = 10;
	long d = 4;
	
	if (0 != PQHeapEnqueue(pq_heap, &b))
	{
		printf(RED "TestEnqueue failed in line %d\n" RESET, __LINE__ );
		++status;
	} 

	if (5 != *(long*)PQHeapPeek(pq_heap))
	{
		printf(RED "TestEnqueue failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 5, actual value- %ld\n" RESET, *(long*)PQHeapPeek(pq_heap));
		++status;
	}

	if (0 != PQHeapEnqueue(pq_heap, &a))
	{
		printf(RED "TestEnqueue failed in line %d\n" RESET, __LINE__ );
		++status;
	} 

	if (5 != *(long*)PQHeapPeek(pq_heap))
	{
		printf(RED "TestEnqueue failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 5, actual value- %ld\n" RESET, *(long*)PQHeapPeek(pq_heap));
		++status;
	}

	if (0 != PQHeapEnqueue(pq_heap, &c))
	{
		printf(RED "TestEnqueue failed in line %d\n" RESET, __LINE__ );
		++status;
	} 

	if (10 != *(long*)PQHeapPeek(pq_heap))
	{
		printf(RED "TestEnqueue failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 10, actual value- %ld\n" RESET, *(long*)PQHeapPeek(pq_heap));
		++status;
	}

	if (0 != PQHeapEnqueue(pq_heap, &d))
	{
		printf(RED "TestEnqueue failed in line %d\n" RESET, __LINE__ );
		++status;
	} 

	if (10 != *(long*)PQHeapPeek(pq_heap))
	{
		printf(RED "TestEnqueue failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 10, actual value- %ld\n" RESET, *(long*)PQHeapPeek(pq_heap));
		++status;
	}

	PQHeapDestroy(pq_heap); pq_heap = NULL;
	return status;
}

int TestDequeue(void)
{
	int status = 0;
	pq_heap_t *pq_heap = PQHeapCreate(Priority);
	long a = 1;
	long b = 5;
	long c = 10;
	long d = 4;
	long removed_data = 0;
	
	PQHeapEnqueue(pq_heap, &b);
	PQHeapEnqueue(pq_heap, &a);
	PQHeapEnqueue(pq_heap, &c);
	PQHeapEnqueue(pq_heap, &d);

	removed_data = *(long *)PQHeapDequeue(pq_heap);
	if (10 != removed_data)
	{
		printf(RED "TestDequeue failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 10, actual value- %ld\n" RESET, removed_data);
		++status;
	}
	
	if (5 != *(long *)PQHeapPeek(pq_heap))
	{
		printf(RED "TestDequeue failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 5, actual value- %ld\n" RESET,  *(long *)PQHeapPeek(pq_heap));
		++status;
	}

	removed_data = *(long *)PQHeapDequeue(pq_heap);
	if (5 != removed_data)
	{
		printf(RED "TestDequeue failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 5, actual value- %ld\n" RESET, removed_data);
		++status;
	}

	if (4 != *(long *)PQHeapPeek(pq_heap))
	{
		printf(RED "TestDequeue failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 4, actual value- %ld\n" RESET,  *(long *)PQHeapPeek(pq_heap));
		++status;
	}

	removed_data = *(long *)PQHeapDequeue(pq_heap);
	if (4 != removed_data)
	{
		printf(RED "TestDequeue failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 4, actual value- %ld\n" RESET, removed_data);
		++status;
	}

	if (1 != *(long *)PQHeapPeek(pq_heap))
	{
		printf(RED "TestDequeue failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %ld\n" RESET, *(long *)PQHeapPeek(pq_heap));
		++status;
	}

	PQHeapDestroy(pq_heap);
	return status;
}

int TestSizeAndIsEmpty(void)
{
	int status = 0;
	pq_heap_t *pq_heap = PQHeapCreate(Priority);
	long a = 1;
	long b = 5;
	long c = 10;
	
	if (0 != PQHeapSize(pq_heap))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %ld\n" RESET,
			   PQHeapSize(pq_heap)); 
		++status;
	}
	
	if (1 != PQHeapIsEmpty(pq_heap))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %d\n" RESET,
			   PQHeapIsEmpty(pq_heap)); 
		++status;
	} 
	
	PQHeapEnqueue(pq_heap, &a);
	if (1 != PQHeapSize(pq_heap))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %ld\n" RESET,
			   PQHeapSize(pq_heap)); 
		++status;
	} 
	
	if (0 != PQHeapIsEmpty(pq_heap))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET,
			   PQHeapIsEmpty(pq_heap)); 
		++status;
	} 
	
	PQHeapEnqueue(pq_heap, &b);
	PQHeapEnqueue(pq_heap, &c);
	
	if (3 != PQHeapSize(pq_heap))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 3, actual value- %ld\n" RESET,
			   PQHeapSize(pq_heap)); 
		++status;
	} 
	
	if (0 != PQHeapIsEmpty(pq_heap))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET,
			   PQHeapIsEmpty(pq_heap)); 
		++status;
	}
	
	PQHeapDequeue(pq_heap);
	if (2 != PQHeapSize(pq_heap))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 2, actual value- %ld\n" RESET,
			   PQHeapSize(pq_heap)); 
		++status;
	} 
	
	if (0 != PQHeapIsEmpty(pq_heap))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET,
			   PQHeapIsEmpty(pq_heap)); 
		++status;
	}
	
	PQHeapDequeue(pq_heap);
	PQHeapDequeue(pq_heap);
	if (0 != PQHeapSize(pq_heap))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %ld\n" RESET,
			   PQHeapSize(pq_heap)); 
		++status;
	} 
	
	if (1 != PQHeapIsEmpty(pq_heap))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET,
			   PQHeapIsEmpty(pq_heap)); 
		++status;
	}
	
	PQHeapDestroy(pq_heap); pq_heap = NULL;
	return status;	
}

int TestClear(void)
{
	int status = 0;
	pq_heap_t *pq_heap = PQHeapCreate(Priority);
	long a = 1;
	long b = 5;
	long c = 10;
	long d = 4;
	
	PQHeapEnqueue(pq_heap, &a);
	PQHeapEnqueue(pq_heap, &b);
	PQHeapEnqueue(pq_heap, &c);
	PQHeapEnqueue(pq_heap, &d);
	
	if (4 != PQHeapSize(pq_heap))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 4, actual value- %ld\n" RESET,
			   PQHeapSize(pq_heap)); 
		++status;
	}
	
	if (0 != PQHeapIsEmpty(pq_heap))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET,
			   PQHeapIsEmpty(pq_heap)); 
		++status;
	}
	
	PQHeapClear(pq_heap);
	if (0 != PQHeapSize(pq_heap))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %ld\n" RESET,
			   PQHeapSize(pq_heap)); 
		++status;
	}
	
	if (1 != PQHeapIsEmpty(pq_heap))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %d\n" RESET,
			   PQHeapIsEmpty(pq_heap)); 
		++status;
	}
	
	PQHeapDestroy(pq_heap);
	return status;
}

int TestErase(void)
{
	int status = 0;
	pq_heap_t *pq_heap = PQHeapCreate(Priority);
	long a = 1;
	long b = 5;
	long c = 10;
	long d = 4;
	long removed_data =0; 

	PQHeapEnqueue(pq_heap, &a);
	PQHeapEnqueue(pq_heap, &b);
	PQHeapEnqueue(pq_heap, &c);
	PQHeapEnqueue(pq_heap, &d);
	

	removed_data = *(long *)PQHeapErase(pq_heap, IntIsMatchFunc, &b);
	if (5 != removed_data)
	{
		printf(RED "TestErase failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 10, actual value- %ld\n" RESET, removed_data);
		++status;
	}
	
	if (10 != *(long *)PQHeapPeek(pq_heap))
	{
		printf(RED "TestErase failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 10, actual value- %ld\n" RESET,  *(long *)PQHeapPeek(pq_heap));
		++status;
	}

	removed_data = *(long *)PQHeapErase(pq_heap, IntIsMatchFunc, &c);
	if (10 != removed_data)
	{
		printf(RED "TestErase failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 10, actual value- %ld\n" RESET, removed_data);
		++status;
	}
	
	if (4 != *(long *)PQHeapPeek(pq_heap))
	{
		printf(RED "TestErase failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 4, actual value- %ld\n" RESET,  *(long *)PQHeapPeek(pq_heap));
		++status;
	}

	
	PQHeapDestroy(pq_heap);
	return status;
}

static int Priority(const void *a, const void *b) 
{
   return ( *(long *)a - *(long *)b );
}

static int IntIsMatchFunc(const void *param, const void *value)
{
	return ((long)value == (long)param);
}
