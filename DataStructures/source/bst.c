 /* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       1.0.0                                            *
 ~ Date          16.11.22                                         ~
 ~ Description   Binary Search Tree Implementation                ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include "include/bst.h"

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

/* definitions */
typedef enum 
{   
    LEFT = 0, 
    RIGHT = 1,
    NUM_CHILDREN = 2
} bst_direction_t;

struct bst_node
{
	bst_node_t *parent;
	bst_node_t *children[NUM_CHILDREN];
	void *value;
};

struct bst
{
	bst_node_t root;
	cmp_func_t cmp_func_p;
};

static int BSTCountNodes(void *param, void *value);
static bst_node_t *BSTIterToNode(bst_iter_t iter);
static bst_iter_t BSTNodeToIter(bst_node_t *node);
static bst_node_t *BSTMoveToChild(bst_node_t *node, 
								  const bst_direction_t direction);
static int BSTIsChildInDirection(const bst_node_t *parent, 
								 const bst_node_t *child, 
								 const bst_direction_t direction);
static void BSTConnectNodes(bst_node_t *position, bst_node_t *new_node, 
							const bst_direction_t direction);
static bst_node_t *BSTFindMinMaxSubTree(bst_node_t *subtree, 
										const bst_direction_t direction);
				
/* API functions */
bst_t *BSTCreate(cmp_func_t cmp_func_p)
{
	bst_t *new_bst = NULL;
		
	assert(cmp_func_p);

	new_bst = (bst_t *)malloc(sizeof(bst_t));
	if (NULL == new_bst)
	{
		return NULL;
	}
	
	new_bst->cmp_func_p = cmp_func_p;
	new_bst->root.parent = NULL;
	new_bst->root.children[LEFT] = NULL;
	new_bst->root.children[RIGHT] = NULL;
	new_bst->root.value = NULL;
	
	return new_bst;
}

void BSTDestroy(bst_t *bst)
{
	assert(bst);
	
	while (!BSTIsEmpty(bst))
	{
		BSTRemove(BSTBegin(bst));
	}	
	
	free(bst); bst = NULL;
}

size_t BSTSize(const bst_t *bst)
{
	size_t size = 0;
	
	assert(bst);
	
	BSTForEach(BSTBegin(bst), BSTEnd(bst), BSTCountNodes, &size);
	return size;
}

int BSTIsEmpty(const bst_t *bst)
{
	assert(bst);
	return (NULL == bst->root.children[LEFT]);
}

bst_iter_t BSTInsert(bst_t *bst, void *value)
{
	bst_node_t *runner = NULL;
	bst_node_t *position = NULL;
	bst_node_t *new_node = NULL;
	bst_direction_t direction = LEFT;
	
	assert(bst);
	
	runner = BSTMoveToChild(BSTIterToNode(BSTEnd(bst)), LEFT);
	position = BSTIterToNode(BSTEnd(bst));
	new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
	if (NULL == new_node)
	{
		return (BSTEnd(bst));
	}
	
	new_node->value = value;	
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	
	while (NULL != runner)
	{
		assert (0 != bst->cmp_func_p(value, runner->value));
		position = runner;
		
		if (bst->cmp_func_p(value, runner->value) > 0)
		{
			direction = RIGHT;
		}
		
		else
		{
			direction = LEFT;
		}
		runner = BSTMoveToChild(runner, direction);
		
	}
	
	BSTConnectNodes(position, new_node, direction);
	
	return BSTNodeToIter(new_node);
}

void BSTRemove(bst_iter_t iter_to_remove)
{
	bst_node_t *to_remove = NULL;	
	int direction = 0;
	bst_node_t *position = NULL;	
	
	assert(iter_to_remove.node);
	
	to_remove = BSTIterToNode(iter_to_remove);
	direction = BSTIsChildInDirection(to_remove->parent, to_remove, RIGHT);
	if (NULL != to_remove->children[RIGHT])
	{
		position = BSTFindMinMaxSubTree(to_remove->children[RIGHT], LEFT);
		BSTConnectNodes(position, to_remove->children[LEFT], LEFT);
		BSTConnectNodes(to_remove->parent, to_remove->children[RIGHT], direction);
	}
	
	else
	{
		BSTConnectNodes(to_remove->parent, to_remove->children[LEFT], direction);
	}
	
	
	free(to_remove); to_remove = NULL;
}

bst_iter_t BSTBegin(const bst_t *bst)
{
	bst_node_t *runner = NULL;
	
	assert(bst);
	
	runner = &(((bst_t *)bst)->root);
	runner = BSTFindMinMaxSubTree(runner, LEFT);
	
	return BSTNodeToIter(runner);
}


bst_iter_t BSTEnd(const bst_t *bst)
{
	assert(bst);
	
	return BSTNodeToIter(&(((bst_t *)bst)->root));
}

bst_iter_t BSTPrev(bst_iter_t iter)
{
	bst_node_t *runner = NULL;
	
	assert(iter.node);
	
	runner = BSTIterToNode(iter);
	
	if (NULL != runner->children[LEFT])
	{
		runner = BSTMoveToChild(runner, LEFT);
		runner = BSTFindMinMaxSubTree(runner, RIGHT);
	}
	
	else
	{
		while (!BSTIsChildInDirection(runner->parent, runner, RIGHT))
		{
			runner = runner->parent;
		}
		runner = runner->parent;
	}
	
	return BSTNodeToIter(runner);
}

bst_iter_t BSTNext(bst_iter_t iter)
{
	bst_node_t *runner = NULL;
	
	assert(iter.node);
	
	runner = BSTIterToNode(iter);

	if (NULL != runner->children[RIGHT])
	{
		runner = BSTMoveToChild(runner, RIGHT);
		runner = BSTFindMinMaxSubTree(runner, LEFT);
	}
	
	else
	{
		while (!BSTIsChildInDirection(runner->parent, runner, LEFT))
		{
			runner = runner->parent;
		}
		runner = runner->parent;
	}
	
	return BSTNodeToIter(runner);
}

int BSTIsSameIter(bst_iter_t iter_1, bst_iter_t iter_2)
{
	return (iter_1.node == iter_2.node);
}

void *BSTGetData(bst_iter_t iter)
{
	assert(iter.node);
	
	return (iter.node->value);
}

bst_iter_t BSTFind(const bst_t *bst, void *data_to_match)
{
	bst_node_t *runner = NULL;
	int iter_found = 0;
	
	assert(bst);
	
	runner = ((bst_t *)bst)->root.children[LEFT];
	
	while (NULL != runner && !iter_found)
	{
		if (bst->cmp_func_p(data_to_match, runner->value) > 0)
		{
			runner = BSTMoveToChild(runner, RIGHT);
		}
		
		else if (bst->cmp_func_p(data_to_match, runner->value) < 0)
		{
			runner = BSTMoveToChild(runner, LEFT);
		}
		
		else
		{
			iter_found = 1;
		}
	}
	
	return (iter_found ? BSTNodeToIter(runner) : BSTEnd(bst));
}

int BSTForEach(bst_iter_t from, bst_iter_t to, action_t action_func, 
			   void *param)
{
	bst_iter_t runner = {0};
	int status = 0;
	
	assert(from.node);
	assert(to.node);
	assert(action_func);
		
	runner = from;
	while (!BSTIsSameIter(to, runner) && 0 == status)
	{
		status = action_func(param, runner.node->value);
		runner = BSTNext(runner);
	}
	
	return status;
}


/* Static Functions */
static int BSTCountNodes(void *param, void *value)
{
	++(*(size_t *)param);
	return 0;
	(void)value;
}

static bst_node_t *BSTIterToNode(bst_iter_t iter)
{
	assert(iter.node);
	return (iter.node);
}

static bst_iter_t BSTNodeToIter(bst_node_t *node)
{
	bst_iter_t return_iter = {0};
	assert(node);
	return_iter.node = node;
	return return_iter;
}

static bst_node_t *BSTMoveToChild(bst_node_t *node, 
								  const bst_direction_t direction)
{
	assert(node);
	return (node->children[direction]);
}

static int BSTIsChildInDirection(const bst_node_t *parent, 
								 const bst_node_t *child, 
								 const bst_direction_t direction)
{
	return (child == parent->children[direction]);
}

static void BSTConnectNodes(bst_node_t *position, bst_node_t *new_node, 
							const bst_direction_t direction)
{
	if (NULL != new_node)
	{
		new_node->parent = position;
	}
	position->children[direction] = new_node;
}

static bst_node_t *BSTFindMinMaxSubTree(bst_node_t *subtree, 
										const bst_direction_t direction)
{
	if (NULL != subtree)
	{
		while (NULL != subtree->children[direction])
		{
			subtree = BSTMoveToChild(subtree, direction);
		}
	}
	
	return subtree;
}
