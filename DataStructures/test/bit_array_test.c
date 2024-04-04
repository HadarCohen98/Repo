#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */

#include "../include/bit_array.h"

int main()
{
	bit_array_t test_a = {0};
	bit_array_t test_b = {3}; 
	bit_array_t test_c = {1};
	bit_array_t test_d = {5};
	bit_array_t test_e = {2};
	bit_array_t test_f = {123456};
	bit_array_t test_g = {1125899906842624};
	char test_str[65]; 
		
	printf("-----------SetAllBitArray-----------\n");
	(SetAllBitArray() + 1 == 0) ? printf("SUCCESS\n") : printf("FAILURE\n");
	
	printf("-----------ResetAllBitArray-----------\n");
	(ResetAllBitArray() == 0) ? printf("SUCCESS\n") : printf("FAILURE\n");
	
	printf("-----------SetOnBitArray-----------\n");
	(SetOnBitArray(test_b, 2) == 7) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(SetOnBitArray(test_b, 10) == 1027) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(SetOnBitArray(test_a, 0) == 1) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(SetOnBitArray(test_a, 50) == 1125899906842624) ? printf("SUCCESS\n") : printf("FAILURE\n");
	
	printf("-----------SetOffBitArray-----------\n");
	(SetOffBitArray(test_a, 10) == 0) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(SetOffBitArray(test_b, 1) == 1) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(SetOffBitArray(test_f, 15) == 90688) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(SetOffBitArray(test_g, 50) == 0) ? printf("SUCCESS\n") : printf("FAILURE\n");
	
	printf("-----------SetBitBitArray-----------\n");
	(SetBitBitArray(test_c, 2, 1) == 5) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(SetBitBitArray(test_c, 10, 1) == 1025) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(SetBitBitArray(test_g, 50, 0) == 0) ? printf("SUCCESS\n") : printf("FAILURE\n");
	
	printf("-----------GetValBitArray-----------\n");
	(GetValBitArray(test_a, 2) == 0) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(GetValBitArray(test_b, 1) == 1) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(GetValBitArray(test_g, 50) == 1) ? printf("SUCCESS\n") : printf("FAILURE\n");

	printf("-----------FlipBitArray-----------\n");
	(FlipBitArray(test_d, 0) == 4) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(FlipBitArray(test_d, 3) == 13) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(FlipBitArray(test_g, 50) == 0) ? printf("SUCCESS\n") : printf("FAILURE\n");
	
	printf("-----------MirrorBitArray-----------\n");
	(test_a == MirrorBitArray(MirrorBitArray(test_a))) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(test_b == MirrorBitArray(MirrorBitArray(test_b))) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(test_g == MirrorBitArray(MirrorBitArray(test_g))) ? printf("SUCCESS\n") : printf("FAILURE\n");
	
	printf("-----------RotateRightBitArray-----------\n");
	(RotateRightBitArray(test_d, 1) == (long unsigned int)-9223372036854775806) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(RotateRightBitArray(test_d, 2) == 4611686018427387905) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(RotateRightBitArray(test_g, 49) == 2) ? printf("SUCCESS\n") : printf("FAILURE\n");
	
	printf("-----------RotateLeftBitArray-----------\n");
	(RotateLeftBitArray(test_c, 1) == 2) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(RotateLeftBitArray(test_e, 63) == 1) ? printf("SUCCESS\n") : printf("FAILURE\n");
	
	printf("-----------CountOnBitArray-----------\n");
	(CountOnBitArray(test_e) == 1) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(CountOnBitArray(test_f) == 6) ? printf("SUCCESS\n") : printf("FAILURE\n");	

	printf("-----------CountOffBitArray-----------\n");
	
	(CountOffBitArray(test_c) == 64-1) ? printf("SUCCESS\n") : printf("FAILURE\n");	
	(CountOffBitArray(test_a) == 64) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(CountOffBitArray(~0) == 0) ? printf("SUCCESS\n") : printf("FAILURE\n");
	
	printf("-----------BitArrayToString-----------\n");
	printf("%s\n", BitArrayToString(test_f, test_str));
	printf("%s\n", BitArrayToString(test_e, test_str));
	printf("%s\n", BitArrayToString(test_g, test_str));

	/* ------------- LUT IMPLEMENTATIONS TESTS ----------------- 
	printf("-----------MirrorBitArrayLut-----------\n");
	(test_a == MirrorBitArrayLut(MirrorBitArrayLut(test_a))) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(test_b == MirrorBitArrayLut(MirrorBitArrayLut(test_b))) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(test_g == MirrorBitArrayLut(MirrorBitArrayLut(test_g))) ? printf("SUCCESS\n") : printf("FAILURE\n");
	
	printf("-----------CountOnBitArrayLut-----------\n");
	(CountOnBitArrayLut(test_e) == 1) ? printf("SUCCESS\n") : printf("FAILURE\n");
	(CountOnBitArrayLut(test_f) == 6) ? printf("SUCCESS\n") : printf("FAILURE\n");	*/
	return 0;
}





