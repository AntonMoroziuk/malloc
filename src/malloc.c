#include <malloc.h>
#include <utils.h>

static void	*tiny_malloc(size_t size)
{
	t_block_header	cur;

	cur = g_malloc.tiny_malloc;
	while(cur->next)
	{
		if(cur->size >= size && cur->free)
			return(split_block(cur, size));
		cur = cur->next;
	}
	if(cur->size >= size && cur->free)
		return(split_block(cur, size));
	else
		return(new_block(cur, size, g_malloc.tiny_area_end));
}

static void	*small_malloc(size_t size)
{
	t_block_header	cur;

	cur = g_malloc.small_malloc;
	while(cur->next)
	{
		if(cur->size >= size && cur->free)
			return(split_block(cur, size));
		cur = cur->next;
	}
	if(cur->size >= size && cur->free)
		return(split_block(cur, size));
	else
		return(new_block(cur, size, g_malloc.small_area_end));
}

void		*big_malloc(size_t size)
{
	
}

void		*malloc(size_t size)
{
	size = ALIGN(size);
	if(!g_malloc)
		malloc_init();
	if(size <= TINY_MALLOC_MAX_SIZE)
		return(tiny_malloc(size));
	else if(size <= SMALL_MALLOC_MAX_SIZE)
		return(small_malloc(size));
	else
		return(big_malloc(size));
}