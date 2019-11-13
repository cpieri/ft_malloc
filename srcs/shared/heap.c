/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 10:03:47 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/20 10:54:32 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_helper_group	select_helper_group(const size_t size)
{
	t_helper_group		hlp;
	size_t				max;
	size_t				alloc_size;

	// ft_putstr("Print size: "), ft_putnbr(size), ft_putchar('\n');
	// ft_putstr("Print Tiny size: "), ft_putnbr(TINY_BLOCK_SIZE), ft_putchar('\n');
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
		alloc_size = ((size + sizeof(t_heap)) + (getpagesize() - 1)) & (-getpagesize());
		max = alloc_size / (size + sizeof(t_block));
		hlp = (t_helper_group){LARGE, max, alloc_size * 2, 0};
	}
	return (hlp);
}

void			print_all_heap(void)
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

t_heap const	*add_to_g_heap(const t_heap *new_heap)
{
	t_heap		*def_heap;

	// ft_putstr("-- Enter in add_to_g_heap --\n");
	def_heap = (t_heap*)g_heap;
	// ft_putstr("def_heap value: 0x"), ft_put64hexa((uint64_t)&*def_heap), ft_putchar('\n');
	if (def_heap == NULL)
	{
		// ft_putstr("first heap\n");
		g_heap = (t_heap*)new_heap;
		// ft_putstr("def_heap value: 0x"), ft_put64hexa((uint64_t)&*def_heap), ft_putchar('\n');
		// ft_putstr("g_heap value: 0x"), ft_put64hexa((uint64_t)&*g_heap), ft_putchar('\n');
		return (g_heap);
	}
	while (def_heap->next != NULL)
		def_heap = def_heap->next;
	def_heap->next = (t_heap*)new_heap;
	def_heap->next->prev = def_heap;
	// ft_putstr("-- Out of add_to_g_heap --\n");
	return (new_heap);
}

t_heap			*create_heap(const size_t size)
{
	t_helper_group		hlp;
	t_heap				*new_heap;
	void				*mem;
	void				*max_add = NULL;

	// ft_putstr("-- Enter in create_heap --\n");
	hlp = select_helper_group(size);
	// ft_putstr("group selected is: "), ft_putnbr(hlp.group), ft_putchar('\n');
	// ft_putstr("max selected is: "), ft_putnbr(hlp.max), ft_putchar('\n');
	// ft_putstr("\033[35mAlloc size: "), ft_putnbr(hlp.alloc_size), ft_putstr("\033[0m\n");
	mem = mmap(0, hlp.alloc_size, MMAP_PROT, MMAP_FLAGS, -1, 0);
	if (mem == MAP_FAILED)
		return (NULL);
	// ft_memset(mem, 0xaa, hlp.alloc_size);
	max_add = mem + hlp.alloc_size;
	new_heap = (t_heap*)mem;
	// ft_putstr("address of new_heap: 0x"), ft_put64hexa((uint64_t)&*new_heap), ft_putchar('\n');
	// ft_putstr("address of end_heap: 0x"), ft_put64hexa((uint64_t)&*max_add), ft_putchar('\n');
	hlp.free_size = hlp.alloc_size - sizeof(t_heap);
	*new_heap = (t_heap){0x00, 0x00, 0x00, hlp.group, hlp.alloc_size, hlp.free_size, 0};
	// ft_putstr("Alloc_size value: "), ft_putnbr(hlp.alloc_size), ft_putchar('\n');
	// ft_putstr("Testing val of new_heap (total_size): "), ft_putnbr(new_heap->total_size), ft_putchar('\n');
	// ft_putstr("-- Out of create_heap --\n");
	return ((t_heap*)add_to_g_heap(new_heap));
}

t_heap			*choose_heap(const size_t size)
{
	t_helper_group		hlp;
	t_heap				*heap;

	// print_all_heap();
	heap = (t_heap*)g_heap;
	// ft_putstr("g_heap value: 0x"), ft_put64hexa((uint64_t)&*g_heap), ft_putchar('\n');
	// ft_putstr("heap value: 0x"), ft_put64hexa((uint64_t)&*heap), ft_putchar('\n');
	hlp = select_helper_group(size);
	while (heap != NULL)
	{
		// ft_putstr("free_size: "), ft_putnbr(heap->free_size), ft_putstr("\n");
		// ft_putstr("size reclaim: "), ft_putnbr((size + sizeof(t_block))), ft_putstr("\n");
		// ft_putstr("max: "), ft_putnbr(hlp.max), ft_putstr("\n");
		// ft_putstr("count: "), ft_putnbr(heap->count), ft_putstr("\n");
		if (heap->group == hlp.group && heap->free_size > (size + sizeof(t_block)) && heap->count < hlp.max)
		{
			// ft_putstr("Heap selcted: 0x"), ft_put64hexa((uint64_t)&*heap), ft_putchar('\n');
			return (heap);
		}
		heap = heap->next;
	}
	// ft_putstr("-- Out of choose_heap --\n");
	return (NULL);
}