 /* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Hadar Cohen                                      ~
 * Version       1.0.0                                            *
 ~ Date          27.11.22                                         ~
 ~ Description   AVL implementation                               ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include "include/avl.h"
#include "../../utils/utilities.h"

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

 typedef enum 
{   
    LEFT = 0, 
    RIGHT = 1,
    NUM_CHILDREN = 2
} avl_direction_t;

typedef struct avl_node
{
	void *data;
	struct avl_node *children[NUM_CHILDREN];
	size_t height;
} avl_node_t;

struct avl
{
	avl_node_t *root;
	cmp_func_t cmp_func_p;
};

static void AVLDestroyRecursive(avl_node_t *root);
static int AVLCountNodes(void *param, void *value);
static avl_node_t *AVLFindRecursive(avl_node_t *root, 
                                    cmp_func_t cmp_func_p, 
                                    void *data_to_match);
static avl_node_t *AVLInsertRecursive(avl_node_t *root, 
                                      cmp_func_t cmp_func_p, 
                                      void *value, 
                                      status_t *status);
static size_t AVLUpdateHeight(avl_node_t *node);
static size_t AVLGetNodeHeight(avl_node_t *node);
static avl_node_t *AVLCreateNode(void *value, status_t *status);
static int AVLForEachPreOrder(avl_node_t *root, 
                              action_t action_func_p, 
                              void *param);
static int AVLForEachPostOrder(avl_node_t *root, 
                               action_t action_func_p, 
                               void *param);
static int AVLForEachInOrder(avl_node_t *root, 
                             action_t action_func_p, 
                             void *param);
static int AVLForEachPreOrder(avl_node_t *root, 
                              action_t action_func_p, 
                              void *param);
static int AVLForEachPostOrder(avl_node_t *root, 
                               action_t action_func_p, 
                               void *param);
static int AVLForEachInOrder(avl_node_t *root, 
                             action_t action_func_p, 
                             void *param);
static avl_node_t *AVLFindMinSubtree(avl_node_t *subtree);
static avl_node_t *AVLRemoveRecursive(avl_node_t *root, 
                                      cmp_func_t cmp_func_p, 
                                      void *data_to_match, 
                                      status_t *status);
static avl_node_t *AVLRemoveNode(avl_node_t *node);
static avl_node_t *AVLRotateLeft(avl_node_t *node);
static avl_node_t *AVLRotateRight(avl_node_t *node);
static avl_node_t *AVLRebalance(avl_node_t *node);
static int AVLGetBalanceFactor(avl_node_t *node);


/* API Functions */
avl_t *AVLCreate(cmp_func_t cmp_func_p)
{
    avl_t *avl = NULL;
		
	assert(cmp_func_p);

	avl = (avl_t *)malloc(sizeof(avl_t));
	if (NULL == avl)
	{
		return NULL;
	}
	
	avl->cmp_func_p = cmp_func_p;
	avl->root = NULL;
	
	return avl;
}

void AVLDestroy(avl_t *tree)
{
    assert(tree);
    AVLDestroyRecursive(tree->root);
    free(tree); tree = NULL;
}

status_t AVLRemove(avl_t *tree, const void *value)
{
    status_t status = FAILURE;

    assert(tree);
    assert(tree->cmp_func_p);

    tree->root = AVLRemoveRecursive(tree->root, 
                                    tree->cmp_func_p, 
                                    (void *)value, 
                                    &status);
    return status;
}

status_t AVLInsert(avl_t *tree, void *value)
{
    status_t status = SUCCESS;

    assert(tree);
    assert(tree->cmp_func_p);
    
    tree->root = AVLInsertRecursive(tree->root, 
                                    tree->cmp_func_p, 
                                    value, 
                                    &status);
    return status;
}

size_t AVLHeight(const avl_t *tree)
{   
    size_t height = 0;
   
    assert(tree);
    
    return (AVLIsEmpty(tree) ? height : tree->root->height);
}

size_t AVLSize(const avl_t *tree)
{
    size_t size = 0;

    assert(tree);
    
    AVLForEach((avl_t *)tree, AVLCountNodes, &size, PRE_ORDER);
    return size;
}

int AVLIsEmpty(const avl_t *tree)
{
    assert(tree);
    return (NULL == tree->root);
}

void *AVLFind(const avl_t *tree, const void *data_to_match)
{
    avl_node_t *found_node = NULL;

    assert(tree);
    assert(tree->cmp_func_p);

    found_node = AVLFindRecursive(tree->root, 
                                  tree->cmp_func_p, 
                                  (void *)data_to_match);

    return (NULL == found_node ? NULL : found_node->data);
}

int AVLForEach(avl_t *tree, action_t action_func_p, void *param, order_t order)
{
    int status = 0;

    assert(tree);
    assert(action_func_p);

    switch (order)
    {
        case PRE_ORDER:
            status = AVLForEachPreOrder(tree->root, action_func_p, param);
            break;

        case POST_ORDER:
            status = AVLForEachPostOrder(tree->root, action_func_p, param);
            break;

        case IN_ORDER:
            status = AVLForEachInOrder(tree->root, action_func_p, param);
            break;
    }

    return status;
}


/* Static Functions */
static void AVLDestroyRecursive(avl_node_t *root)
{
    if (NULL != root)
    {
        AVLDestroyRecursive(root->children[LEFT]);
        AVLDestroyRecursive(root->children[RIGHT]);
        free(root); root = NULL;
    }
}

static avl_node_t *AVLFindRecursive(avl_node_t *root, 
                                    cmp_func_t cmp_func_p, 
                                    void *data_to_match)
{
    assert(cmp_func_p);

    if (NULL == root)
    {
        return NULL;
    }

    if (0 < cmp_func_p(data_to_match, root->data))
    {
        return AVLFindRecursive(root->children[RIGHT], 
                                cmp_func_p, 
                                data_to_match);
    }

    else if (0 > cmp_func_p(data_to_match, root->data))
    {
        return AVLFindRecursive(root->children[LEFT], 
                                cmp_func_p, 
                                data_to_match);
    }
    
    else
    {
        return root;
    }
}

static avl_node_t *AVLInsertRecursive(avl_node_t *root, 
                                      cmp_func_t cmp_func_p, 
                                      void *value, 
                                      status_t *status)
{
    avl_direction_t direction = LEFT;

    assert(cmp_func_p);

    if (NULL == root)
    {
        return AVLCreateNode(value, status);
    }

    else if (0 < cmp_func_p(value, root->data))
    {
        direction = RIGHT;
    }

    else if (0 > cmp_func_p(value, root->data))
    {
        direction = LEFT;
        
    }
    
    root->children[direction] = AVLInsertRecursive(root->children[direction], 
                                                   cmp_func_p, 
                                                   value, 
                                                   status);
    AVLUpdateHeight(root);
    
    return AVLRebalance(root);
}

static size_t AVLGetNodeHeight(avl_node_t *node)
{
    return (NULL == node ? 0 : node->height);
}

static avl_node_t *AVLCreateNode(void *value, status_t *status)
{
    avl_node_t *new_node = (avl_node_t *)malloc(sizeof(avl_node_t));
    if (NULL == new_node)
    {
        *status = FAILURE;
        return NULL;
    }

    new_node->children[RIGHT] = NULL;
    new_node->children[LEFT] = NULL;
    new_node->data = value;
    new_node->height = 1;

    *status = SUCCESS;
    return new_node;
}

static int AVLForEachPreOrder(avl_node_t *root, 
                              action_t action_func_p, 
                              void *param)
{
    int status = 0;

    assert(action_func_p);

    if (NULL != root && 0 == status)
    {
        status = action_func_p(param, root->data);
        status = AVLForEachPreOrder(root->children[LEFT], action_func_p, param);
        status = AVLForEachPreOrder(root->children[RIGHT], action_func_p, param);
    }

    return status;
}

static int AVLForEachPostOrder(avl_node_t *root, 
                               action_t action_func_p, 
                               void *param)
{
    int status = 0;
    
    assert(action_func_p);

    if (NULL != root && 0 == status)
    {
        status = AVLForEachPostOrder(root->children[LEFT], action_func_p, param);
        status = AVLForEachPostOrder(root->children[RIGHT], action_func_p, param);
        status = action_func_p(param, root->data);
    }

    return status;
}

static int AVLForEachInOrder(avl_node_t *root, 
                             action_t action_func_p, 
                             void *param)
{
    int status = 0;

    assert(action_func_p);

    if (NULL != root && 0 == status)
    {
        status = AVLForEachInOrder(root->children[LEFT], action_func_p, param);
        status = action_func_p(param, root->data);
        status = AVLForEachInOrder(root->children[RIGHT], action_func_p, param);
    }

    return status;
}

static avl_node_t *AVLFindMinSubtree(avl_node_t *subtree)
{
	if (NULL == subtree->children[LEFT])
	{
        return subtree;
	}
	
	return (AVLFindMinSubtree(subtree->children[LEFT]));
}

static avl_node_t *AVLRemoveRecursive(avl_node_t *root, 
                                      cmp_func_t cmp_func_p, 
                                      void *data_to_match, 
                                      status_t *status)
{
    assert(cmp_func_p);

    if (NULL == root)
    {
        return NULL;
    }

    else if (0 < cmp_func_p(data_to_match, root->data))
    {
        root->children[RIGHT] =  AVLRemoveRecursive(root->children[RIGHT], 
                                                    cmp_func_p, 
                                                    data_to_match, 
                                                    status);
    }

    else if (0 > cmp_func_p(data_to_match, root->data))
    {
        root->children[LEFT] =  AVLRemoveRecursive(root->children[LEFT], 
                                                   cmp_func_p, 
                                                   data_to_match, 
                                                   status);
    }
    
    else
    {
        *status = SUCCESS;
        root = AVLRemoveNode(root);
    }  
    
    AVLUpdateHeight(root);
    return AVLRebalance(root);
  
}

static avl_node_t *AVLRemoveNode(avl_node_t *node)
{
	avl_node_t *return_child = NULL;

    assert(node);

	if (NULL == node->children[RIGHT])
	{
		return_child = node->children[LEFT];
	}

	else if (NULL == node->children[LEFT])
	{
		return_child = node->children[RIGHT];
	}

	else
	{
		avl_node_t *position = AVLFindMinSubtree(node->children[RIGHT]);
		position->children[LEFT] = node->children[LEFT];
		position->height = node->children[LEFT]->height + 1;
		return_child = node->children[RIGHT];
	}

    free(node); node = NULL;
    return return_child;
}

static int AVLGetBalanceFactor(avl_node_t *node)
{
    if (NULL == node)
    {
        return 0;
    }

    return (AVLGetNodeHeight(node->children[RIGHT]) - 
            AVLGetNodeHeight(node->children[LEFT]));
}

static avl_node_t *AVLRebalance(avl_node_t *node)
{
    int balance_factor = 0;

    balance_factor = AVLGetBalanceFactor(node);
    
    if (2 == balance_factor)
    {
        balance_factor = AVLGetBalanceFactor(node->children[RIGHT]);
        if (-1 == balance_factor)
        {
            node->children[RIGHT] = AVLRotateRight(node->children[RIGHT]);
            node = AVLRotateLeft(node);
        }
        
        else
        {
            node = AVLRotateLeft(node);
        }
        
    }

    else if (-2 == balance_factor)
    {
        balance_factor = AVLGetBalanceFactor(node->children[LEFT]);
        if (1 == balance_factor)
        {
            node->children[LEFT] = AVLRotateLeft(node->children[LEFT]);
            node = AVLRotateRight(node);
        }
        
        else
        {
            node = AVLRotateRight(node);
        }
    }

    return node;
}

static avl_node_t *AVLRotateLeft(avl_node_t *node)
{
    avl_node_t *right_child = node->children[RIGHT];
    
    node->children[RIGHT] = right_child->children[LEFT];
    right_child->children[LEFT] = node;
    AVLUpdateHeight(node);
    AVLUpdateHeight(right_child);
    
    return right_child;
}

static avl_node_t *AVLRotateRight(avl_node_t *node)
{
    avl_node_t *left_child = node->children[LEFT];
    
    node->children[LEFT] = left_child->children[RIGHT];
    left_child->children[RIGHT] = node;
    AVLUpdateHeight(node);
    AVLUpdateHeight(left_child);
    
    return left_child;
}

static size_t AVLUpdateHeight(avl_node_t *node)
{
    if (NULL == node)
    {
        return 0;
    }

    node->height = 1 + MAX(AVLGetNodeHeight(node->children[LEFT]), 
                           AVLGetNodeHeight(node->children[RIGHT]));

    return node->height;
}

static int AVLCountNodes(void *param, void *value)
{
	++(*(size_t *)param);
	return 0;
	(void)value;
}
