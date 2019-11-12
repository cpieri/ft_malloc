/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 10:22:29 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/12 12:21:18 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block		*choose_block(const size_t size)
{
	t_heap		*heap;
	t_block		*block;

	if ((heap = choose_heap(size)) == NULL)
		if (create_heap(size) == SUCCESS)
			if ((heap = choose_heap(size)) == NULL)
				return (NULL);
	if ((block = heap->metadata_block) == NULL)
		return (add_block(heap->metadata_block, &(heap->count), size));
	while (block->next != NULL)
	{
		if (block->is_free == TRUE && block->size == size)
		{
			block->is_free = FALSE;
			return (block);
		}
		block = block->next;
	}
	return (add_block(heap->metadata_block, &(heap->count), size));
}

t_block		*add_block(const t_block *blocks, size_t *count, size_t size)
{
	t_block		*block;

	block = (t_block*)blocks;
	while (block->next != NULL)
		block = block->next;
	(*count)++;
	block->next = block->ptr + block->size;
	*(block->next) = (t_block){block, NULL, size, FALSE, block->next + sizeof(t_block)};
	return (block->next);
}
