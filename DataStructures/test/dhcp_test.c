
#include <stdio.h> /* printf */

#include "../../utils/utilities.h"
#include "include/dhcp.h"	

int TestCreateDestroy(void);
int TestAllocate(void);
int TestFree(void);
int TestCountFree(void);


int main()
{
	size_t fail_counter = 0;
	
	(0 == TestCreateDestroy()) ? 1 : ++fail_counter;
	(0 == TestAllocate()) ? 1 : ++fail_counter;
	(0 == TestFree()) ? 1 : ++fail_counter;
	(0 == TestCountFree()) ? 1 : ++fail_counter;
	
	(0 == fail_counter) ? printf(YEL "All tests passed successfuly :)\n" RESET) 
	: printf(RED ":(\n" RESET); 
	return 0;
}


int TestCreateDestroy(void)
{
	int status = 0;
	unsigned char network_add[BYTES_IN_IP] = {192,168,20,0};
	size_t num_bits_in_subnet = 24;
	dhcp_t *dhcp = DHCPCreate(network_add, num_bits_in_subnet); 
	if (NULL == dhcp)
	{
		printf(RED "TestCreate failed in line %d\n" RESET, __LINE__ );
		printf(RED "actual value return value is null\n" RESET); 
		++status;
	} 
	
	DHCPDestroy(dhcp);
	printf("DO NOT FORGET TO CHECK VLG\n");

	return status;	
}

int TestAllocate(void)
{
	int status = 0;
	unsigned char network_add[BYTES_IN_IP] = {192,168,20,0};
	size_t num_bits_in_subnet = 24;
	dhcp_t *dhcp = DHCPCreate(network_add, num_bits_in_subnet); 
	
	unsigned char requested_ip1[BYTES_IN_IP] = {192,168,20,80};
	unsigned char requested_ip2[BYTES_IN_IP] = {192,168,20,12};
	unsigned char requested_ip3[BYTES_IN_IP] = {192,168,20,255};
	unsigned char requested_ip4[BYTES_IN_IP] = {0};
	unsigned char requested_ip5[BYTES_IN_IP] = {192,168,20,14};
	
	unsigned char result_ip[BYTES_IN_IP] = {0,0,0,0};
	
	status_t return_value = DHCPAllocateIP(dhcp, requested_ip1, result_ip);
	if (SUCCESS != return_value)
	{
		printf(RED "TestAllocate failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET, return_value); 
		++status;
	} 
	
	if (requested_ip1[BYTES_IN_IP - 1] != result_ip[BYTES_IN_IP - 1])
	{
		printf(RED "TestAllocate failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- %c, actual value- %c\n" RESET, requested_ip1[BYTES_IN_IP - 1], result_ip[BYTES_IN_IP - 1]); 
		++status;
	}

	return_value = DHCPAllocateIP(dhcp, requested_ip2, result_ip);
	if (SUCCESS != return_value)
	{
		printf(RED "TestAllocate failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET, return_value); 
		++status;
	} 
	
	if (requested_ip2[BYTES_IN_IP - 1] != result_ip[BYTES_IN_IP - 1])
	{
		printf(RED "TestAllocate failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- %c, actual value- %c\n" RESET, requested_ip2[BYTES_IN_IP - 1], result_ip[BYTES_IN_IP - 1]); 
		++status;
	}

	return_value = DHCPAllocateIP(dhcp, requested_ip2, result_ip);
	if (SUCCESS != return_value)
	{
		printf(RED "TestAllocate failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET, return_value); 
		++status;
	} 
	
	if ((requested_ip2[BYTES_IN_IP - 1] + 1) != result_ip[BYTES_IN_IP - 1])
	{
		printf(RED "TestAllocate failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- %c, actual value- %c\n" RESET, (requested_ip2[BYTES_IN_IP - 1] + 1), result_ip[BYTES_IN_IP - 1]); 
		++status;
	}

	return_value = DHCPAllocateIP(dhcp, requested_ip2, result_ip);
	if (SUCCESS != return_value)
	{
		printf(RED "TestAllocate failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET, return_value); 
		++status;
	} 
	
	if ((requested_ip2[BYTES_IN_IP - 1] + 2) != result_ip[BYTES_IN_IP - 1])
	{
		printf(RED "TestAllocate failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- %c, actual value- %c\n" RESET, (requested_ip2[BYTES_IN_IP - 1] + 2), result_ip[BYTES_IN_IP - 1]); 
		++status;
	}

	return_value = DHCPAllocateIP(dhcp, requested_ip3, result_ip);
	if (FAILURE != return_value)
	{
		printf(RED "TestAllocate failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %d\n" RESET, return_value); 
		++status;
	} 
	
	return_value = DHCPAllocateIP(dhcp, requested_ip4, result_ip);
	if (SUCCESS != return_value)
	{
		printf(RED "TestAllocate failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET, return_value); 
		++status;
	} 
	
	if (1 != result_ip[BYTES_IN_IP - 1])
	{
		printf(RED "TestAllocate failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %c\n" RESET, result_ip[BYTES_IN_IP - 1]); 
		++status;
	}

	return_value = DHCPAllocateIP(dhcp, requested_ip5, result_ip);
	if (SUCCESS != return_value)
	{
		printf(RED "TestAllocate failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET, return_value); 
		++status;
	} 
	
	if (15 != result_ip[BYTES_IN_IP - 1])
	{
		printf(RED "TestAllocate failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %c\n" RESET, result_ip[BYTES_IN_IP - 1]); 
		++status;
	}


	DHCPDestroy(dhcp);
	return status;	
}

int TestFree(void)
{
	int status = 0;
	unsigned char network_add[BYTES_IN_IP] = {192,168,20,0};
	size_t num_bits_in_subnet = 24;
	dhcp_t *dhcp = DHCPCreate(network_add, num_bits_in_subnet); 
	status_t return_value = 0;

	unsigned char requested_ip1[BYTES_IN_IP] = {192,168,20,80};
	unsigned char free_fail_ip[BYTES_IN_IP] = {192,168,20,250};
	
	unsigned char result_ip[BYTES_IN_IP] = {0,0,0,0};
	
	DHCPAllocateIP(dhcp, requested_ip1, result_ip);
	return_value = DHCPFreeIP(dhcp, result_ip);
	if (SUCCESS != return_value)
	{
		printf(RED "TestFree failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET, return_value); 
		++status;
	} 

	return_value = DHCPAllocateIP(dhcp, requested_ip1, result_ip);
	if (SUCCESS != return_value)
	{
		printf(RED "TestFree failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET, return_value); 
		++status;
	} 
	
	if ((requested_ip1[BYTES_IN_IP - 1]) != result_ip[BYTES_IN_IP - 1])
	{
		printf(RED "TestFree failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- %c, actual value- %c\n" RESET, requested_ip1[BYTES_IN_IP - 1], result_ip[BYTES_IN_IP - 1]); 
		++status;
	}

	return_value = DHCPFreeIP(dhcp, free_fail_ip);
	if (IP_NOT_FOUND != return_value)
	{
		printf(RED "TestFree failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 2, actual value- %d\n" RESET, return_value); 
		++status;
	} 
	
	
	DHCPDestroy(dhcp);
	return status;	
}

int TestCountFree(void)
{
	int status = 0;
	unsigned char network_add[BYTES_IN_IP] = {192,168,20,0};
	size_t num_bits_in_subnet = 24;
	dhcp_t *dhcp = DHCPCreate(network_add, num_bits_in_subnet); 

	unsigned char requested_ip1[BYTES_IN_IP] = {192,168,20,80};	
	unsigned char result_ip[BYTES_IN_IP] = {0,0,0,0};
	
	if (253 != DHCPCountFree(dhcp))
	{
		printf(RED "TestCountFree failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 253, actual value- %ld\n" RESET, DHCPCountFree(dhcp)); 
		++status;
	} 

	DHCPAllocateIP(dhcp, requested_ip1, result_ip);
	if (252 != DHCPCountFree(dhcp))
	{
		printf(RED "TestCountFree failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 252, actual value- %ld\n" RESET, DHCPCountFree(dhcp)); 
		++status;
	} 
	
	DHCPFreeIP(dhcp, result_ip);
	if (253 != DHCPCountFree(dhcp))
	{
		printf(RED "TestCountFree failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 253, actual value- %ld\n" RESET, DHCPCountFree(dhcp)); 
		++status;
	}
	
	DHCPDestroy(dhcp);
	return status;	
}
