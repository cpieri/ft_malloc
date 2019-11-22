/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:58:38 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/26 10:56:41 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	free_core(t_block *block)
{
	t_heap	*heap;

	// ft_putstr("\033[38;5;206m-- Enter in free_core --\033[0m\n");
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
	// ft_putstr("\033[38;5;206m-- Out of free_core --\033[0m\n");
}

void		free(void *ptr)
{
	t_block		*block;

	block = NULL;
	// ft_putstr("\033[38;5;206m-- Enter in free --\033[0m\n");
	// ft_putstr("\033[32mPtr to free = 0x"), ft_put64hexa((uint64_t)&*ptr), ft_putstr("\033[0m\n");
	// print_all_blocks();
	if (ptr != NULL)
	{
		// ft_putstr("\033[34m-- Enter condition of free --\033[0m\n");
		// ft_putstr("\033[34m-- Check if block existe --\033[0m\n");
		if ((block = check_if_block_exist(ptr)) != NULL)
		{
			free_core(block);
			// print_all_blocks();
		}
	}
	// ft_putstr("\033[35m-- Out of free --\033[0m\n");
}
