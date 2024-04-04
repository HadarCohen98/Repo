/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       1.0                                             *
 ~ Date          04/12/22                                        ~
 ~ Description   UID Header                                      ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
#ifndef __UID__
#define __UID__

#include <unistd.h> /* pid_t */
#include <sys/types.h> /* pid_t */
#include <time.h> /* time */
#include <stddef.h> /* size_t */

 /* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ UID (unique identifier) is a data structure that contain       ~
 * unique information about a proccess.                           /
 / The values that is used to differ between proccess are-        *
 * 1. pid                                                         /
 / 2. time from the begining of the program                       *
 * 3. counter                                                     /
 / 4. ip address of the machine                                   *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */


struct uid
{
	pid_t pid;
	time_t time;
	size_t counter;
	char ip_address[14];
};

typedef struct uid uid_ty;

extern const uid_ty g_bad_uid;

/*
Description- The UIDCreate() function create UID of uid_ty type. To check if the function failed the user will need to compare the UID to the extern variable "g_bad_uid" using the UIDIsEqual() function.
Return Value- The function returns the new UID.
Time Complexity- O(1).
*/
uid_ty UIDCreate(void);

/*
Description- The UIDIsEqual() function check if "uid_1" and "uid_2" is the same UID.
Return Value- The function returns 1 if "uid_1" and "uid_2" is equal and 0 otherwise.
Time Complexity- O(1).
*/
int UIDIsEqual(uid_ty uid_1, uid_ty uid_2);

#endif /* __UID__ */
