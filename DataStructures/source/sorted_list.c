
 /* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       1.0.0                                            *
 ~ Date          20.10.22                                         ~
 ~ Description   sorted list impl using dll                       ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "include/sorted_list.h"

static sdll_iterator_t SDListFindPosition(sdll_iterator_t from, 
											sdll_iterator_t to, 
											sdll_t *slist, 
											void *param);

#ifndef NDEBUG									
static sdll_iterator_t SDListGetIteratorEnd(sdll_iterator_t iter);
static int SDListIsSameList(sdll_iterator_t from, sdll_iterator_t to);
#endif

struct sdll 
{
    dll_t *list;
    cmp_func_t cmp_func_p;
};

sdll_t *SDListCreate(cmp_func_t cmp_func_p)
{
	sdll_t *new_sdll = (sdll_t *)malloc(sizeof(sdll_t));
	if (NULL == new_sdll)
	{
		return NULL;
	}
	
	assert(cmp_func_p);

	new_sdll->list = DListCreate();
	if (NULL == new_sdll->list)
	{
		free(new_sdll); new_sdll = NULL;
		return NULL;
	}

	new_sdll->cmp_func_p = cmp_func_p;
	
	return new_sdll;
}

void SDListDestroy(sdll_t *slist)
{
	assert(slist);
	
	DListDestroy(slist->list);
	free(slist); slist = NULL;
}

sdll_iterator_t SDListIteratorNext(sdll_iterator_t position)
{
	assert(position);
	
	return DListIteratorNext(position);
}

sdll_iterator_t SDListIteratorPrev(sdll_iterator_t position)
{
	assert(position);
	
	return DListIteratorPrev(position);
}

sdll_iterator_t SDListIteratorFirst(const sdll_t *slist)
{
	assert(slist);
	
	return DListIteratorFirst(slist->list);
}

sdll_iterator_t SDListIteratorEnd(const sdll_t *slist)
{
	assert(slist);
	
	return DListIteratorEnd(slist->list);
}

sdll_iterator_t SDListInsert(sdll_t *slist, void *value)
{
	dll_iterator_t found_position = NULL;
	
	assert(slist);
	
	found_position = SDListFindPosition(SDListIteratorFirst(slist),
										SDListIteratorEnd(slist), 
										slist, value);
								
	return (DListInsertBefore(found_position, value));
}

void *SDListPopFront(sdll_t *slist)
{
	assert(slist);
	
	return (DListPopFront(slist->list));
}

void *SDListPopBack(sdll_t *slist)
{
	assert(slist);
	
	return (DListPopBack(slist->list));
}

sdll_iterator_t SDListRemove(sdll_iterator_t position_to_remove)
{
	assert(position_to_remove);
	
	return (DListRemove(position_to_remove));
}

void *SDListGetValue(sdll_iterator_t position)
{
	assert(position);
	
	return (DListGetValue(position));
}

int SDListIsIterEqual(sdll_iterator_t iterator_1, sdll_iterator_t iterator_2)
{
	assert(iterator_1);
	assert(iterator_2);
		
	return (DListIsIterEqual(iterator_1, iterator_2));
}

size_t SDListSize(const sdll_t *slist)
{
	assert(slist);
	
	return (DListSize(slist->list));
}

int SDListIsEmpty(const sdll_t *slist)
{
	assert(slist);
	
	return (DListIsEmpty(slist->list));
}

int SDListForEach(sdll_iterator_t from, sdll_iterator_t to, 
				  action_t action_function_ptr, void *param)
{
	assert(from);
	assert(to);
	assert(action_function_ptr);
	
	#ifndef NDEBUG
	assert(SDListIsSameList(from, to));
	#endif
	
	return (DListForEach(from, to, action_function_ptr, param));
}

sdll_iterator_t SDListFindIf(sdll_iterator_t from, sdll_iterator_t to,
							 is_match_t is_match_function_ptr, void *param)
{
	assert(from);
	assert(to);
	assert(is_match_function_ptr);

	#ifndef NDEBUG
	assert(SDListIsSameList(from, to));
	#endif
	
	return (DListFind(from, to, is_match_function_ptr, param));
}

void SDListSMerge(sdll_iterator_t from, sdll_iterator_t to, sdll_t *slist)
{
	sdll_iterator_t from_runner = NULL;
	sdll_iterator_t to_runner = NULL;
	sdll_iterator_t list_position = NULL;

	assert(from);
	assert(to);
	assert(slist);
	
	#ifndef NDEBUG
	assert(SDListIsSameList(from, to));
	#endif
	
	from_runner = from;
	to_runner = from;
	list_position = SDListIteratorFirst(slist);
	
	while (!SDListIsIterEqual(to_runner, to))
	{
		list_position = SDListFindPosition(list_position,
										   SDListIteratorEnd(slist),
										   slist,
										   SDListGetValue(from_runner)); 
										   
		if (!SDListIsIterEqual(SDListIteratorEnd(slist), list_position))
		{ 
			to_runner = SDListFindPosition(from_runner,
										   to,
										   slist,
										   SDListGetValue(list_position)); 
		}
		
		else
		{
			to_runner = to; 
		}
		
		DListSplice(from_runner, to_runner, list_position);
		from_runner = to_runner;
	}

}			

sdll_iterator_t SDListFind(sdll_iterator_t from, sdll_iterator_t to, sdll_t *slist, void *param)
{
	sdll_iterator_t find_value = NULL;

	assert(from);
	assert(to);
	assert(slist);

	#ifndef NDEBUG
	assert(SDListIsSameList(from, to));
	#endif
		
	find_value = from;
		
	while (!SDListIsIterEqual(find_value, to))
	{
		if (0 == slist->cmp_func_p(param, SDListGetValue(find_value)))
		{
		    return find_value;
		}
		
		find_value = DListIteratorNext(find_value);
	}

	return to;


}

static sdll_iterator_t SDListFindPosition(sdll_iterator_t from, 
											sdll_iterator_t to, 
											sdll_t *slist, 
											void *param)
{
	assert(from);
	assert(to);
	assert(slist);

	#ifndef NDEBUG
	assert(SDListIsSameList(from, to));
	#endif
	
	while (0 == SDListIsIterEqual(from, to) && 
			0 <= slist->cmp_func_p(param, DListGetValue(from)))
	{
		from = DListIteratorNext(from);
	}
	return from;
}

static sdll_iterator_t SDListGetIteratorEnd(sdll_iterator_t iter)
{
	while (NULL != SDListIteratorNext(iter))
	{
		iter = SDListIteratorNext(iter);
	}
	
	return iter;
}

static int SDListIsSameList(sdll_iterator_t from, sdll_iterator_t to)
{
	return (SDListIsIterEqual(SDListGetIteratorEnd(from), SDListGetIteratorEnd(to)));
}

