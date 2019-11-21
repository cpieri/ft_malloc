/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:58:38 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/21 11:25:47 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	free_core(t_block *block)
{
	t_heap	*heap;

	if ((heap = find_heap(block)))
	{
		ft_memset(block->ptr, 0xaa, block->size);
		block->is_free = TRUE;
		if (heap->count - 1 == 0)
		{
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
			free_core(block);
	}
}
