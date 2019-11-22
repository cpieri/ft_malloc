/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:19:29 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/26 10:57:27 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_heap			*create_heap(const size_t size)
{
	t_helper_group		hlp;
	t_heap				*new_heap;

	// ft_putstr("\033[38;5;206m-- Enter in create_heap --\033[0m\n");
	hlp = select_helper_group(size);
	new_heap = (t_heap*)mmap(0, hlp.alloc_size, MMAP_PROT, MMAP_FLAGS, -1, 0);
	if (new_heap == MAP_FAILED)
		return (NULL);
	hlp.free_size = hlp.alloc_size - sizeof(t_heap);
	new_heap->prev = 0x00;
	new_heap->next = 0x00;
	new_heap->metadata_block = 0x00;
	new_heap->group = hlp.group;
	new_heap->total_size = hlp.alloc_size;
	new_heap->free_size = hlp.free_size;
	new_heap->count = 0;
	// ft_putstr("\033[38;5;206m-- Out of create_heap --\033[0m\n");
	return ((t_heap*)add_to_g_heap(new_heap));
}

int				destroy_heap(const t_heap *heap)
{
	t_heap		*c_heap;

	if ((c_heap = check_heap_exist(heap)))
	{
		rm_to_g_heap(heap);
		if (munmap((t_heap*)heap, heap->total_size) == -1)
			return (FAILURE);
	}
	return (SUCCESS);
}

t_heap			*find_heap(const t_block *block)
{
	t_block	*tmp_block;
	t_heap	*heap;

	tmp_block = (t_block*)block;
	while (tmp_block->prev != NULL)
		tmp_block = tmp_block->prev;
	heap = (t_heap*)((void*)tmp_block - sizeof(t_heap));
	return (heap);
}
