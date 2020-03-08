/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 17:18:43 by amoroziu          #+#    #+#             */
/*   Updated: 2020/01/05 17:32:23 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdint.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>

# include "../libft/libft.h"

# define TINY_MALLOC_MAX_SIZE 1024
# define SMALL_MALLOC_MAX_SIZE 1048576
# define MIN_NUMBER_OF_ALLOCATIONS 128
# define NEW_MAPPING_SIZE SMALL_MALLOC_MAX_SIZE * 16
# define TINY_START_SIZE TINY_MALLOC_MAX_SIZE * MIN_NUMBER_OF_ALLOCATIONS
# define SMALL_START_SIZE SMALL_MALLOC_MAX_SIZE * MIN_NUMBER_OF_ALLOCATIONS
# define INIT_FAIL -1

# if UINTPTR_MAX == 0xFFFF
#  define PTR16 10
# elif UINTPTR_MAX == 0xFFFFFFFF
#  define PTR32
# else
#  define PTR64
# endif

# ifdef PTR16
#  define ALIGN(x) (((((x) - 1) >> 1) << 1) + 2)
# endif

# ifdef PTR32
#  define ALIGN(x) (((((x) - 1) >> 2) << 2) + 4)
# endif

# ifdef PTR64
#  define ALIGN(x) (((((x) - 1) >> 3) << 3) + 8)
# endif

typedef struct	s_block_header
{
	size_t					size;
	size_t					used;
	struct s_block_header	*next;
	struct s_block_header	*prev;
	void					*magic;
	int						free;
	char					data[1];

}				t_block_header;

typedef struct	s_malloc
{
	t_block_header			*tiny_malloc;
	t_block_header			*small_malloc;
	void					*tiny_area;
	void					*tiny_area_end;
	void					*small_area;
	void					*small_area_end;
	t_block_header			*big_malloc;
}				t_malloc;

t_malloc		g_malloc;

# define HEADER_SIZE (sizeof(size_t) * 2 + sizeof(int) + sizeof(void*) * 3)

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem(void);
void			show_alloc_mem_ex(void);

#endif
