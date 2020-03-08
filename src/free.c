/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:23:17 by amoroziu          #+#    #+#             */
/*   Updated: 2020/02/02 15:21:30 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "utils.h"
#include <unistd.h>

static void	defragment_forward(t_block_header *ptr)
{
	t_block_header	*cur;

	cur = ptr->next;
	while (cur)
		if (cur->free)
		{
			ptr->size += HEADER_SIZE + cur->size;
			ptr->next = cur->next;
			cur = cur->next;
		}
		else
			return ;
}

static void	*defragment_backward(t_block_header *ptr)
{
	t_block_header	*cur;
	t_block_header	*tmp;

	cur = ptr->prev;
	tmp = ptr;
	while (cur)
		if (cur->free)
		{
			cur->size += HEADER_SIZE + tmp->size;
			cur->next = tmp->next;
			tmp = cur;
			cur = cur->prev;
		}
		else
			return (cur->next);
	return (tmp);
}

static void	defragment(t_block_header *ptr)
{
	ptr->free = 1;
	ptr->used = 0;
	ptr = defragment_backward(ptr);
	defragment_forward(ptr);
}

static void	free_big(t_block_header *ptr)
{
	t_block_header	*cur;

	cur = g_malloc.big_malloc;
	if (cur == ptr)
		g_malloc.big_malloc = NULL;
	else
	{
		while (cur->next != ptr)
			cur = cur->next;
		cur->next = ptr->next;
		if (ptr->next)
			ptr->next->prev = cur;
	}
	munmap(ptr, ptr->size + HEADER_SIZE);
}

void		free(void *ptr)
{
	t_block_header	*temp;

	if (!(ptr >= g_malloc.tiny_area && ptr < g_malloc.tiny_area_end) &&
		!(ptr >= g_malloc.small_area && ptr < g_malloc.small_area_end) &&
		!is_big(ptr))
		return ;
	temp = (t_block_header *)((char*)ptr - HEADER_SIZE);
	if (temp->magic != temp || temp->free)
		return ;
	if (temp->size > SMALL_MALLOC_MAX_SIZE)
		free_big(temp);
	else
		defragment(temp);
}
