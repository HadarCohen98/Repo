/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       1.0.0                                           *
 ~ Date          24/11/22                                        ~
 ~ Description   Bit Array Header                                ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#ifndef __BIT_ARRAY__
#define __BIT_ARRAY__

#include <stddef.h>

typedef size_t bit_array_t;
	
/*
Description- The SetAllBitArray() function return a bit array that all the
bits are set (equal to 1).
Return Value- The function returns the bit array.
Time complexity- O(1).
*/
bit_array_t SetAllBitArray(void);

/*
Description- The ResetAllBitArray() function return a bit array whose all
bits are 0.
Return Value- The function returns the bit array.
Time complexity- O(1).
*/
bit_array_t ResetAllBitArray(void);

/*
Description- The SetOnBitArray() function set the n_bit to 1. 
Return Value- The function returns the new bit array.
Time complexity- O(1).
*/
bit_array_t SetOnBitArray(bit_array_t bit_arr, size_t n_bit);

/*
Description- The SetOffBitArray() function set off the n_bit (i.e set to 0).
Return Value- The function returns the new bit array.
Time complexity- O(1).
*/
bit_array_t SetOffBitArray(bit_array_t bit_arr, size_t n_bit);

/*
Description- The SetBitBitArray() function set the n_bit to the value 
specified (0 or 1).
Return Value- The function returns the new bit array.
Time complexity- O(1).
*/
bit_array_t SetBitBitArray(bit_array_t bit_arr, size_t n_bit, unsigned int value);

/*
Description- The GetValBitArray() function return the value of the bit in 
the n_bit position.
Return Value- The function returns 0 or 1.
Time complexity- O(1).
*/
unsigned int GetValBitArray(bit_array_t bit_arr, size_t n_bit);

/*
Description- The FlipBitArray() function flip the value of the bit in the 
n_bit position (from 0 to 1 and vice versa).
Return Value- The function returns the new bit array.
Time complexity- O(1).
*/
bit_array_t FlipBitArray(bit_array_t bit_arr, size_t n_bit);

/*
Description- The MirrorBitArray() function mirrors the bit array
Return Value- The function returns the new bit array.
Time complexity- O(1).
*/
bit_array_t MirrorBitArray(bit_array_t bit_arr);

/*
Description- The RotateRightBitArray() function rotates the bit array to
the right n times.
Return Value- The function returns the new bit array.
Time complexity- O(1).
*/
bit_array_t RotateRightBitArray(bit_array_t bit_arr, unsigned int n);

/*
Description- The RotateLeftBitArray() function rotates the bit array to
the left n times.
Return Value- The function returns the new bit array.
Time complexity- O(1).
*/
bit_array_t RotateLeftBitArray(bit_array_t bit_arr, unsigned int n);

/*
Description- The CountOnBitArray() function counts how many set bits there 
are in the bit array.
Return Value- The function returns the count in size_t type.
Time complexity- O(1).
*/
size_t CountOnBitArray(bit_array_t bit_arr);

/*
Description- The CountOffBitArray() function counts how many bits are off 
in the bit array.
Return Value- The function returns the count in size_t type.
Time complexity- O(1).
*/
size_t CountOffBitArray(bit_array_t bit_arr);

/*
Description- The BitArrayToString() function convert the bit array to 
string.
Return Value- The function returns pointer to the start of the string.
Time complexity- O(n).
*/
char *BitArrayToString(bit_array_t bit_arr, char *str);

#endif /* __BIT_ARRAY__ */
