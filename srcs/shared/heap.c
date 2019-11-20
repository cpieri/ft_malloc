/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 10:03:47 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/21 10:31:30 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_helper_group	select_helper_group(const size_t size)
{
	t_helper_group		hlp;
	size_t				max;
	size_t				alloc_size;

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
	{
		alloc_size = size + sizeof(t_heap);
		alloc_size = (alloc_size + (getpagesize() - 1)) & (-getpagesize());
		max = alloc_size / (size + sizeof(t_block));
		hlp = (t_helper_group){LARGE, max, alloc_size * 2, 0};
	}
	return (hlp);
}

t_heap const	*add_to_g_heap(const t_heap *new_heap)
{
	t_heap		*def_heap;

	def_heap = (t_heap*)g_heap;
	if (def_heap == NULL)
	{
		g_heap = (t_heap*)new_heap;
		return (g_heap);
	}
	while (def_heap->next != NULL)
		def_heap = def_heap->next;
	def_heap->next = (t_heap*)new_heap;
	def_heap->next->prev = def_heap;
	return (new_heap);
}

t_heap			*create_heap(const size_t size)
{
	t_helper_group		hlp;
	t_heap				*new_heap;

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
	return ((t_heap*)add_to_g_heap(new_heap));
}

void			print_heap(void)
{
	t_heap	*heaps;

	heaps = (t_heap*)g_heap;
	while (heaps != NULL)
	{
		ft_putstr("\033[36mHeap address: \033[0m\033[34m0x");
		ft_put64hexa((uint64_t)&*heaps);
		ft_putstr("\033[0m\n");
		heaps = heaps->next;
	}
	ft_putstr("\033[35m---------\033[0m\n");
}

t_heap			*choose_heap(const size_t size)
{
	t_helper_group		hlp;
	t_heap				*heap;

	heap = (t_heap*)g_heap;
	hlp = select_helper_group(size);
	while (heap != NULL)
	{
		if (heap->group == hlp.group
			&& heap->free_size > (size + sizeof(t_block))
			&& heap->count < hlp.max)
			return (heap);
		heap = heap->next;
	}
	return (NULL);
}

t_heap			*find_heap(const t_block *block)
{
	t_block	*tmp_block;
	t_heap	*heap = NULL;

	tmp_block = (t_block*)block;
	// print_heap();
	while (tmp_block->prev != NULL)
		tmp_block = tmp_block->prev;
	heap = (t_heap*)((void*)tmp_block - sizeof(t_heap));
	// ft_putstr("heap find: 0x"), ft_put64hexa((uint64_t)&*heap), ft_putstr("\n");
	// ft_putstr("print heap total size"), ft_putnbr(heap->total_size), ft_putstr("\n");
	return (heap);
}

t_heap			*check_heap_exist(const t_heap *heap)
{
	t_heap		*def_heap;

	def_heap = (t_heap*)g_heap;
	while (def_heap != NULL)
	{
		if (def_heap == heap)
			return (def_heap);
		def_heap = def_heap->next;
	}
	return (NULL);
}

int				rm_to_g_heap(const t_heap *heap)
{
	t_heap	*prev;
	t_heap	*tmp;
	t_heap	*next;

	tmp = (t_heap*)g_heap;
	while (tmp != NULL)
	{
		prev = tmp->prev;
		next = tmp->next;
		// ft_putstr("tmp heap: 0x"), ft_put64hexa((uint64_t)&*tmp), ft_putstr("\n");
		// ft_putstr("fnd heap: 0x"), ft_put64hexa((uint64_t)&*heap), ft_putstr("\n");
		if (tmp == heap)
		{
			prev->next = tmp->next;
			if (next != 0x00)
				next->prev = prev;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int				destroy_heap(const t_heap *heap)
{
	t_heap		*c_heap;

	// ft_putstr("enter in destroy heap\n");
	if ((c_heap = check_heap_exist(heap)))
	{
		// ft_putstr("Heap to delete: 0x"), ft_put64hexa((uint64_t)&*heap), ft_putstr("\n");
		// print_heap();
		rm_to_g_heap(heap);
		// print_heap();
		if (munmap((t_heap*)heap, heap->total_size) == -1)
			return (FAILURE);
	}
	return (SUCCESS);
}
