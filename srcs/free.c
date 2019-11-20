/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:58:38 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/21 10:29:08 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	free_core(const void *ptr, t_block *block)
{
	t_heap	*heap;

	(void)ptr;
	if ((heap = find_heap(block)))
	{
		// ft_putstr("Enter in Free\n");
		// (heap->free_size) += block->size + sizeof(t_block);
		ft_memset(block->ptr, 0xaa, block->size);
		block->is_free = TRUE;
		if (heap->count - 1 == 0)
		{
			// ft_putstr("Go to destroy heap\n");
			if (heap->prev != 0x00 || heap->next != 0x00)
				destroy_heap(heap);
		}
	}
}

void		free(void *ptr)
{
	t_block		*block;

	block = NULL;
	if (ptr != NULL)
	{
		block = (t_block*)(ptr - sizeof(t_block));
		if (block->ptr != NULL)
			free_core(ptr, block);
	}
}
