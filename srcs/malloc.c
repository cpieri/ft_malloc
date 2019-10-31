/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:38:43 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/05 14:58:26 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_zone	select_zone(size_t size)
{
	t_zone		zone;
	size_t		max;

	if (size < (TINY_BLOCK_SIZE - sizeof(t_block)))
	{
		max = TINY_SIZE_ALLOCATION / (128 + sizeof(t_block));
		zone = (t_zone){TINY, max, TINY_SIZE_ALLOCATION};
	}
	else if (size < (SMALL_BLOCK_SIZE - sizeof(t_block)))
	{
		max = SMALL_SIZE_ALLOCATION / (128 + sizeof(t_block));
		zone = (t_zone){SMALL, max, SMALL_SIZE_ALLOCATION};
	}
	else
		zone = (t_zone){LARGE, 1, size + sizeof(t_heap)};
	return (zone);
}

static int		create_zone(size_t size)
{
	size_t	free_size;
	t_zone		zone;

	zone = select_zone(size);
	g_heap = (t_heap*)mmap(0, zone.alloc_size, MMAP_PROT, MMAP_FLAGS, -1, 0);
	if (g_heap == NULL)
		return (FAILURE);
	free_size = zone.alloc_size - sizeof(t_heap);
	*g_heap = (t_heap){NULL, NULL, (t_block*)(g_heap + sizeof(t_heap)), zone.alloc_size, free_size, 0, TINY};
	return (SUCCESS);
}

static t_heap	*choose_heap(size_t size)
{
	t_zone		zone;
	t_heap		*heap;

	ft_putstr("-- Start ChooseHeap --\n");
	heap = g_heap;
	zone = select_zone(size);
	while (heap != NULL)
	{
		if (heap->zone_type == zone.type && heap->count < zone.max)
		{
			return (heap);
		}
		heap = heap->next;
	}
	// if (heap == NULL)
	// 	if (create_zone(size) == SUCCESS)
	// 	{
	// 		if ((heap = choose_heap(size)) != NULL)
	// 			return (heap);
	// 	}
	ft_putstr("-- End ChooseHeap --\n");
	return (NULL);
}

static void		*add_block(const t_block *blocks, size_t *count, size_t size)
{
	t_block		*blocks_c;
	t_block		*prev;
	void		*new_ptr;

	ft_putstr("-- Start AddBlock --\n");
	blocks_c = (t_block*)blocks;
	new_ptr = NULL;
	while (blocks_c != NULL)
	{
		if (blocks_c->is_free == FREE && blocks_c->size == size)
		{
			blocks_c->is_free = NOT_FREE;
			return (blocks->ptr);
		}
		prev = blocks_c;
		blocks_c = blocks_c->next;
	}
	(*count)++;
	new_ptr = prev->ptr + prev->size + sizeof(t_block);
	prev->next = &((t_block){prev, NULL, size, FREE, new_ptr});
	ft_putstr("-- End AddBlock --\n");
	ft_putstr("Return ptr: 0x"), ft_put64hexa((uint64_t)&*new_ptr), ft_putchar('\n');
	return (new_ptr);
}

void			*malloc(size_t size)
{
	void		*ptr;
	t_heap		*heap;

	ft_putstr("-- Start Malloc --\n");
	if (g_heap == NULL)
		if (create_zone(size) == FAILURE)
			return (NULL);
	ft_putstr("-- Choose Heap --\n");
	heap = choose_heap(size);
	ft_putstr("Heap ptr: 0x"), ft_put64hexa((uint64_t)&*heap), ft_putchar('\n');
	ft_putstr("-- Add block --\n");
	ptr = add_block(heap->metadata_block, &heap->count, size);
	ft_putstr("-- End Malloc --\n");
	ft_putstr("Return ptr: 0x"), ft_put64hexa((uint64_t)&*ptr), ft_putchar('\n');
	return (ptr);
}