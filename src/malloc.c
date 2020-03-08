/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 17:35:12 by amoroziu          #+#    #+#             */
/*   Updated: 2020/02/02 15:21:12 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "utils.h"

extern t_malloc	g_malloc;

static void	*tiny_malloc(size_t size)
{
	t_block_header	*cur;

	cur = g_malloc.tiny_malloc;
	while (cur->next)
	{
		if (cur->size >= size && cur->free)
			return (split_block(cur, size));
		cur = cur->next;
	}
	if (cur->size >= size && cur->free)
		return (split_block(cur, size));
	else
		return (new_block(cur, size, g_malloc.tiny_area_end));
}

static void	*small_malloc(size_t size)
{
	t_block_header	*cur;

	cur = g_malloc.small_malloc;
	while (cur->next)
	{
		if (cur->size >= size && cur->free)
			return (split_block(cur, size));
		cur = cur->next;
	}
	if (cur->size >= size && cur->free)
		return (split_block(cur, size));
	else
		return (new_block(cur, size, g_malloc.small_area_end));
}

static void	*big_malloc(size_t size, size_t alloc_size)
{
	t_block_header	*temp;
	t_block_header	*cur;

	temp = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (temp == MAP_FAILED)
		return (NULL);
	temp->size = alloc_size - HEADER_SIZE;
	temp->used = size;
	temp->next = NULL;
	temp->prev = NULL;
	temp->magic = temp;
	temp->free = 0;
	if (!g_malloc.big_malloc)
		g_malloc.big_malloc = temp;
	else
	{
		cur = g_malloc.big_malloc;
		while (cur->next)
			cur = cur->next;
		cur->next = temp;
		temp->prev = cur;
	}
	return ((void *)temp->data);
}

void		*malloc(size_t size)
{
	int				page_size;
	size_t			alloc_size;

	size = ALIGN(size);
	if (!g_malloc.tiny_malloc || !g_malloc.small_malloc)
		if (malloc_init() == INIT_FAIL)
			return (NULL);
	if (size <= TINY_MALLOC_MAX_SIZE)
		return (tiny_malloc(size));
	else if (size <= SMALL_MALLOC_MAX_SIZE)
		return (small_malloc(size));
	else
	{
		page_size = getpagesize();
		alloc_size = page_size * ((size + HEADER_SIZE) / page_size + 1);
		return (big_malloc(size, alloc_size));
	}
}
