/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 10:22:29 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/20 11:49:28 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*choose_block(const size_t size)
{
	t_heap		*heap;
	t_block		*block;

	block = NULL;
	if ((heap = choose_heap(size)) == NULL)
		return (NULL);
	if ((block = heap->metadata_block) == NULL)
		return (add_block(&heap, size));
	while (block->next != NULL)
	{
		if (block->is_free == TRUE && block->size == size)
		{
			block->is_free = FALSE;
			return (block->ptr);
		}
		block = block->next;
	}
	return (add_block(&heap, size));
}

t_block		*add_block(t_heap **heap, const size_t size)
{
	t_block		*block;
	void		*ptr;

	block = ((*heap)->metadata_block);
	(((*heap)->count))++;
	(((*heap)->free_size)) -= (size + sizeof(t_block));
	if (block == NULL)
	{
		block = (t_block*)((void*)*heap + sizeof(t_heap));
		ptr = ((void*)block + sizeof(t_block));
		*block = (t_block){NULL, NULL, size, FALSE, ptr};
		((*heap)->metadata_block) = block;
		return (block->ptr);
	}
	while (block->next != NULL)
		block = block->next;
	block->next = (t_block*)(block->ptr + block->size);
	ptr = ((void*)block->next + sizeof(t_block));
	*(block->next) = (t_block){block, NULL, size, FALSE, ptr};
	return (block->next->ptr);
}
