
 /* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       0.0.1                                            *
 ~ Date          29.09.22                                         ~
 ~ Description   bit array implementation                         ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include "../include/bit_array.h"

#include <limits.h> /* CHAR_BIT */
#include <stdio.h> /* sprintf */
#include <assert.h> /* assert */

#define COMPARISON_BYTES_1 0XAAAAAAAAAAAAAAAA	 
#define COMPARISON_BYTES_2 0XCCCCCCCCCCCCCCCC 	
#define COMPARISON_BYTES_4 0XF0F0F0F0F0F0F0F0 
#define COMPARISON_BYTES_8 0XFF00FF00FF00FF00 	
#define COMPARISON_BYTES_16 0XFFFF0000FFFF0000

#define SELECT_BIT_SINGLE 0x5555555555555555	 
#define SELECT_BIT_TWOS 0x3333333333333333  	
#define SELECT_BIT_FOURS 0x0F0F0F0F0F0F0F0F 
#define SELECT_BIT_EIGTHS 0x00FF00FF00FF00FF00
#define SELECT_FIRST_BIT 0x0101010101010101

#define BIT_ARR_SIZE (sizeof(bit_array_t) * CHAR_BIT)

bit_array_t SetAllBitArray(void)
{
	return (~0lu);
}

bit_array_t ResetAllBitArray(void)
{
	return 0lu;
}

bit_array_t SetOnBitArray(bit_array_t bit_arr, size_t n_bit)
{
	assert(n_bit < 64);
	
	return (bit_arr | ((size_t)1 << n_bit));	
}

bit_array_t SetOffBitArray(bit_array_t bit_arr, size_t n_bit)
{
	assert(n_bit < 64);
	
	return (bit_arr & ~((size_t)1 << n_bit));
}

bit_array_t SetBitBitArray(bit_array_t bit_arr, size_t n_bit,
						   unsigned int value)
{
	assert(n_bit < 64);
	
	return (SetOffBitArray(bit_arr, n_bit)) ^ ((size_t)value << n_bit);
}

unsigned int GetValBitArray(bit_array_t bit_arr, size_t n_bit)
{
	assert(n_bit < 64);
	
	return (SetOnBitArray(bit_arr, n_bit) == bit_arr);
}

bit_array_t FlipBitArray(bit_array_t bit_arr, size_t n_bit)
{
	assert(n_bit < 64);
	
	return (bit_arr ^ ((size_t)1 << n_bit));
}

bit_array_t MirrorBitArray(bit_array_t bit_arr)
{
	bit_arr = ((bit_arr & COMPARISON_BYTES_1) >> 1) | 
			  ((bit_arr & ~COMPARISON_BYTES_1) << 1);
	
	bit_arr = ((bit_arr & COMPARISON_BYTES_2) >> 2) | 
			  ((bit_arr & ~COMPARISON_BYTES_2) << 2); 
	
	bit_arr = ((bit_arr & COMPARISON_BYTES_4) >> 4) | 
			  ((bit_arr & ~COMPARISON_BYTES_4) << 4);
	
	bit_arr = ((bit_arr & COMPARISON_BYTES_8) >> 8) | 
			  ((bit_arr & ~COMPARISON_BYTES_8) << 8);
	
	bit_arr = ((bit_arr & COMPARISON_BYTES_16) >> 16) | 
			  ((bit_arr & ~COMPARISON_BYTES_16) << 16);
	
	bit_arr = (bit_arr >> 32) | (bit_arr << 32); 
	
	return bit_arr;
}

bit_array_t RotateRightBitArray(bit_array_t bit_arr, unsigned int n)
{
	return ((bit_arr >> n) | (bit_arr << (BIT_ARR_SIZE - n)));
}

bit_array_t RotateLeftBitArray(bit_array_t bit_arr, unsigned int n)
{
	return ((bit_arr << n) | (bit_arr >> (BIT_ARR_SIZE - n)));
}

size_t CountOnBitArray(bit_array_t bit_arr)
{
	bit_arr = bit_arr - ((bit_arr >> 1) & SELECT_BIT_SINGLE); 			
	bit_arr = (bit_arr & SELECT_BIT_TWOS) + 
			  ((bit_arr >> 2) & SELECT_BIT_TWOS);
	bit_arr = ((bit_arr + (bit_arr >> 4)) & SELECT_BIT_FOURS);
	
	return ((bit_arr * SELECT_FIRST_BIT) >> 56);
}

size_t CountOffBitArray(bit_array_t bit_arr)
{
	return (CountOnBitArray(~bit_arr));
}

char *BitArrayToString(bit_array_t bit_arr, char *str)
{
	long unsigned int i = 0;
	char *str_runner = str;
	
	assert(NULL != str);
	assert(NULL != str_runner);
	
	for (i = 0; i < BIT_ARR_SIZE; ++i)
	{
		sprintf(str_runner, "%lu", (bit_arr & 1));
		bit_arr >>= 1;
		++str_runner;
	}
		
	return str;
}

