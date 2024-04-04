#include "../../utils/utilities.h"
#include "include/hash_table.h"

#include <stdio.h> /* printf */
#include <string.h> /* strcmp, strlen */
#include <stdlib.h> /* malloc, free */
#include <ctype.h> /* tolower */

#define CAPACITY 10
static size_t IntHashFunc(const void *key);
static size_t CharHashFunc(const void *key);
static int IntIsMatchFunc(const void *param, const void *value);
static int CharIsMatchFunc(const void *param, const void *value);
static int IsLengthLessThanFive(void *value, void *param);
int HashTableSpellChecker(const hash_table_t *dictionary, const char *word);
int FreeString(void *param, void *value);


int TestCreateDestroy(void);
int TestInsert(void);
int TestRemove(void);
int TestSizeIsEmpty(void);
int TestFind(void);
int TestForEach(void);
void TestSpellChecker(void);

int main()
{
	size_t fail_counter = 0;
	
	(0 == TestCreateDestroy()) ? 1 : ++fail_counter;
	(0 == TestInsert()) ? 1 : ++fail_counter;
	(0 == TestRemove()) ? 1 : ++fail_counter;
	(0 == TestSizeIsEmpty()) ? 1 : ++fail_counter;
	(0 == TestFind()) ? 1 : ++fail_counter;
	(0 == TestForEach()) ? 1 : ++fail_counter;

	printf("CHECK VLG\n");
	(0 == fail_counter) ? printf(YEL "All tests passed successfuly :)\n" RESET) 
	: printf(RED ":(\n" RESET); 

	printf("Spell Checker Test- \nEnter a word:\n");	
	TestSpellChecker();
	return 0;
}

int TestCreateDestroy(void)
{
	int status = 0;
	hash_table_t *table = HashTableCreate(CAPACITY, 
										  IntHashFunc, 
										  IntIsMatchFunc);
	if (NULL == table)
	{
		printf(RED "TestCreateDestroy failed in line %d\n" RESET, __LINE__ );
		printf(RED "The return value is NULL\n" RESET); 
		++status;
	} 
	
	HashTableDestroy(table);
	return status;	
}

int TestInsert(void)
{
	int status = 0;
	hash_table_t *table = HashTableCreate(CAPACITY, 
										  IntHashFunc, 
										  IntIsMatchFunc);
	int key1 = 8284;
	char *value1 = "Hadar"; 

	int key2 = 3960;
	char *value2 = "Mom"; 

	int key3 = 3319;
	char *value3 = "Dad"; 

	if (SUCCESS != HashTableInsert(table, &key1, value1))
	{
		printf(RED "TestInsert failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET, HashTableInsert(table, &key1, &value1)); 
		++status;
	} 

	if (SUCCESS != HashTableInsert(table, &key2, value2))
	{
		printf(RED "TestInsert failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET, HashTableInsert(table, &key2, &value2)); 
		++status;
	} 

	if (SUCCESS != HashTableInsert(table, &key3, value3))
	{
		printf(RED "TestInsert failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET, HashTableInsert(table, &key3, &value3)); 
		++status;
	} 

	HashTableDestroy(table);
	return status;	
}

int TestRemove(void)
{
	int status = 0;
	hash_table_t *table = HashTableCreate(CAPACITY, 
										  IntHashFunc, 
										  IntIsMatchFunc);
	int key1 = 8284;
	char *value1 = "Hadar"; 

	int key2 = 3960;
	char *value2 = "Mom"; 

	int key3 = 3319;
	char *value3 = "Dad"; 

	HashTableInsert(table, &key1, value1);
	HashTableInsert(table, &key2, value2);
	HashTableInsert(table, &key3, value3);

	if (SUCCESS != HashTableRemove(table, &key1))
	{
		printf(RED "TestRemove failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET, HashTableRemove(table, &key1)); 
		++status;
	} 

	if (SUCCESS != HashTableRemove(table, &key3))
	{
		printf(RED "TestRemove failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET, HashTableRemove(table, &key3)); 
		++status;
	}  

	if (SUCCESS != HashTableRemove(table, &key2))
	{
		printf(RED "TestRemove failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET, HashTableRemove(table, &key2)); 
		++status;
	} 

	HashTableDestroy(table);
	return status;	
}

int TestSizeIsEmpty(void)
{
	int status = 0;
	hash_table_t *table = HashTableCreate(CAPACITY, 
										  IntHashFunc, 
										  IntIsMatchFunc);
	int key1 = 8284;
	char *value1 = "Hadar"; 

	int key2 = 3960;
	char *value2 = "Mom"; 

	int key3 = 3319;
	char *value3 = "Dad"; 

	if (0 != HashTableSize(table))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %ld\n" RESET, HashTableSize(table)); 
		++status;
	} 

	if (1 != HashTableIsEmpty(table))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %d\n" RESET, HashTableIsEmpty(table)); 
		++status;
	} 

	HashTableInsert(table, &key1, value1);
	if (1 != HashTableSize(table))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %ld\n" RESET, HashTableSize(table)); 
		++status;
	} 

	if (0 != HashTableIsEmpty(table))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET, HashTableIsEmpty(table)); 
		++status;
	} 

	HashTableInsert(table, &key2, value2);
	HashTableInsert(table, &key3, value3);
	if (3 != HashTableSize(table))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 3, actual value- %ld\n" RESET, HashTableSize(table)); 
		++status;
	} 

	if (0 != HashTableIsEmpty(table))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET, HashTableIsEmpty(table)); 
		++status;
	} 

	HashTableRemove(table, &key3);
	if (2 != HashTableSize(table))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 2, actual value- %ld\n" RESET, HashTableSize(table)); 
		++status;
	} 

	if (0 != HashTableIsEmpty(table))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET, HashTableIsEmpty(table)); 
		++status;
	} 

	HashTableRemove(table, &key2);
	HashTableRemove(table, &key1);
	if (0 != HashTableSize(table))
	{
		printf(RED "TestSize failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %ld\n" RESET, HashTableSize(table)); 
		++status;
	} 

	if (1 != HashTableIsEmpty(table))
	{
		printf(RED "TestIsEmpty failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %d\n" RESET, HashTableIsEmpty(table)); 
		++status;
	} 

	HashTableDestroy(table);
	return status;	
}

int TestFind(void)
{
	int status = 0;
	hash_table_t *table = HashTableCreate(CAPACITY, 
										  IntHashFunc, 
										  IntIsMatchFunc);
	int key1 = 8284;
	char *value1 = "Hadar"; 

	int key2 = 3960;
	char *value2 = "Mom"; 

	int key3 = 3319;
	char *value3 = "Dad"; 

	int key4 = 0000;

	if (NULL != (char *)HashTableFind(table, &value1))
	{
		printf(RED "TestFind failed in line %d\n" RESET, __LINE__ );
		printf(RED "actual value is not NULL\n" RESET); 
		++status;
	} 

	HashTableInsert(table, &key1, value1);
	HashTableInsert(table, &key2, value2);
	HashTableInsert(table, &key3, value3);
	
	if (0 != strcmp(value1, (char *)HashTableFind(table, &key1)))
	{
		printf(RED "TestFind failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- %s, actual value- %s\n" RESET, value1, (char *)HashTableFind(table, &value1)); 
		++status;
	}  

	if (NULL != (char *)HashTableFind(table, &key4))
	{
		printf(RED "TestFind failed in line %d\n" RESET, __LINE__ );
		printf(RED "actual value is not NULL\n" RESET); 
		++status;
	}
	
	HashTableRemove(table, &key1);
	if (NULL != (char *)HashTableFind(table, &key1
	))
	{
		printf(RED "TestFind failed in line %d\n" RESET, __LINE__ );
		printf(RED "actual value is not NULL\n" RESET); 
		++status;
	}

	HashTableDestroy(table);
	return status;	
}

int TestForEach(void)
{
	int status = 0;
	hash_table_t *table = HashTableCreate(CAPACITY, 
										  IntHashFunc, 
										  IntIsMatchFunc);
	int key1 = 8284;
	char *value1 = "Hadar"; 

	int key2 = 3960;
	char *value2 = "Mother"; 

	int key3 = 3319;
	char *value3 = "Dad"; 

	HashTableInsert(table, &key1, value1);
	HashTableInsert(table, &key2, value2);
	HashTableInsert(table, &key3, value3);
	
	if (1 != HashTableForEach(table, IsLengthLessThanFive, NULL))
	{
		printf(RED "TestForEach failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 1, actual value- %d\n" RESET, HashTableForEach(table, IsLengthLessThanFive, NULL)); 
		++status;
	}  

	HashTableRemove(table, &key3);
	if (0 != HashTableForEach(table, IsLengthLessThanFive, NULL))
	{
		printf(RED "TestForEach failed in line %d\n" RESET, __LINE__ );
		printf(RED "wanted value- 0, actual value- %d\n" RESET, HashTableForEach(table, IsLengthLessThanFive, NULL)); 
		++status;
	}  

	HashTableDestroy(table);
	return status;	
}

static void LoadDictionary(hash_table_t *dict)
{
	char *buffer = NULL;
	FILE *fp = fopen("/usr/share/dict/american-english", "r");
	if (NULL == fp)
	{
		printf("problem when opening file\n");
		return;
	}

	buffer = (char *)malloc(sizeof(char) * 80);
	if (NULL == buffer)
	{
		fclose(fp);
		printf("problem when allocating buffer\n");
		return;
	}

	while (NULL != buffer)
	{
		char *curr_word = fgets(buffer, 80, fp);
		char *start_word = curr_word;
		if (NULL == curr_word)
		{
			free(buffer); buffer = NULL;
		}

		else
		{
			while ('\0' != *curr_word && '\n' != *curr_word)
			{
				++curr_word;
			}

			*curr_word = '\0';

			HashTableInsert(dict, start_word, start_word);
			buffer = (char *)malloc(sizeof(char) * 80);
			if (NULL == buffer)
			{
				fclose(fp);
				printf("problem when allocating buffer\n");
				return;
			}
		}
	}

	fclose(fp);
}

void TestSpellChecker(void)
{
	int i = 0;
	int number_of_tests = 5;
	hash_table_t *dict = HashTableCreate(26, CharHashFunc, CharIsMatchFunc);
	LoadDictionary(dict);
	
	for (i = 0; i < number_of_tests; ++i)
	{
		char *input = (char *)malloc(sizeof(char) * 80);
		char *start_input = input;
		if (EOF == scanf("%s", input))
		{
			printf("error with scanf\n");
			return;
		}

		while ('\0' != *input && '\n' != *input)
		{
			++input;
		}

		*input = '\0';

		if (SUCCESS == HashTableSpellChecker(dict, start_input))
		{
			printf("Word is in the dictionary :)\n");
		}
		else
		{
			printf("Word is not in the dictionary :(\n");
		}

		free(start_input);
	}
	
	
	HashTableForEach(dict, FreeString, NULL);
	HashTableDestroy(dict);
}


int HashTableSpellChecker(const hash_table_t *dictionary, const char *word)
{
	return (NULL == HashTableFind(dictionary, word) ? FAILURE : SUCCESS);
}


static int IsLengthLessThanFive(void *param, void *value)
{
	return (strlen((char *)value) >= 5 ? FALSE : TRUE);
	(void)param;
}

static size_t IntHashFunc(const void *key)
{
	return (size_t)(*(int *)key / 1000);
}

static size_t CharHashFunc(const void *key)
{
	char *key_string = (char *)key;
	return ((size_t)(tolower(*key_string)));

}

static int IntIsMatchFunc(const void *param, const void *value)
{
	return ((size_t)value == (size_t)param);
}

static int CharIsMatchFunc(const void *param,const void *value)
{
	return (0 == strcmp(param, value));
}

int FreeString(void *param, void *value)
{
	free(value); value = NULL;
	return SUCCESS;
	(void)param;
}

