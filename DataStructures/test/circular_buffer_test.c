#include <stdio.h> 

#include "../include/circular_buffer.h"

#define RED  "\x1B[31m"
#define YEL  "\x1B[33m"
#define RESET "\x1B[0m"

#define CAPACITY 10

static circular_buffer_t *TestBufferCreate()
{
	circular_buffer_t *my_buffer = BufferCreate(CAPACITY);
	circular_buffer_t *temp = my_buffer;
	BufferDestroy(my_buffer);
	return temp;
}

static int TestBufferWrite()
{	
	int status = 0;
	circular_buffer_t *my_buffer = BufferCreate(CAPACITY);
	
	status += (5 != BufferWrite(my_buffer, 5, "hello"));
	status += (4 != BufferWrite(my_buffer, 4, "aaaa"));
	status += (1 != BufferWrite(my_buffer, 2, "hi"));
	status += (0 != BufferWrite(my_buffer, 1, "bbbb"));
	
	BufferDestroy(my_buffer);
	return status;
}

static int TestBufferRead()
{	
	int status = 0;
	circular_buffer_t *my_buffer = BufferCreate(CAPACITY);
	char dest[5];
	
	BufferWrite(my_buffer, 5, "hello");
	status += (5 != BufferRead(dest, my_buffer, 5));
	status += (0 != BufferRead(dest, my_buffer, 7));

	BufferDestroy(my_buffer);
	return status;
}

static int TestBufferSize()
{
	int status = 0;
	circular_buffer_t *my_buffer = BufferCreate(CAPACITY);
	char dest[10];
	
	status += (0 != BufferSize(my_buffer));
	
	BufferWrite(my_buffer, 5, "hello");
	status += (5 != BufferSize(my_buffer));
	
	BufferWrite(my_buffer, 5, "hadar");
	status += (10 != BufferSize(my_buffer));
	
	BufferRead(dest, my_buffer, 10);
	status += (0 != BufferSize(my_buffer));
	
	BufferDestroy(my_buffer);
	return status;
}

static int TestBufferIsEmpty()
{
	int status = 0;
	circular_buffer_t *my_buffer = BufferCreate(CAPACITY);
	char dest[5];
	
	status += (1 != BufferIsEmpty(my_buffer));
	
	BufferWrite(my_buffer, 4, "aaaa");
	status += (0 != BufferIsEmpty(my_buffer));
	
	BufferRead(dest, my_buffer, 5);
	status += (1 != BufferIsEmpty(my_buffer));
	
	BufferDestroy(my_buffer);
	return status;
}

static int TestBufferFreeSpace()
{
	int status = 0;
	circular_buffer_t *my_buffer = BufferCreate(CAPACITY);
	
	status += (10 != BufferFreeSpace(my_buffer));
	
	BufferWrite(my_buffer, 5, "hello");
	status += (5 != BufferFreeSpace(my_buffer));
	
	BufferWrite(my_buffer, 5, "hadar");
	status += (0 != BufferFreeSpace(my_buffer));
	
	BufferDestroy(my_buffer);
	return status;
}

int main()
{	
	int counter = 0;
	int fail_counter = 0;
	
	(NULL != TestBufferCreate()) ? ++counter : printf(RED "Test %d failed\n" RESET, ++counter) && ++fail_counter;
	
	(0 == TestBufferWrite()) ? ++counter : printf(RED "Test %d failed\n" RESET, ++counter) && ++fail_counter;
	
	(0 == TestBufferRead()) ? ++counter : printf(RED "Test %d failed\n" RESET, ++counter) && ++fail_counter;
	
	(0 == TestBufferSize()) ? ++counter : printf(RED "Test %d failed\n" RESET, ++counter) && ++fail_counter;
	
	(0 == TestBufferIsEmpty()) ? ++counter : printf(RED "Test %d failed\n" RESET, ++counter) && ++fail_counter;
	
	(0 == TestBufferFreeSpace()) ? ++counter : printf(RED "Test %d failed\n" RESET, ++counter) && ++fail_counter;
	
	
	(0 == fail_counter) ? printf(YEL "All tests passed successfuly :)\n" RESET) : printf(RED ":(\n" RESET); 
	return 0;
}


