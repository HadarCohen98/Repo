
 /* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       0.0.1                                            *
 ~ Date          23.10.22                                         ~
 ~ Description   UID impl                                         ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
#include "include/uid.h"

#include <ifaddrs.h> /* getifaddrs */
#include <arpa/inet.h>  /* inet_ntoa */
#include <string.h> /* strncmp, memcpy */

static int GetIPAddress(char *ip_address);

const uid_ty g_bad_uid = {0,0,0,{'#','#','#','#','#','#','#','#','#','#','#','#','#','#'}};

uid_ty UIDCreate(void)
{
	uid_ty new_uid = g_bad_uid;
	static size_t counter = 0;
	
	time(&new_uid.time);
	if (-1 == new_uid.time)
	{
		return g_bad_uid;
	}
	
	if (1 == GetIPAddress(new_uid.ip_address))
	{
		return g_bad_uid;
	}
	
	new_uid.pid = getpid();
	++counter;
	new_uid.counter = counter;
	
	return new_uid;
}

int UIDIsEqual(uid_ty uid_1, uid_ty uid_2)
{
	int status = 0;
	
	status += !(uid_1.pid == uid_2.pid);
	status += !(0 == difftime(uid_1.time, uid_2.time));
	status += !(uid_1.counter == uid_2.counter);
	status += !(0 == strncmp(uid_1.ip_address, uid_2.ip_address, 14));
	
	return (0 == status);
}

static int GetIPAddress(char *ip_address)
{
	struct ifaddrs *ifap, *ifa;
	struct sockaddr_in *s_addr;
	int status = 0;

	if (-1 == getifaddrs(&ifap))
	{
		char *invalid_adderss = "##############";
		memcpy(ip_address, invalid_adderss, 14);
		status = 1;
	}

	else
	{
		for (ifa = ifap; (ifa->ifa_addr && AF_INET != ifa->ifa_addr->sa_family);
			 ifa = ifa->ifa_next)
		{
			/* do nothing */
		}

		s_addr = (struct sockaddr_in *) ifa->ifa_addr;
		memcpy(ip_address, inet_ntoa(s_addr->sin_addr), 14);
	}
	
	freeifaddrs(ifap);
	return status;
}
