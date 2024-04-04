/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       1.0                                             *
 ~ Date          04/12/22                                        ~
 ~ Description   Trie Header                                     ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
#ifndef __TRIE__
#define __TRIE__

#include <stddef.h> /* size_t */

#define BYTES_IN_ARR 4

typedef struct trie_node trie_node_t;

typedef enum
{
    TRIE_SUCCESS = 0,
    TRIE_FAILURE = 1,
    TRIE_NODE_NOT_FOUND = 2
} trie_status_t;

typedef enum
{
    LEFT,
    RIGHT,
    NUM_CHILDREN = 2
} direction_t;


/*--------------------------------------------------------
Params: a size_t number representing the hight of the root.
Return: a pointer to the root of the trie created.
Complexity: O(1) 
*/
trie_node_t *TrieCreate(size_t root_height);



/*--------------------------------------------------------
Params: trie_node_t type pointer to the root of the trie to be destroyed.
Return: None.
Complexity: O(n) 
*/
void TrieDestroy(trie_node_t *root);



/*--------------------------------------------------------
Params: A pointer to the root of the trie. Requested ip and result ip represented 
        in unsigned char array. If the requested ip is NULL, the requested ip is 
        considered to be all zeroes. 
Return: SUCCESS on success and FAILURE if the allocation fails.
Complexity: O(lon(n))
*/
trie_status_t TrieInsert(trie_node_t *node, 
                         unsigned char node_to_insert[BYTES_IN_ARR],
                         unsigned char result[BYTES_IN_ARR]);



/*--------------------------------------------------------
Params: A pointer to the root of the trie and an unsigned char array representing 
        the node to be freed. 
Return: SUCCESS on success and IP_NOT_FOUND if ip wasn't found.
Complexity: O(lon(n))
*/
trie_status_t TrieRemove(trie_node_t *root, 
                         const unsigned char node_to_free[BYTES_IN_ARR]);


/*--------------------------------------------------------
Params: A pointer to the root of the trie.
Return: The number of leaves in the trie.
Complexity: O(lon(n))
*/
size_t TrieSize(trie_node_t *root);

/*--------------------------------------------------------
	Params: trie_node_t type ptr to the root of the trie, 
            function pointer to the action to perform and 
            void pointer to the parameter to use in the action.
	Return: success or failure status of the action_func_p function;
	Complexity: O(n).
*/
int TrieForEach(trie_node_t *root, 
                   int (*action_func_p)(void *param, void *value),
                   void *param);



#endif /* __TRIE__ */
