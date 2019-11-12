/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 10:03:47 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/12 12:20:36 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_helper_group	select_helper_group(const size_t size)
{
	t_helper_group		hlp;
	size_t				max;

	if (size <= (size_t)TINY_BLOCK_SIZE)
	{
		max = TINY_SIZE_ALLOCATION / (128 + sizeof(t_block));
		hlp = (t_helper_group){TINY, max, TINY_SIZE_ALLOCATION, 0};
	}
	else if (size <= (size_t)SMALL_BLOCK_SIZE)
	{
		max = SMALL_SIZE_ALLOCATION / (128 + sizeof(t_block));
		hlp = (t_helper_group){SMALL, max, SMALL_SIZE_ALLOCATION, 0};
	}
	else
		hlp = (t_helper_group){LARGE, 1, size + sizeof(t_heap), 0};
	return (hlp);
}

int				add_to_g_heap(const t_heap *new_heap)
{
	t_heap		*def_heap;
	t_heap		*def_heap_prev;

	def_heap_prev = NULL;
	def_heap = (t_heap*)g_heap;
	if (def_heap == NULL)
	{
		def_heap = (t_heap*)new_heap;
		return (SUCCESS);
	}
	while (def_heap->next != NULL)
		def_heap = def_heap->next;
	def_heap->next = (t_heap*)new_heap;
	def_heap->next->prev = def_heap;
	return (SUCCESS);
}

int				create_heap(const size_t size)
{
	t_helper_group		hlp;
	t_heap				*new_heap;

	hlp = select_helper_group(size);
	new_heap = (t_heap*)mmap(0, hlp.alloc_size, MMAP_PROT, MMAP_FLAGS, -1, 0);
	if (new_heap == NULL)
		return (FAILURE);
	hlp.free_size = hlp.alloc_size - sizeof(t_heap);
	*new_heap = (t_heap){0x00, 0x00, 0x00, hlp.group, hlp.alloc_size, hlp.free_size, 0};
	add_to_g_heap(new_heap);
	return (SUCCESS);
}

t_heap			*choose_heap(const size_t size)
{
	t_helper_group		hlp;
	t_heap				*heap;

	heap = (t_heap*)g_heap;
	hlp = select_helper_group(size);
	while (heap != NULL)
	{
		if (heap->group == hlp.group && heap->count < hlp.max)
			return (heap);
		heap = heap->next;
	}
	return (NULL);
}