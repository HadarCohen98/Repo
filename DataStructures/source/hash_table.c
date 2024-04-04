
 /* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       1.0.0                                            *
 ~ Date          28.11.22                                         ~
 ~ Description   Hash Table Implementation                        ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include "include/hash_table.h"
#include "include/dll.h"

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

typedef struct key_value 
{
    void *key;
    void *value;
} pair_t;

struct hash_table
{
    size_t hash_table_size;
    hash_func_t hash_func_p;
    is_match_func_t is_match_func_p;
    dll_t **buckets;
};

typedef struct 
{
    void *key;
    is_match_func_t is_match_func;
} is_match_wrapper_t;

typedef struct 
{
    void *param;
    action_t action_func;
} action_func_wrapper_t;

static int HashTableDestroyPair(void *param, void *node_value);
static int HashTableCountPairs(void *param, void *value);
static size_t HashTableGetBucketIndex(hash_table_t *table, const void *key);
static int HashTableIsKeyMatch(void *key_and_is_match_wrapper, 
                               void *pair_key_value);

static dll_iterator_t HashTableFindUsingKey(const hash_table_t *table,
                                       size_t index,
                                       const void *key);

static int HashTableActionFuncValue(void *param_and_action_wrapper, 
                                    void *pair_key_value);



/* API Functions */
hash_table_t *HashTableCreate(size_t capacity, 
                              hash_func_t hash_func_p, 
                              is_match_func_t is_match_func_p)
{
    hash_table_t *table = NULL;
    size_t i = 0; 
    
    assert(capacity > 0);
    assert(hash_func_p);
    assert(is_match_func_p);
    
    table = (hash_table_t *)malloc(sizeof(hash_table_t));
    if (NULL == table)
    {
        return NULL;
    }
    

    table->buckets = malloc(sizeof(dll_t *) * capacity); 
    if (NULL == table->buckets)
    {
        free(table->buckets); table->buckets = NULL;
        return NULL;
    }

    table->hash_table_size = capacity;
    table->hash_func_p = hash_func_p;
    table->is_match_func_p = is_match_func_p;
    
    for (i = 0; i < capacity; ++i)
    {
        table->buckets[i] = DListCreate();
        if (NULL == table->buckets[i])
        {
            size_t j = 0;
            for (; i < j + 1; ++j)
            {
                DListDestroy(table->buckets[j]); table->buckets[j] = NULL;
            }

            free(table->buckets); table->buckets = NULL;
            free(table); table = NULL;
            return NULL;
        }
    }

    return table;
}

void HashTableDestroy(hash_table_t *table)
{
    size_t i = 0;

    assert(table);

        
    for (; i < table->hash_table_size; ++i)
    {
        if (NULL != table->buckets[i])
        {
            DListForEach(DListIteratorFirst(table->buckets[i]), 
                         DListIteratorEnd(table->buckets[i]),
                         HashTableDestroyPair, 
                         NULL);
            
        
            DListDestroy(table->buckets[i]); table->buckets[i] = NULL;
        }
    }
    
    free(table->buckets); table->buckets = NULL;
    free(table); table = NULL;
}

status_t HashTableRemove(hash_table_t *table, const void *key)
{
    size_t found_bucket = 0;
    dll_iterator_t iter_to_remove = 0;

    assert(table);
    
    found_bucket = HashTableGetBucketIndex(table, key);

    iter_to_remove = HashTableFindUsingKey(table, found_bucket, key);

    if (DListIsIterEqual(iter_to_remove, 
                         DListIteratorEnd(table->buckets[found_bucket])))
    {
        return FAILURE;
    }

    HashTableDestroyPair(NULL, (pair_t *)DListGetValue(iter_to_remove));
    DListRemove(iter_to_remove); iter_to_remove = NULL;

    return SUCCESS;
}

status_t HashTableInsert(hash_table_t *table, 
                         const void *key, 
                         void *value)

{
    pair_t *pair = NULL;
    size_t found_bucket = 0;
    dll_iterator_t insert_status = 0;

    assert(table);

    pair = (pair_t *)malloc(sizeof(pair_t));
    if (NULL == pair)
    {
        return MEMORY_ALLOCATION_ERROR;
    }

    pair->key = (void *)key;
    pair->value = value;

    found_bucket = HashTableGetBucketIndex(table, key);
    insert_status = DListPushFront(table->buckets[found_bucket], pair);
    if (NULL == insert_status)
    {
        free(pair); pair = NULL;
        return MEMORY_ALLOCATION_ERROR;
    }

    return SUCCESS;
}

size_t HashTableSize(const hash_table_t *table)
{
    size_t counter = 0;
    assert(table);

    HashTableForEach((hash_table_t *)table, HashTableCountPairs, &counter);
    
    return counter;
}

int HashTableIsEmpty(const hash_table_t *table)
{
    return (0 == HashTableSize(table));
}

void *HashTableFind(const hash_table_t *table, const void *key)
{
    size_t found_bucket = 0;
    dll_iterator_t found_iter = 0;
    pair_t *found_pair = NULL;

    assert(table);
    
    found_bucket = HashTableGetBucketIndex((hash_table_t *)table, key);

    found_iter = HashTableFindUsingKey(table, found_bucket, key);
    
    if (DListIsIterEqual(found_iter, 
                         DListIteratorEnd(table->buckets[found_bucket])))
	{
		return NULL;
	}

    found_pair = (pair_t *)DListGetValue(found_iter);

    return found_pair->value;
}

int HashTableForEach(hash_table_t *table, 
                     int (*action_func)(void *value, void *param), 
                     void *param)
{
    size_t i = 0;
    int status = 0;
    action_func_wrapper_t wrapper = {0};

    assert(table);
    assert(action_func);

    wrapper.action_func = action_func;
    wrapper.param = param;

    for (i = 0; i < table->hash_table_size && 0 == status; ++i)
    {
        status = DListForEach(DListIteratorFirst(table->buckets[i]), 
                              DListIteratorEnd(table->buckets[i]),
                              HashTableActionFuncValue, 
                              &wrapper);

    }

    return status;
}




/* Static Functions */
static dll_iterator_t HashTableFindUsingKey(const hash_table_t *table, 
                                       size_t index, 
                                       const void *key)
{
    dll_iterator_t found_iter = 0;
    is_match_wrapper_t wrapper = {0};

    assert(table);

    wrapper.is_match_func = table->is_match_func_p;
    wrapper.key = (void *)key;
   
    found_iter = DListFind(DListIteratorFirst(table->buckets[index]), 
                           DListIteratorEnd(table->buckets[index]),
                           HashTableIsKeyMatch,
                           &wrapper);
    return found_iter;
}

static int  HashTableDestroyPair(void *param, void *node_value)
{
    assert(node_value);
    
    free(node_value); node_value = NULL;
    
    return 0;
    (void)param;
}

static int HashTableCountPairs(void *param, void *value)
{
	++(*(size_t *)param);
	
    return 0;
	(void)value;
}

static size_t HashTableGetBucketIndex(hash_table_t *table, const void *key) 
{
    assert(table);

    return (table->hash_func_p(key) % table->hash_table_size);
}

static int HashTableIsKeyMatch(void *key_and_is_match_wrapper, 
                               void *pair_key_value)
{
    is_match_wrapper_t *wrapper = ((is_match_wrapper_t *)key_and_is_match_wrapper);
    pair_t *pair = (pair_t *)pair_key_value;
    return (wrapper->is_match_func(wrapper->key, pair->key));
}

static int HashTableActionFuncValue(void *param_and_action_wrapper, 
                                    void *pair_key_value)
{
    action_func_wrapper_t *wrapper = ((action_func_wrapper_t *)param_and_action_wrapper);
    pair_t *pair = (pair_t *)pair_key_value;
    return (wrapper->action_func(wrapper->param, pair->value));
}


