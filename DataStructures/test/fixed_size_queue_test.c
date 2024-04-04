
#include "include/fixed_size_queue.h"

#include <stdio.h> /* printf */

#define CAPACITY 2

int main()
{
	fsq_t *my_fsq = FSQCreate(CAPACITY);
	
	long x = 3;
	long y = 666;
	long z = -90;
	
	printf("---------init fsq---------\n");
	printf("fsq is empty? %d\n", FSQIsEmpty(my_fsq));
	printf("the size of fsq is- %lu\n", FSQSize(my_fsq));
	
	printf("\n---------first insertion---------\n");
	(0 == FSQEnqueue(my_fsq, &x)) ? printf("insert succeed\n") : printf("insert failed\n");
	printf("the value is- %ld\n", *(long *)FSQPeek(my_fsq));
	printf("fsq is empty? %d\n", FSQIsEmpty(my_fsq));
	printf("the size of fsq is- %lu\n", FSQSize(my_fsq));
		
	printf("\n---------second insertion---------\n");
	(0 == FSQEnqueue(my_fsq, &y)) ? printf("insert succeed\n") : printf("insert failed\n");
	printf("fsq is empty? %d\n", FSQIsEmpty(my_fsq));
	printf("the size of fsq is- %lu\n", FSQSize(my_fsq));
	
	printf("\n---------third insertion---------\n");
	(1 == FSQEnqueue(my_fsq, &z)) ? printf("TEST succeed\n") : printf("TEST failed\n");
	printf("fsq is empty? %d\n", FSQIsEmpty(my_fsq));
	printf("the size of fsq is- %lu\n", FSQSize(my_fsq));	
	
	printf("\n---------remove first---------\n");
	printf("element to remove- %ld\n", *(long *)FSQDequeue(my_fsq));
	printf("the new head of the fsq is- %ld\n", *(long *)FSQPeek(my_fsq));
	printf("fsq is empty? %d\n", FSQIsEmpty(my_fsq));
	printf("the size of fsq is- %lu\n", FSQSize(my_fsq));
	
	printf("\n---------remove second---------\n");
	printf("element to remove- %ld\n", *(long *)FSQDequeue(my_fsq));
	printf("fsq is empty? %d\n", FSQIsEmpty(my_fsq));
	printf("the size of fsq is- %lu\n", FSQSize(my_fsq));
	
	printf("\n---------first insertion---------\n");
	(0 == FSQEnqueue(my_fsq, &x)) ? printf("insert succeed\n") : printf("insert failed\n");
	printf("the new head of the fsq is- %ld\n", *(long *)FSQPeek(my_fsq));
	printf("fsq is empty? %d\n", FSQIsEmpty(my_fsq));
	printf("the size of fsq is- %lu\n", FSQSize(my_fsq));	
	
	FSQDestroy(my_fsq);
	
	return 0;
}
