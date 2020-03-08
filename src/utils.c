/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 17:33:52 by amoroziu          #+#    #+#             */
/*   Updated: 2020/01/05 17:35:02 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*split_block(t_block_header *block, size_t size)
{
	t_block_header	*temp;

	if (block->size <= size + 2 * HEADER_SIZE + ALIGN(1))
	{
		block->free = 0;
		block->used = size;
		return ((void*)block);
	}
	temp = (t_block_header *)(block->data + size);
	temp->size = block->size - size - HEADER_SIZE;
	temp->used = temp->size;
	temp->next = block->next;
	temp->prev = block;
	temp->free = 1;
	temp->magic = temp;
	block->size = size;
	block->used = size;
	block->next = temp;
	block->free = 0;
	return ((void*)block->data);
}

int		is_big(void *ptr)
{
	t_block_header	*cur;

	cur = g_malloc.big_malloc;
	while (cur)
	{
		if (cur->data == ptr)
			return (1);
		cur = cur->next;
	}
	return (0);
}

void	*new_block(t_block_header *last, size_t size, void *max_addr)
{
	t_block_header	*temp;

	temp = mmap(max_addr, NEW_MAPPING_SIZE, PROT_WRITE |
		PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (temp == MAP_FAILED)
		return (NULL);
	last->next = temp;
	temp->prev = last;
	temp->size = NEW_MAPPING_SIZE - HEADER_SIZE;
	temp->magic = temp;
	if (max_addr == g_malloc.tiny_area_end)
		g_malloc.tiny_area_end = (void*)(temp->data + temp->size);
	else
		g_malloc.small_area_end = (void*)(temp->data + temp->size);
	return (split_block(temp, size));
}

int		malloc_init(void)
{
	t_block_header	*tiny;
	t_block_header	*small;

	tiny = (t_block_header *)mmap(NULL, TINY_START_SIZE,
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	small = (t_block_header *)mmap(NULL, SMALL_START_SIZE,
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (small == MAP_FAILED || tiny == MAP_FAILED)
		return (INIT_FAIL);
	tiny->prev = NULL;
	tiny->next = NULL;
	tiny->size = TINY_START_SIZE - HEADER_SIZE;
	tiny->free = 1;
	small->prev = NULL;
	small->next = NULL;
	small->size = SMALL_START_SIZE - HEADER_SIZE;
	small->free = 1;
	g_malloc.tiny_malloc = tiny;
	g_malloc.small_malloc = small;
	g_malloc.tiny_area = tiny;
	g_malloc.small_area = small;
	g_malloc.tiny_area_end = (void*)((char*)tiny + tiny->size);
	g_malloc.small_area_end = (void*)((char*)small + small->size);
	return (0);
}
