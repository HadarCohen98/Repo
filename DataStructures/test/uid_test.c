#include <stdio.h> /* printf */

#include "../../utils/colors.h"
#include "include/uid.h"

static int TestAll(void);


int main()
{
	size_t fail_counter = 0;
	
	(0 == TestAll()) ? 1 : ++fail_counter;
	
	(0 == fail_counter) ? printf(YEL "All tests passed successfuly :)\n" RESET) : printf(RED ":(\n" RESET); 
	return 0;
}

static int TestAll(void)
{
	int status = 0;
	uid_ty test_uid_1 = UIDCreate();
	uid_ty test_uid_2 = UIDCreate();
	
	(0 == UIDIsEqual(test_uid_1, g_bad_uid)) ? 1 : (printf(RED "TestAll failed in line %d\n" RESET, __LINE__ ), ++status);
	(0 == UIDIsEqual(test_uid_1, test_uid_2)) ? 1 : (printf(RED "TestAll failed in line %d\n" RESET, __LINE__ ), ++status);
	(1 == UIDIsEqual(test_uid_1, test_uid_1)) ? 1 : (printf(RED "TestAll failed in line %d\n" RESET, __LINE__ ), ++status);
	
	return status;	
}



