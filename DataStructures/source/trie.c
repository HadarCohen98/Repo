
 /* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       1.0.0                                            *
 ~ Date          06.12.22                                         ~
 ~ Description   Trie implementation                              ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include "include/trie.h"

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

#define BITS_IN_BYTE 8

struct trie_node
{
    int is_full;
    size_t n_bit;
    struct trie_node *children[NUM_CHILDREN];
};

static int GetDirection(const unsigned char ip[BYTES_IN_ARR], size_t n_bit);
static int CreateNode(trie_node_t *node, direction_t direction);
static void UpdateResultIP(unsigned char result[BYTES_IN_ARR], 
                           size_t n_bit,
                           int value);
static void UpdateRequestedIP(unsigned char node_to_insert[BYTES_IN_ARR],
                              size_t n_bit);
static unsigned char SetBitOn(unsigned char byte_to_set, size_t bit_to_set);
static unsigned char SetBitOff(unsigned char byte_to_set, size_t bit_to_set);
static int TrieCountNodes(void *param, void *value);
                           


/* API functions */
trie_node_t *TrieCreate(size_t root_height)
{
    trie_node_t *root = (trie_node_t *)calloc(sizeof(trie_node_t), 1);
    if (NULL == root)
    {
        return NULL;
    }

    root->children[LEFT] = NULL;
    root->children[RIGHT] = NULL;
    root->is_full = 0;
    root->n_bit = root_height;

    return root;
}

void TrieDestroy(trie_node_t *root)
{
    if (NULL != root)
    {
        TrieDestroy(root->children[LEFT]);
        TrieDestroy(root->children[RIGHT]);
        free(root); root = NULL;
    }
}

trie_status_t TrieInsert(trie_node_t *node, 
                         unsigned char node_to_insert[BYTES_IN_ARR],
                         unsigned char result[BYTES_IN_ARR])
{
    direction_t direction = GetDirection(node_to_insert, node->n_bit);
    trie_status_t status = 0;

    if (node->is_full)
    {
        return TRIE_FAILURE;
    }

    if (node->n_bit == (BITS_IN_BYTE * BYTES_IN_ARR))
    {
        node->is_full = 1;
        return TRIE_SUCCESS;
    }

    if (NULL == node->children[direction])
    {
        if (TRIE_FAILURE == CreateNode(node, direction))
        {
            return TRIE_FAILURE;
        }

        UpdateResultIP(result, node->n_bit, direction);
        status = TrieInsert(node->children[direction],
                            node_to_insert,
                            result);
    }

    else
    {
        if (LEFT == direction)
        {
            UpdateResultIP(result, node->n_bit, direction);
            status = TrieInsert(node->children[LEFT],
                                node_to_insert,
                                result);
            if (TRIE_FAILURE == status)
            {
                UpdateRequestedIP(node_to_insert, node->n_bit);
                status = TrieInsert(node,
                                    node_to_insert,
                                    result);
            }
        }

        else 
        {
            UpdateResultIP(result, node->n_bit, direction);
            status = TrieInsert(node->children[RIGHT],
                                node_to_insert,
                                result);
        }
    }

    if ((node->children[LEFT] && (node->children[LEFT]->is_full)) && 
        (node->children[RIGHT] && (node->children[RIGHT]->is_full)))
    {
        node->is_full = 1;
    }

    return status;
}

trie_status_t TrieRemove(trie_node_t *root, 
                         const unsigned char node_to_free[BYTES_IN_ARR])
{
    direction_t direction = 0;
    trie_status_t status = 0;
    
    if (NULL == root)
    {
        return TRIE_NODE_NOT_FOUND;
    }

    direction = GetDirection(node_to_free, root->n_bit);
    if (root->n_bit == (BITS_IN_BYTE * BYTES_IN_ARR - 1))
    {
        if (NULL != root->children[direction])
        {
            free(root->children[direction]); root->children[direction] = NULL;
            return TRIE_SUCCESS;
        }

        return TRIE_FAILURE;
    }

    else
    {
        status = TrieRemove(root->children[direction], node_to_free);

        if ((NULL == root->children[LEFT]) && (NULL == root->children[RIGHT]))
        {
            root->is_full = 0;
            free(root); root = NULL;
        } 
    }
    
    return status;
}

size_t TrieSize(trie_node_t *root)
{
    size_t leaves_counter = 0;
    
    TrieForEach(root, TrieCountNodes, &leaves_counter);
    return leaves_counter;
}


int TrieForEach(trie_node_t *root, 
                   int (*action_func_p)(void *param, void *value),
                   void *param)
{
    int status = 0;

    assert(action_func_p);

    if (NULL != root && 0 == status)
    {
        status = action_func_p(param, (void *)root->n_bit);
        status = TrieForEach(root->children[LEFT], action_func_p, param);
        status = TrieForEach(root->children[RIGHT], action_func_p, param);
    }

    return status;
}


/* Static Functions */
static int GetDirection(const unsigned char ip[BYTES_IN_ARR], size_t n_bit)
{
    unsigned char byte = ip[n_bit / BITS_IN_BYTE];
    unsigned char bit = n_bit % BITS_IN_BYTE;
    return ((byte >> (BITS_IN_BYTE - bit - 1)) & 1);
}

static int CreateNode(trie_node_t *node, direction_t direction)
{
    node->children[direction] = (trie_node_t *)calloc(sizeof(trie_node_t), 1);
    if (NULL == node->children[direction])
    {
        return TRIE_FAILURE;
    }

    node->children[direction]->n_bit = node->n_bit + 1;
    node->children[direction]->children[LEFT] = NULL;
    node->children[direction]->children[RIGHT] = NULL;

    return TRIE_SUCCESS;
}

static void UpdateResultIP(unsigned char result[BYTES_IN_ARR], 
                           size_t n_bit,
                           int value)
{
    unsigned char bit_to_set = BITS_IN_BYTE - (n_bit % BITS_IN_BYTE);
    result[n_bit / BITS_IN_BYTE] = SetBitOff(result[n_bit / BITS_IN_BYTE], bit_to_set - 1) ^ (value << (bit_to_set - 1));
}

static void UpdateRequestedIP(unsigned char node_to_insert[BYTES_IN_ARR],
                              size_t n_bit)
{
    size_t bit_to_set = BITS_IN_BYTE - (n_bit % BITS_IN_BYTE);
    node_to_insert[n_bit / BITS_IN_BYTE] = SetBitOn(node_to_insert[n_bit / BITS_IN_BYTE], bit_to_set - 1);
    ++n_bit;
    while (n_bit < (BITS_IN_BYTE * BYTES_IN_ARR))
    {
        bit_to_set = BITS_IN_BYTE - (n_bit % BITS_IN_BYTE);
        node_to_insert[n_bit / BITS_IN_BYTE] = SetBitOff(node_to_insert[n_bit / BITS_IN_BYTE], bit_to_set - 1);
        ++n_bit;
    }
}

static unsigned char SetBitOn(unsigned char byte_to_set, size_t bit_to_set)
{
    return byte_to_set | (1 << bit_to_set);
}

static unsigned char SetBitOff(unsigned char byte_to_set, size_t bit_to_set)
{
    return byte_to_set & ~(1 << bit_to_set);
}

static int TrieCountNodes(void *param, void *value)
{
    if ((size_t)value == (BYTES_IN_ARR * BITS_IN_BYTE))
    {
	    ++(*(size_t *)param);
    }

	return 0;
}