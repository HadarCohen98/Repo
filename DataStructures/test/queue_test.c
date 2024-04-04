
#include <stdio.h> /* printf */
#include <stdlib.h> /* free */

#include "include/queue.h"

int main()
{
	queue_t *my_queue = QueueCreate();
	queue_t *my_queue_1 = QueueCreate();
	
	long x = 3;
	long y = 666;
	long z = -90;
	long a = 5;
	long b = -10;
	long c = 80;
	long d = 100;
	
	printf("---------init queue---------\n");
	printf("queue is empty? %d\n", QueueIsEmpty(my_queue));
	printf("the size of queue is- %lu\n", QueueSize(my_queue));
	
	printf("\n---------first insertion---------\n");
	(0 == Enqueue(my_queue, (void *)x)) ? printf("insert succeed\n") : printf("insert failed\n");
	printf("the value is- %ld\n", (long)QueuePeek(my_queue));
	printf("queue is empty? %d\n", QueueIsEmpty(my_queue));
	printf("the size of queue is- %lu\n", QueueSize(my_queue));
		
	printf("\n---------second insertion---------\n");
	(0 == Enqueue(my_queue, (void *)y)) ? printf("insert succeed\n") : printf("insert failed\n");
	printf("queue is empty? %d\n", QueueIsEmpty(my_queue));
	printf("the size of queue is- %lu\n", QueueSize(my_queue));
	
	printf("\n---------third insertion---------\n");
	(0 == Enqueue(my_queue, (void *)z)) ? printf("insert succeed\n") : printf("insert failed\n");
	printf("queue is empty? %d\n", QueueIsEmpty(my_queue));
	printf("the size of queue is- %lu\n", QueueSize(my_queue));	
	
	printf("\n---------remove first---------\n");
	printf("element to remove- %ld\n", (long)Dequeue(my_queue));
	printf("the new head of the queue is- %ld\n", (long)QueuePeek(my_queue));
	printf("queue is empty? %d\n", QueueIsEmpty(my_queue));
	printf("the size of queue is- %lu\n", QueueSize(my_queue));
	
	printf("\n---------remove seocnd---------\n");
	printf("element to remove- %ld\n", (long)Dequeue(my_queue));
	printf("the new head of the queue is- %ld\n", (long)QueuePeek(my_queue));
	printf("queue is empty? %d\n", QueueIsEmpty(my_queue));
	printf("the size of queue is- %lu\n", QueueSize(my_queue));
	
	printf("\n---------remove last---------\n");
	printf("element to remove- %ld\n", (long)Dequeue(my_queue));
	printf("the new head of the queue is- %ld\n", (long)QueuePeek(my_queue));
	printf("queue is empty? %d\n", QueueIsEmpty(my_queue));
	printf("the size of queue is- %lu\n", QueueSize(my_queue));
	
	printf("\n---------first insertion---------\n");
	(0 == Enqueue(my_queue, (void *)x)) ? printf("insert succeed\n") : printf("insert failed\n");
	printf("the new head of the queue is- %ld\n", (long)QueuePeek(my_queue));
	printf("queue is empty? %d\n", QueueIsEmpty(my_queue));
	printf("the size of queue is- %lu\n", QueueSize(my_queue));	
	
	printf("\n---------create another queue---------\n");
	Enqueue(my_queue_1, (void *)a);
	Enqueue(my_queue_1, (void *)b);
	Enqueue(my_queue_1, (void *)c);
	Enqueue(my_queue_1, (void *)d);
	printf("the head of the queue is- %ld\n", (long)QueuePeek(my_queue_1));
	printf("queue is empty? %d\n", QueueIsEmpty(my_queue_1));
	printf("the size of queue is- %lu\n", QueueSize(my_queue_1));
	
	printf("\n---------append queue---------\n");
	QueueAppend(my_queue, my_queue_1);
	printf("the size of queue (dest) is- %lu\n", QueueSize(my_queue));
	printf("the size of queue (src) is- %lu\n", QueueSize(my_queue_1));
	printf("the head of the queue is- %ld\n", (long)QueuePeek(my_queue));
	
	Dequeue(my_queue);
	printf("the head of the queue is- %ld\n", (long)QueuePeek(my_queue));
	Dequeue(my_queue);
	printf("the head of the queue is- %ld\n", (long)QueuePeek(my_queue));
	Dequeue(my_queue);
	printf("the head of the queue is- %ld\n", (long)QueuePeek(my_queue));
	Dequeue(my_queue);
	printf("the head of the queue is- %ld\n", (long)QueuePeek(my_queue));
	Dequeue(my_queue);
	printf("the head of the queue is- %ld\n", (long)QueuePeek(my_queue)); 
	
	QueueDestroy(my_queue);
	QueueDestroy(my_queue_1);
	
	return 0;
}
