#include <stdio.h> /* printf */

#include "../../utils/utilities.h"
#include "include/bst.h"	

static int CmpFunc(void *a, void *b);
static int AddToIter(void *param, void *value);

int TestCreateAndDestroy(void);
int TestInsert(void);
int TestRemove(void);
int TestSizeAndIsEmpty(void);
int TestIsSameIter(void);
int TestBegin(void);
int TestPrevAndNext(void);
int TestFind(void);
int TestForEach(void);


int main()
{
	size_t fail_counter = 0;

	(0 == TestCreateAndDestroy()) ? 1 : ++fail_counter;
	(0 == TestInsert()) ? 1 : ++fail_counter;
	(0 == TestRemove()) ? 1 : ++fail_counter;
	(0 == TestSizeAndIsEmpty()) ? 1 : ++fail_counter;
	(0 == TestIsSameIter()) ? 1 : ++fail_counter;
	(0 == TestBegin()) ? 1 : ++fail_counter;
	(0 == TestPrevAndNext()) ? 1 : ++fail_counter;
	(0 == TestFind()) ? 1 : ++fail_counter;
	(0 == TestForEach()) ? 1 : ++fail_counter;
	
	(0 == fail_counter) ? printf(YEL "All tests passed successfuly :)\n" 
	RESET) 
	: printf(RED ":(\n" RESET); 
	return 0;
}

int TestCreateAndDestroy(void)
{
	int status = 0;
	bst_t *bst = BSTCreate(CmpFunc);
	if (NULL == bst)
	{
		printf(RED "TestCreateAndDestroy failed in line %d\n" RESET, 
		__LINE__ );
		printf(RED "BSTCreate returns NULL\n" RESET); 
		++status;
	} 
	
	printf("DO NOT FORGET TO CHECK VLG\n");
	
	BSTDestroy(bst); bst = NULL;
	return status;	
}

int TestInsert(void)
{
	int status = 0;
	bst_t *bst = BSTCreate(CmpFunc);
	bst_iter_t inserted = {0};
	long a = 1;
	long b = 3;
	long c = -8;
	
	inserted = BSTInsert(bst, &a);
	if (1 == BSTIsSameIter(BSTEnd(bst), inserted))
	{
		printf(RED "TestInsert failed in line %d\n" RESET, __LINE__ );
		printf(RED "iter is BSTEnd\n" RESET); 
		++status;
	} 
	
	if (a != *(long*)BSTGetData(inserted))
	{
		printf(RED "TestInsert failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %ld\n" RESET,
			   *(long*)BSTGetData(inserted)); 
		++status;
	} 
	
	inserted = BSTInsert(bst, &b);
	if (1 == BSTIsSameIter(BSTEnd(bst), inserted))
	{
		printf(RED "TestInsert failed in line %d\n" RESET, __LINE__ );
		printf(RED "iter is null\n" RESET); 
		++status;
	} 
	
	if (b != *(long*)BSTGetData(inserted))
	{
		printf(RED "TestInsert failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 3, actual value- %ld\n" RESET,
			   *(long*)BSTGetData(inserted)); 
		++status;
	} 
	
	inserted = BSTInsert(bst, &c);
	if (1 == BSTIsSameIter(BSTEnd(bst), inserted))
	{
		printf(RED "TestInsert failed in line %d\n" RESET, __LINE__ );
		printf(RED "iter is null\n" RESET); 
		++status;
	} 
	
	if (c != *(long*)BSTGetData(inserted))
	{
		printf(RED "TestInsert failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- -8, actual value- %ld\n" RESET,
			   *(long*)BSTGetData(inserted)); 
		++status;
	} 
	
	BSTDestroy(bst); bst = NULL;
	return status;	
}

int TestRemove(void)
{
	int status = 0;
	bst_t *bst = BSTCreate(CmpFunc);
	bst_iter_t inserted = {0};
	long a = 1;
	long b = 3;
	long c = -8;
	long d = -10;
	
	BSTInsert(bst, &a);
	inserted = BSTInsert(bst, &b);
	BSTInsert(bst, &c);
	
	BSTRemove(inserted);
	
	inserted = BSTInsert(bst, &d);
	BSTRemove(inserted);

	BSTDestroy(bst); bst = NULL;
	return status;	
}

int TestSizeAndIsEmpty(void)
{
	int status = 0;
	bst_t *bst = BSTCreate(CmpFunc);
	bst_iter_t inserted_1 = {0};
	bst_iter_t inserted_2 = {0};
	bst_iter_t inserted_3 = {0};
	long a = 1;
	long b = 3;
	long c = -8;
	
	if (0 != BSTSize(bst))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %ld\n" RESET,
			   BSTSize(bst)); 
		++status;
	} 
	
	if (1 != BSTIsEmpty(bst))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %d\n" RESET,
			   BSTIsEmpty(bst)); 
		++status;
	} 
	
	inserted_1 = BSTInsert(bst, &a);
	if (1 != BSTSize(bst))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %ld\n" RESET,
			   BSTSize(bst)); 
		++status;
	} 
	
	if (0 != BSTIsEmpty(bst))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET,
			   BSTIsEmpty(bst)); 
		++status;
	} 
	
	inserted_2 = BSTInsert(bst, &b);
	inserted_3 = BSTInsert(bst, &c);
	
	if (3 != BSTSize(bst))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 3, actual value- %ld\n" RESET,
			   BSTSize(bst)); 
		++status;
	} 
	
	if (0 != BSTIsEmpty(bst))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET,
			   BSTIsEmpty(bst)); 
		++status;
	}
	
	BSTRemove(inserted_3);
	if (2 != BSTSize(bst))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 2, actual value- %ld\n" RESET,
			   BSTSize(bst)); 
		++status;
	} 
	
	if (0 != BSTIsEmpty(bst))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET,
			   BSTIsEmpty(bst)); 
		++status;
	}
	
	BSTRemove(inserted_1);
	BSTRemove(inserted_2);
	if (0 != BSTSize(bst))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %ld\n" RESET,
			   BSTSize(bst)); 
		++status;
	} 
	
	if (1 != BSTIsEmpty(bst))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET,
			   BSTIsEmpty(bst)); 
		++status;
	}
	
	BSTDestroy(bst); bst = NULL;
	return status;	
}

int TestIsSameIter(void)
{
	int status = 0;
	bst_t *bst = BSTCreate(CmpFunc);
	bst_iter_t inserted_1 = {0};
	bst_iter_t inserted_2 = {0};
	bst_iter_t inserted_3 = {0};
	long a = 1;
	long b = 3;
	
	inserted_1 = BSTInsert(bst, &a);
	inserted_2 = BSTInsert(bst, &b);
	inserted_3 = inserted_1;
	
	if (0 != BSTIsSameIter(inserted_1, inserted_2))
	{
		printf(RED "TestIsSameIter failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET,
			   BSTIsSameIter(inserted_1, inserted_2)); 
		++status;
	}
	
	if (1 != BSTIsSameIter(inserted_1, inserted_3))
	{
		printf(RED "TestIsSameIter failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %d\n" RESET,
			   BSTIsSameIter(inserted_1, inserted_3)); 
		++status;
	}

	BSTDestroy(bst); bst = NULL;
	return status;	
}

int TestBegin(void)
{
	int status = 0;
	bst_t *bst = BSTCreate(CmpFunc);
	bst_iter_t inserted_1 = {0};
	bst_iter_t inserted_2 = {0};
	bst_iter_t inserted_3 = {0};
	long a = 1;
	long b = 3;
	long c = -8;
	long d = -10;
	
	inserted_3 = BSTInsert(bst, &a);
	BSTInsert(bst, &b);
	inserted_1 = BSTInsert(bst, &c);
	
	if (1 != BSTIsSameIter(inserted_1, BSTBegin(bst)))
	{
		printf(RED "TestBegin failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- -8, actual value- %ld\n" RESET,
			    *(long*)BSTGetData(BSTBegin(bst))); 
		++status;
	}
	
	inserted_2 = BSTInsert(bst, &d);
	if (1 != BSTIsSameIter(inserted_2, BSTBegin(bst)))
	{
		printf(RED "TestBegin failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- -10, actual value- %ld\n" RESET,
			    *(long*)BSTGetData(BSTBegin(bst))); 
		++status;
	}
	
	BSTRemove(inserted_1);
	BSTRemove(inserted_2);
	if (1 != BSTIsSameIter(inserted_3, BSTBegin(bst)))
	{
		printf(RED "TestBegin failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %ld\n" RESET,
			   *(long*)BSTGetData(BSTBegin(bst))); 
		++status;
	}

	BSTDestroy(bst); bst = NULL;
	return status;	
}

int TestPrevAndNext(void)
{
	int status = 0;
	bst_t *bst = BSTCreate(CmpFunc);
	bst_iter_t inserted_1 = {0};
	bst_iter_t inserted_2 = {0};
	bst_iter_t inserted_3 = {0};
	long a = 1;
	long b = 3;
	long c = -8;
	
	inserted_1 = BSTInsert(bst, &a);
	inserted_2 = BSTInsert(bst, &b);
	inserted_3 = BSTInsert(bst, &c);
	
	if (1 != BSTIsSameIter(inserted_3, BSTPrev(inserted_1)))
	{
		printf(RED "TestPrev failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- -8, actual value- %ld\n" RESET,
			   *(long*)BSTGetData(BSTPrev(inserted_1))); 
		++status;
	}
	
	if (1 != BSTIsSameIter(inserted_2, BSTNext(inserted_1)))
	{
		printf(RED "TestNext failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 3, actual value- %ld\n" RESET,
			   *(long*)BSTGetData(BSTNext(inserted_1))); 
		++status;
	}
	
	if (1 != BSTIsSameIter(inserted_1, BSTPrev(inserted_2)))
	{
		printf(RED "TestPrev failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %ld\n" RESET,
			   *(long*)BSTGetData(BSTPrev(inserted_1))); 
		++status;
	}
	
	if (1 != BSTIsSameIter(BSTEnd(bst), BSTNext(inserted_2)))
	{
		printf(RED "TestNext failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- BSTEnd, actual value- %ld\n" RESET,
			   *(long*)BSTGetData(BSTNext(inserted_2))); 
		++status;
	}
	
	BSTRemove(inserted_1);
	if (1 != BSTIsSameIter(inserted_3, BSTPrev(inserted_2)))
	{
		printf(RED "TestPrev failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- -8, actual value- %ld\n" RESET,
			   *(long*)BSTGetData(BSTPrev(inserted_1))); 
		++status;
	}
	
	if (1 != BSTIsSameIter(inserted_2, BSTNext(inserted_3)))
	{
		printf(RED "TestNext failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 3, actual value- %ld\n" RESET,
			   *(long*)BSTGetData(BSTNext(inserted_3))); 
		++status;
	}
	
	BSTDestroy(bst); bst = NULL;
	return status;	
}

int TestFind(void)
{
	int status = 0;
	bst_t *bst = BSTCreate(CmpFunc);
	bst_iter_t inserted_1 = {0};
	bst_iter_t inserted_2 = {0};
	long a = 1;
	long b = 3;
	long c = 4;
	
	inserted_1 = BSTInsert(bst, &a);
	inserted_2 = BSTInsert(bst, &b);
	
	if (1 != BSTIsSameIter(inserted_1, BSTFind(bst, &a)))
	{
		printf(RED "TestFind failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %ld\n" RESET,
			   *(long*)BSTGetData(BSTFind(bst, &a))); 
		++status;
	}
	
	if (1 != BSTIsSameIter(inserted_2, BSTFind(bst, &b)))
	{
		printf(RED "TestFind failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 3, actual value- %ld\n" RESET,
			   *(long*)BSTGetData(BSTFind(bst, &b))); 
		++status;
	}
	
	if (1 != BSTIsSameIter(BSTEnd(bst), BSTFind(bst, &c)))
	{
		printf(RED "TestFind failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- BSTEnd\n" RESET); 
		++status;
	}
	
	BSTRemove(inserted_1);
	if (1 != BSTIsSameIter(BSTEnd(bst), BSTFind(bst, &a)))
	{
		printf(RED "TestFind failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- BSTEnd\n" RESET); 
		++status;
	}
	
	BSTDestroy(bst); bst = NULL;
	return status;	
}

int TestForEach(void)
{
	int status = 0;
	bst_t *bst = BSTCreate(CmpFunc);
	bst_iter_t inserted_1 = {0};
	bst_iter_t inserted_2 = {0};
	bst_iter_t inserted_3 = {0};
	long a = 1;
	long b = 3;
	long c = -8;
	long p = 100;
	
	inserted_1 = BSTInsert(bst, &a);
	inserted_2 = BSTInsert(bst, &b);
	inserted_3 = BSTInsert(bst, &c);
	
	BSTForEach(BSTBegin(bst), BSTEnd(bst), AddToIter, &p);
	
	if (101 != *(long*)BSTGetData(inserted_1))
	{
		printf(RED "TestForEach failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 101, actual value- %ld\n" RESET,
			   *(long*)BSTGetData(inserted_1)); 
		++status;
	}
	
	if (103 != *(long*)BSTGetData(inserted_2))
	{
		printf(RED "TestForEach failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 103, actual value- %ld\n" RESET,
			   *(long*)BSTGetData(inserted_2)); 
		++status;
	}
	
	if (92 != *(long*)BSTGetData(inserted_3))
	{
		printf(RED "TestForEach failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 92, actual value- %ld\n" RESET,
			   *(long*)BSTGetData(inserted_3)); 
		++status;
	}
	
	BSTDestroy(bst); bst = NULL;
	return status;	
}

static int AddToIter(void *param, void *value)
{
	*(long *)value += *(long *)param; 
	return 0;
}

static int CmpFunc(void *a, void *b) 
{
   return ( *(int*)a - *(int*)b );
}
