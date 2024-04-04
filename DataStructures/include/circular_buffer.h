#ifndef __CIRCULAR_BUFFER__
#define __CIRCULAR_BUFFER__

#include <sys/types.h> /* ptrdiff_t */
#include <stddef.h> /* size_t */
#include <cstddef>

typedef struct circular_buffer circular_buffer_t;

/*
Description- The BufferCreate() function creates a new circular_buffer_t 
type.
Return Value- The function returns a pointer to the new circular buffer, in 
the case of failure the returned pointer will be NULL.
Time complexity- O(1).
*/
circular_buffer_t *BufferCreate(size_t capacity); 

/*
Description- The BufferWrite() function writes "count" bytes from 
src_buffer into the circular buffer. 
Return Value- In success, the function returns the number of bytes written. 
The function fails when "buffer" is not a circular_buffer_t type. In the 
case of failure the fucntion returns -1 (therefore the return type is 
ptrdiff_t, signed size_t).
Notes- If count is bigger than the free sapce left on the circular buffer, 
only the number of bytes in the free space will be written.
Time complexity- O(n).
*/
ptrdiff_t BufferWrite(circular_buffer_t *buffer, size_t count, 
					const void *src_buffer);

/*
Description- The BufferRead() function writes "count" bytes from the 
circular buffer into dest_buffer. 
Return Value- In success, the function returns the number of bytes written. 
The function fails when "buffer" is not a circular_buffer_t type. In the 
case of failure the fucntion returns -1 (therefore the return type is 
ptrdiff_t, signed size_t).
Notes- If count is bigger than the free sapce left on the circular buffer, 
only the number of bytes in the free space will be written.
Time complexity- O(n).
*/
ptrdiff_t BufferRead(void *dest_buffer, circular_buffer_t *buffer, 
				   size_t count); 

/*
Description- The BufferSize() returns the current size of the circular 
buffer.
Return Value- The size in size_t type.
Time complexity- O(1).
*/
size_t BufferSize(const circular_buffer_t *buffer);

/*
Description- The BufferIsEmpty() checks if the circular buffer is empty.
Return Value- If empty the returns value is 1, otherwise 0.
Time complexity- O(1).
*/
int BufferIsEmpty(const circular_buffer_t *buffer);

/*
Description- The BufferFreeSpace() checks for the number of free bytes in 
the circular buffer.
Return Value- The number of free bytes in size_t type.
Time complexity- O(1).
*/
size_t BufferFreeSpace(const circular_buffer_t *buffer);

/*
Description- The BufferDestroy() function frees the buffer.
Time complexity- O(1).
*/
void BufferDestroy(circular_buffer_t *buffer);

#endif /* __CIRCULAR_BUFFER__*/
