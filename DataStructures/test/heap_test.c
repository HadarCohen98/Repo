#include <stdio.h> /* printf */

#include "../../utils/utilities.h"
#include "include/heap.h"	

static int CmpFunc(const void *a, const void *b);
static int IntIsMatchFunc(const void *param, const void *value);

int TestCreateAndDestroy(void);
int TestPush(void);
int TestPop(void);
int TestRemove(void);
int TestSizeAndIsEmpty(void);


int main()
{
	size_t fail_counter = 0;

	(0 == TestCreateAndDestroy()) ? 1 : ++fail_counter;
	(0 == TestPush()) ? 1 : ++fail_counter;
	(0 == TestPop()) ? 1 : ++fail_counter;
	(0 == TestSizeAndIsEmpty()) ? 1 : ++fail_counter;
	(0 == TestRemove()) ? 1 : ++fail_counter;
	
	(0 == fail_counter) ? printf(YEL "All tests passed successfuly :)\n" 
	RESET) 
	: printf(RED ":(\n" RESET); 
	return 0;
}

int TestCreateAndDestroy(void)
{
	int status = 0;
	heap_t *heap = HeapCreate(CmpFunc);
	if (NULL == heap)
	{
		printf(RED "TestCreateAndDestroy failed in line %d\n" RESET, 
		__LINE__ );
		printf(RED "HeapCreate returns NULL\n" RESET); 
		++status;
	} 
	
	printf("DO NOT FORGET TO CHECK VLG\n");
	
	HeapDestroy(heap); heap = NULL;
	return status;	
}

int TestPush(void)
{
	int status = 0;
	heap_t *heap = HeapCreate(CmpFunc);
	long a = 1;
	long b = 3;
	long c = -8;
	long d = 2;
	long e = 5;
	
	if (SUCCESS != HeapPush(heap, &a))
	{
		printf(RED "TestPush failed in line %d\n" RESET, __LINE__ );
		++status;
	} 
	
	if (a != *(long *)HeapPeek(heap))
	{
		printf(RED "TestPush failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- %ld, actual value- %ld\n" RESET, a,  *(long *)HeapPeek(heap));
		++status;
	}
	
	if (SUCCESS != HeapPush(heap, &b))
	{
		printf(RED "TestPush failed in line %d\n" RESET, __LINE__ );
		++status;
	} 

	if (b != *(long *)HeapPeek(heap))
	{
		printf(RED "TestPush failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- %ld, actual value- %ld\n" RESET, b,  *(long *)HeapPeek(heap));
		++status;
	}
	
	if (SUCCESS != HeapPush(heap, &c))
	{
		printf(RED "TestPush failed in line %d\n" RESET, __LINE__ );
		++status;
	} 

	if (b != *(long *)HeapPeek(heap))
	{
		printf(RED "TestPush failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- %ld, actual value- %ld\n" RESET, b,  *(long *)HeapPeek(heap));
		++status;
	}

	HeapPush(heap, &d);
	HeapPush(heap, &e);
	if (e != *(long *)HeapPeek(heap))
	{
		printf(RED "TestPush failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- %ld, actual value- %ld\n" RESET, b,  *(long *)HeapPeek(heap));
		++status;
	}
	
	HeapDestroy(heap); heap = NULL;
	return status;	
}

int TestPop(void)
{
	int status = 0;
	heap_t *heap = HeapCreate(CmpFunc);
	long a = 1;
	long b = 3;
	long c = -8;
	long d = 2;
	long e = 5;
	long removed_data = 0;
	
	HeapPush(heap, &a);
	HeapPush(heap, &b);
	HeapPush(heap, &c);
	HeapPush(heap, &d);
	HeapPush(heap, &e);

	removed_data = *(long *)HeapPop(heap);
	if (5 != removed_data)
	{
		printf(RED "TestPop failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 5, actual value- %ld\n" RESET, removed_data);
		++status;
	}
	
	if (3 != *(long *)HeapPeek(heap))
	{
		printf(RED "TestPop failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 3, actual value- %ld\n" RESET,  *(long *)HeapPeek(heap));
		++status;
	}

	removed_data = *(long *)HeapPop(heap);
	if (3 != removed_data)
	{
		printf(RED "TestPop failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 3, actual value- %ld\n" RESET, removed_data);
		++status;
	}

	if (2 != *(long *)HeapPeek(heap))
	{
		printf(RED "TestPop failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 2, actual value- %ld\n" RESET,  *(long *)HeapPeek(heap));
		++status;
	}

	removed_data = *(long *)HeapPop(heap);
	if (2 != removed_data)
	{
		printf(RED "TestPop failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 2, actual value- %ld\n" RESET, removed_data);
		++status;
	}

	if (1 != *(long *)HeapPeek(heap))
	{
		printf(RED "TestPop failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %ld\n" RESET, *(long *)HeapPeek(heap));
		++status;
	}

	HeapDestroy(heap); heap = NULL;
	return status;	
}

int TestRemove(void)
{
	int status = 0;
	heap_t *heap = HeapCreate(CmpFunc);
	long a = 1;
	long b = 3;
	long c = -8;
	long d = 2;
	long e = 5;
	long removed_data = 0;
	
	HeapPush(heap, &a);
	HeapPush(heap, &b);
	HeapPush(heap, &c);
	HeapPush(heap, &d);
	HeapPush(heap, &e);
	
	removed_data = *(long*)HeapRemove(heap, IntIsMatchFunc, &c);
	if (-8 != removed_data)
	{
		printf(RED "TestRemove failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- %ld, actual value- %ld\n" RESET,c, removed_data);
		++status;
	} 
	
	removed_data = *(long*)HeapRemove(heap, IntIsMatchFunc, &a);
	if (1 != removed_data)
	{
		printf(RED "TestRemove failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %ld\n" RESET, removed_data);
		++status;
	} 

	removed_data = *(long*)HeapRemove(heap, IntIsMatchFunc, &e);
	if (5 != removed_data)
	{
		printf(RED "TestRemove failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 5, actual value- %ld\n" RESET, removed_data);
		++status;
	} 

	if (NULL != HeapRemove(heap, IntIsMatchFunc, &e))
	{
		printf(RED "TestRemove failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- null\n" RESET);
		++status;
	} 

	HeapDestroy(heap); heap = NULL;
	return status;	
}

int TestSizeAndIsEmpty(void)
{
	int status = 0;
	heap_t *heap = HeapCreate(CmpFunc);
	long a = 1;
	long b = 3;
	long c = -8;
	
	if (0 != HeapSize(heap))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %ld\n" RESET,
			   HeapSize(heap)); 
		++status;
	}
	
	if (1 != HeapIsEmpty(heap))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %d\n" RESET,
			   HeapIsEmpty(heap)); 
		++status;
	} 
	
	HeapPush(heap, &a);
	if (1 != HeapSize(heap))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %ld\n" RESET,
			   HeapSize(heap)); 
		++status;
	} 
	
	if (0 != HeapIsEmpty(heap))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET,
			   HeapIsEmpty(heap)); 
		++status;
	} 
	
	HeapPush(heap, &b);
	HeapPush(heap, &c);
	
	if (3 != HeapSize(heap))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 3, actual value- %ld\n" RESET,
			   HeapSize(heap)); 
		++status;
	} 
	
	if (0 != HeapIsEmpty(heap))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET,
			   HeapIsEmpty(heap)); 
		++status;
	}
	
	HeapPop(heap);
	if (2 != HeapSize(heap))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 2, actual value- %ld\n" RESET,
			   HeapSize(heap)); 
		++status;
	} 
	
	if (0 != HeapIsEmpty(heap))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET,
			   HeapIsEmpty(heap)); 
		++status;
	}
	
	HeapPop(heap);
	HeapPop(heap);
	if (0 != HeapSize(heap))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %ld\n" RESET,
			   HeapSize(heap)); 
		++status;
	} 
	
	if (1 != HeapIsEmpty(heap))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET,
			   HeapIsEmpty(heap)); 
		++status;
	}
	
	HeapDestroy(heap); heap = NULL;
	return status;	
}


static int CmpFunc(const void *a, const void *b) 
{
   return ( *(long *)a - *(long *)b );
}

static int IntIsMatchFunc(const void *param, const void *value)
{
	return ((size_t)value == (size_t)param);
}