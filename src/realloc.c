/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 17:36:52 by amoroziu          #+#    #+#             */
/*   Updated: 2020/02/02 15:21:43 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "utils.h"

static int	valid(void *ptr)
{
	t_block_header	*temp;

	if (!ptr)
		return (0);
	if (!(ptr >= g_malloc.tiny_area && ptr < g_malloc.tiny_area_end) &&
		!(ptr >= g_malloc.small_area && ptr < g_malloc.small_area_end) &&
		!is_big(ptr))
		return (0);
	temp = (t_block_header *)((char*)ptr - HEADER_SIZE);
	if (temp->magic != temp)
		return (0);
	return (1);
}

void		*realloc(void *ptr, size_t size)
{
	t_block_header	*temp;
	size_t			new_size;
	char			*new_ptr;

	if (ptr == NULL)
		return (malloc(size));
	if (valid(ptr))
	{
		size = ALIGN(size);
		temp = (t_block_header *)((char*)ptr - HEADER_SIZE);
		if (temp->size >= size)
		{
			temp->used = size;
			return (ptr);
		}
		new_size = size > temp->size ? temp->size : size;
		new_ptr = (char*)malloc(size);
		if (new_ptr == NULL)
			return (NULL);
		ft_memmove(new_ptr, ptr, new_size);
		free(temp->data);
		return (new_ptr);
	}
	return (NULL);
}
