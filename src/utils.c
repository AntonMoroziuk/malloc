#include <utils.h>
#include <stdlib.h>

void	*split_block(t_block_header block, size_t size)
{
	t_block_header	temp;

	if(block->size <= size + HEADER_SIZE + ALIGN(1))
	{
		block->used = size;
		return((void*)block);
	}
	temp = block->data + size;
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
	return((void*)block);
}
void	*new_block(t_block_header last, size_t size, void *max_addr)
{
	t_block_header	temp;

	temp = mmap((void*)((char*)max_addr + 1), NEW_MAPPING_SIZE, PROT_WRITE |
		PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if(temp == MAP_FAILED)
		return (NULL);
	last->next = temp;
	temp->prev = last;
	temp->size = NEW_MAPPING_SIZE;
	temp->magic = temp;
	return(split_block(temp, size));
}
