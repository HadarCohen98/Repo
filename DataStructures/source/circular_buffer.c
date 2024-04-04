
 /* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       0.0.1                                            *
 ~ Date          18.10.22                                         ~
 ~ Description   circular buffer impl using flexible array        ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "../include/circular_buffer.h"

#define MAGIC_NUMBER 0xDEADBEEF
#define MIN(a, b) ((a > b) ? b : a)

static void WriteWordSize(circular_buffer_t *buffer, 
						  size_t bytes_to_copy,
						  char *src_buffer);

static void ReadWordSize(circular_buffer_t *buffer,
			    		 size_t bytes_to_copy,
			      		 char *dest_buffer);


struct circular_buffer
{
	size_t capacity;
	size_t front;
	size_t size;
	unsigned int magic_number;
	char buffer_arr[1];
};

circular_buffer_t *BufferCreate(size_t capacity)
{
	circular_buffer_t *buffer = NULL;
	assert(capacity > 0);
	
	buffer = malloc(sizeof(circular_buffer_t) - 1 + capacity);
	if (NULL == buffer)
	{
		return NULL;
	}
	
	buffer->front = 0;
	buffer->capacity = capacity;
	buffer->size = 0;
	buffer->magic_number = MAGIC_NUMBER;
	
	return buffer;
}

ptrdiff_t BufferWrite(circular_buffer_t *buffer, 
		    		size_t count,
		    		const void *src_buffer)
{
	ptrdiff_t bytes_written = 0;
	size_t bytes_to_write = 0;
	char *src_runner = NULL;
	
	assert(buffer);
	assert(src_buffer);
	
	src_runner = (char *)src_buffer;
	if ((MAGIC_NUMBER == buffer->magic_number))
	{	
		if (buffer->size != buffer->capacity)
		{
			size_t rear = (buffer->front + buffer->size) % 
						   buffer->capacity;
						   
			bytes_to_write = MIN(count, buffer->capacity - rear);
			WriteWordSize(buffer,bytes_to_write, src_runner);
			src_runner += bytes_to_write;
			bytes_written += bytes_to_write;
			
			
			bytes_to_write = MIN(count - bytes_to_write, 
					   			BufferFreeSpace(buffer));
			WriteWordSize(buffer, bytes_to_write, src_runner);
			bytes_written += bytes_to_write;
		}
	}
	
	else
	{
		bytes_written = -1;
	}
	
	return bytes_written;
}

ptrdiff_t BufferRead(void *dest_buffer, circular_buffer_t *buffer, size_t count)
{
	ptrdiff_t bytes_read = 0;
	size_t bytes_to_read = 0;
	char *dest_runner = NULL;
	
	
	assert(buffer);
	assert(dest_buffer);
	
	dest_runner = (char *)dest_buffer;

	if (MAGIC_NUMBER == buffer->magic_number)
	{
		count = MIN(count, buffer->size); 
		if(!BufferIsEmpty(buffer))
		{
			size_t rear = (buffer->front + buffer->size) % 
						   buffer->capacity;
			
			if ((buffer->front >= rear) && (0 != buffer->front))
			{
				bytes_to_read = MIN(count, 
									buffer->capacity - buffer->front);
				
				ReadWordSize(buffer, bytes_to_read, dest_runner);
				dest_runner += bytes_to_read;
				bytes_read += bytes_to_read;
			}
			
			bytes_to_read = MIN(count - bytes_to_read, 
								buffer->capacity - bytes_to_read);
								
			ReadWordSize(buffer, bytes_to_read, dest_runner);
			bytes_read += bytes_to_read;
		}
	}
	
	else
	{
		bytes_read = -1;
	}
	
	return bytes_read;
}

size_t BufferSize(const circular_buffer_t *buffer)
{
	assert(buffer);
	
	return (buffer->size);
}

int BufferIsEmpty(const circular_buffer_t *buffer)
{
	assert(buffer);
	
	return (0 == buffer->size);
}

size_t BufferFreeSpace(const circular_buffer_t *buffer)
{
	assert(buffer);
	
	return (buffer->capacity - buffer->size);
}

void BufferDestroy(circular_buffer_t *buffer)
{
	assert(buffer);
	free(buffer); buffer = NULL;
}


static void WriteWordSize(circular_buffer_t *buffer, 
								size_t bytes_to_write,
								char *src_buffer)
{
	size_t rear = (buffer->front + buffer->size) % buffer->capacity;
	
	memcpy(buffer->buffer_arr + rear, src_buffer, bytes_to_write);
	buffer->size += bytes_to_write;
	
}

static void ReadWordSize(circular_buffer_t *buffer,
			    		   	   size_t bytes_to_read,
			       			   char *dest_buffer)
{
	char *src_buffer = buffer->buffer_arr + buffer->front;
	
	memcpy(dest_buffer, src_buffer, bytes_to_read);
	buffer->size -= bytes_to_read;
	buffer->front = (buffer->front + bytes_to_read) % buffer->capacity;
}	
