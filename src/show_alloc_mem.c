/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 18:38:57 by amoroziu          #+#    #+#             */
/*   Updated: 2020/02/01 18:39:00 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		print_byte(int k)
{
	char	c;

	if (k > 9)
		c = 'a' + k - 10;
	else
		c = '0' + k;
	ft_putchar(c);
}

static void		print_content(char *arr, size_t size)
{
	size_t			i;

	i = -1;
	while (++i < size)
	{
		print_byte((unsigned char)arr[i] / 16);
		print_byte((unsigned char)arr[i] % 16);
		if (i % 16 == 15 || i == size - 1)
			ft_putstr("\n");
		else if (i % 2 == 1)
			ft_putstr(" ");
	}
}

static size_t	show_zone(t_block_header *cur, int extended)
{
	size_t			size;

	size = 0;
	while (cur)
	{
		if (!cur->free)
			ft_printf("%X - %X : %lld bytes\n",
			cur->data, cur->data + cur->used, cur->used);
		if (extended)
			print_content(cur->data, cur->used);
		size += cur->used;
		cur = cur->next;
	}
	return (size);
}

void			show_alloc_mem(void)
{
	t_block_header	*cur;
	size_t			total;

	cur = g_malloc.tiny_malloc;
	total = 0;
	ft_printf("TINY : %X\n", cur);
	total += show_zone(cur, 0);
	cur = g_malloc.small_malloc;
	ft_printf("SMALL : %X\n", cur);
	total += show_zone(cur, 0);
	cur = g_malloc.big_malloc;
	ft_printf("LARGE : %X\n", cur);
	total += show_zone(cur, 0);
	ft_printf("Total : %lld bytes\n", total);
}

void			show_alloc_mem_ex(void)
{
	t_block_header	*cur;
	size_t			total;

	cur = g_malloc.tiny_malloc;
	total = 0;
	ft_printf("TINY : %X\n", cur);
	total += show_zone(cur, 1);
	cur = g_malloc.small_malloc;
	ft_printf("SMALL : %X\n", cur);
	total += show_zone(cur, 1);
	cur = g_malloc.big_malloc;
	ft_printf("LARGE : %X\n", cur);
	total += show_zone(cur, 1);
	ft_printf("Total : %lld bytes\n", total);
}
