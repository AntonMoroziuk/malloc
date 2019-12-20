#ifndef MALLOC_H
#define MALLOC_H

#include <libft.h>
#include <stdlib.h>
#include <stdint.h>

#if UINTPTR_MAX == 0xFFFF
  #define PTR16
#elif UINTPTR_MAX == 0xFFFFFFFF
  #define PTR32
#else
  #define PTR64

#ifdef PTR16
#define align(x) (((((x) - 1) >> 1) << 1) + 2)
#endif

#ifdef PTR32
#define align(x) (((((x) - 1) >> 2) << 2) + 4)
#endif

#ifdef PTR64
#define align(x) (((((x) - 1) >> 3) << 3) + 8)
#endif

typedef struct	s_block_header
{
	size_t					size;
	struct s_block_header	*next;
	struct s_block_header	*prev;
	void					*magic;
	int						free;
	char					data[1];

}				*t_block_header;

#define HEADER_SIZE sizeof(t_block_header) - sizeof(char*);

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

#endif