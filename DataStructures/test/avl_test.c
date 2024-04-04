
#include <stdio.h> /* printf */

#include "../../utils/colors.h"
#include "include/avl.h"	

static int CmpFunc(void *a, void *b);
static int PrintValue(void *param, void *value);

int TestCreateAndDestroy(void);
int TestInsert(void);
int TestRemove(void);
int TestHeight(void);
int TestSizeAndIsEmpty(void);
int TestFind(void);
int TestForEach(void);
int TestRemoveBalanced(void);
int TestInsertBalanced(void);


int main()
{
	size_t fail_counter = 0;

	(0 == TestCreateAndDestroy()) ? 1 : ++fail_counter;
	(0 == TestInsert()) ? 1 : ++fail_counter;
	(0 == TestHeight()) ? 1 : ++fail_counter;
	(0 == TestRemove()) ? 1 : ++fail_counter;
	(0 == TestSizeAndIsEmpty()) ? 1 : ++fail_counter;
	(0 == TestFind()) ? 1 : ++fail_counter;
	(0 == TestForEach()) ? 1 : ++fail_counter;
	(0 == TestInsertBalanced()) ? 1 : ++fail_counter;
	(0 == TestRemoveBalanced()) ? 1 : ++fail_counter;
	
	(0 == fail_counter) ? printf(YEL "All tests passed successfuly :)\n" 
	RESET) 
	: printf(RED ":(\n" RESET); 
	return 0;
}

int TestCreateAndDestroy(void)
{
	int status = 0;
	avl_t *avl = AVLCreate(CmpFunc);
	if (NULL == avl)
	{
		printf(RED "TestCreateAndDestroy failed in line %d\n" RESET, 
		__LINE__ );
		printf(RED "AVLCreate returns NULL\n" RESET); 
		++status;
	} 
	
	printf("DO NOT FORGET TO CHECK VLG\n");
	
	AVLDestroy(avl); avl = NULL;
	return status;	
}

int TestInsert(void)
{
	int status = 0;
	avl_t *avl = AVLCreate(CmpFunc);
	long a = 1;
	long b = 3;
	long c = -8;
	
	if (SUCCESS != AVLInsert(avl, &a))
	{
		printf(RED "TestInsert failed in line %d\n" RESET, __LINE__ );
		++status;
	} 
	
	
	if (SUCCESS != AVLInsert(avl, &b))
	{
		printf(RED "TestInsert failed in line %d\n" RESET, __LINE__ );
		++status;
	} 
	
	if (SUCCESS != AVLInsert(avl, &c))
	{
		printf(RED "TestInsert failed in line %d\n" RESET, __LINE__ );
		++status;
	} 
	
	AVLDestroy(avl); avl = NULL;
	return status;	
}

int TestRemove(void)
{
	int status = 0;
	avl_t *avl = AVLCreate(CmpFunc);
	long a = 1;
	long b = 3;
	long c = -8;
	
	AVLInsert(avl, &a);
	AVLInsert(avl, &b);
	AVLInsert(avl, &c);
	
	if (SUCCESS != AVLRemove(avl, &a))
	{
		printf(RED "TestRemove failed in line %d\n" RESET, __LINE__ );
		++status;
	} 
	
	if (SUCCESS != AVLRemove(avl, &c))
	{
		printf(RED "TestRemove failed in line %d\n" RESET, __LINE__ );
		++status;
	} 
	
	if (SUCCESS != AVLRemove(avl, &b))
	{
		printf(RED "TestRemove failed in line %d\n" RESET, __LINE__ );
		++status;
	} 

	AVLDestroy(avl); avl = NULL;
	return status;	
}

int TestHeight(void) 
{
	int status = 0;
	avl_t *avl = AVLCreate(CmpFunc);

	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	
	if (0 != AVLHeight(avl))
	{
		printf(RED "TestHeight failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %ld\n" RESET,
			   AVLHeight(avl)); 
		++status;
	} 

	AVLInsert(avl, &a);
	if (1 != AVLHeight(avl))
	{
		printf(RED "TestHeight failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %ld\n" RESET,
			   AVLHeight(avl)); 
		++status;
	}

	AVLInsert(avl, &b);
	AVLInsert(avl, &c);
	AVLInsert(avl, &d);

	if (3 != AVLHeight(avl))
	{
		printf(RED "TestHeight failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 3, actual value- %ld\n" RESET,
			   AVLHeight(avl)); 
		++status;
	}
	
	AVLDestroy(avl); avl = NULL;
	return status;
}

int TestSizeAndIsEmpty(void)
{
	int status = 0;
	avl_t *avl = AVLCreate(CmpFunc);
	long a = 1;
	long b = 3;
	long c = -8;
	
	if (0 != AVLSize(avl))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %ld\n" RESET,
			   AVLSize(avl)); 
		++status;
	}
	
	if (1 != AVLIsEmpty(avl))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %d\n" RESET,
			   AVLIsEmpty(avl)); 
		++status;
	} 
	
	AVLInsert(avl, &a);
	if (1 != AVLSize(avl))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %ld\n" RESET,
			   AVLSize(avl)); 
		++status;
	} 
	
	if (0 != AVLIsEmpty(avl))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET,
			   AVLIsEmpty(avl)); 
		++status;
	} 
	
	AVLInsert(avl, &b);
	AVLInsert(avl, &c);
	
	if (3 != AVLSize(avl))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 3, actual value- %ld\n" RESET,
			   AVLSize(avl)); 
		++status;
	} 
	
	if (0 != AVLIsEmpty(avl))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET,
			   AVLIsEmpty(avl)); 
		++status;
	}
	
	AVLRemove(avl, &b);
	if (2 != AVLSize(avl))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 2, actual value- %ld\n" RESET,
			   AVLSize(avl)); 
		++status;
	} 
	
	if (0 != AVLIsEmpty(avl))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET,
			   AVLIsEmpty(avl)); 
		++status;
	}
	
	AVLRemove(avl, &a);
	AVLRemove(avl, &c);
	if (0 != AVLSize(avl))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %ld\n" RESET,
			   AVLSize(avl)); 
		++status;
	} 
	
	if (1 != AVLIsEmpty(avl))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET,
			   AVLIsEmpty(avl)); 
		++status;
	}
	
	AVLDestroy(avl); avl = NULL;
	return status;	
}

int TestFind(void)
{
	int status = 0;
	avl_t *avl = AVLCreate(CmpFunc);
	long a = 1;
	long b = 3;
	long c = 4;
	
	AVLInsert(avl, &a);
	AVLInsert(avl, &b);
	
	if (a != *(long*)AVLFind(avl, &a))
	{
		printf(RED "TestFind failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %ld\n" RESET,
			   *(long*)AVLFind(avl, &a)); 
		++status;
	}
	
	if (b != *(long*)AVLFind(avl, &b))
	{
		printf(RED "TestFind failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 3, actual value- %ld\n" RESET,
			   *(long*)AVLFind(avl, &b)); 
		++status;
	}
	
	if (NULL != AVLFind(avl, &c))
	{
		printf(RED "TestFind failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- null\n" RESET); 
		++status;
	}
	
	AVLRemove(avl, &a);
	if (NULL != AVLFind(avl, &a))
	{
		printf(RED "TestFind failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- null\n" RESET); 
		++status;
	}
	
	AVLDestroy(avl); avl = NULL;
	return status;	
}

int TestForEach(void)
{
	int status = 0;
	avl_t *avl = AVLCreate(CmpFunc);
	long a = 'F';
	long b = 'B';
	long c = 'G';
	long d = 'A';
	long e = 'D';
	long f = 'I';
	long g = 'C';
	long h = 'E';
	long i = 'H';
	
	AVLInsert(avl, &a);
	AVLInsert(avl, &b);
	AVLInsert(avl, &c);
	AVLInsert(avl, &d);
	AVLInsert(avl, &e);
	AVLInsert(avl, &f);
	AVLInsert(avl, &g);
	AVLInsert(avl, &h);
	AVLInsert(avl, &i);
	
	printf("pre-order- \n");
	AVLForEach(avl, PrintValue, 0, PRE_ORDER);
	printf("\n");

	printf("post-order- \n");
	AVLForEach(avl, PrintValue, 0, POST_ORDER);
	printf("\n");

	printf("in-order- \n");
	AVLForEach(avl, PrintValue, 0, IN_ORDER);
	printf("\n");
	
	AVLDestroy(avl); avl = NULL;
	return status;	
}

int TestInsertBalanced(void)
{
	int status = 0;
	avl_t *avl = AVLCreate(CmpFunc);
	long a = 5;
	long b = 10;
	long c = 15;
	long d = 1;
	long e = 2;
	long f = 6;
	
	AVLInsert(avl, &a);
	AVLInsert(avl, &b);
	AVLInsert(avl, &c);
	
	if (2 != AVLHeight(avl))
	{
		printf(RED "TestInsertBalanced failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 2, actual value- %ld\n" RESET, AVLHeight(avl)); 
		++status;
	}
	
	AVLInsert(avl, &d);
	AVLInsert(avl, &e);

	if (3 != AVLHeight(avl))
	{
		printf(RED "TestInsertBalanced failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 3, actual value- %ld\n" RESET, AVLHeight(avl)); 
		++status;
	}
	
	AVLInsert(avl, &f);

	if (3 != AVLHeight(avl))
	{
		printf(RED "TestInsertBalanced failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 3, actual value- %ld\n" RESET, AVLHeight(avl)); 
		++status;
	}
	AVLDestroy(avl); avl = NULL;
	return status;	
}

int TestRemoveBalanced(void)
{
	int status = 0;
	avl_t *avl = AVLCreate(CmpFunc);
	long a = 5;
	long b = 10;
	long c = 15;
	long d = 1;
	long e = 2;
	long f = 6;
	long g = 7;
	
	AVLInsert(avl, &a);
	AVLInsert(avl, &b);
	AVLInsert(avl, &c);
	AVLInsert(avl, &d);
	AVLInsert(avl, &e);
	AVLInsert(avl, &f);
	AVLInsert(avl, &g);
	
	if (4 != AVLHeight(avl))
	{
		printf(RED "TestRemoveBalanced failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 4, actual value- %ld\n" RESET, AVLHeight(avl)); 
		++status;
	}
	
	AVLRemove(avl, &d);
	if (3 != AVLHeight(avl))
	{
		printf(RED "TestRemoveBalanced failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 3, actual value- %ld\n" RESET, AVLHeight(avl)); 
		++status;
	}
	
	AVLDestroy(avl); avl = NULL;
	return status;	
}

static int PrintValue(void *param, void *value)
{
	printf("%c ", *(char *)value); 
	
	return 0;
	(void)param;
}

static int CmpFunc(void *a, void *b) 
{
   return ( *(int*)a - *(int*)b );
}
