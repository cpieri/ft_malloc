/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 10:22:29 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/26 10:57:41 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*choose_block(const size_t size)
{
	t_heap		*heap;
	t_block		*block;

	block = NULL;
	// ft_putstr("\033[38;5;206m-- Enter in choose_block --\033[0m\n");
	if ((heap = choose_heap(size)) == NULL)
		return (NULL);
	// ft_putstr("\033[34mHeap returned: \033[36m0x"), ft_put64hexa((uint64_t)&*heap), ft_putstr("\033[0m\n");
	// ft_putstr("\033[34mBlocks in heap: \033[36m0x"), ft_put64hexa((uint64_t)&*(heap->metadata_block)), ft_putstr("\033[0m\n");
	if ((block = heap->metadata_block) == NULL)
	{
		// ft_putstr("\033[35m-- Out of choose_block --\033[0m\n");
		return (add_block(&heap, size));
	}
	// ft_putstr("\033[34mCheck if one block is free\033[0m\n");
	while (block != NULL)
	{
		// ft_putstr("\033[34mBlock find: \033[36m0x"), ft_put64hexa((uint64_t)&*block), ft_putstr("\033[0m\n");
		if (block->is_free == TRUE && block->size == size)
		{
			block->is_free = FALSE;
			// ft_putstr("\033[34mBlocks free find: \033[36m0x"), ft_put64hexa((uint64_t)&*block), ft_putstr("\033[0m\n");
			// ft_putstr("\033[35m-- Out of choose_block --\033[0m\n");
			return (block->ptr);
		}
		block = block->next;
	}
	// ft_putstr("\033[35m-- Out of choose_block --\033[0m\n");
	return (add_block(&heap, size));
}

t_block		*add_block(t_heap **heap, const size_t size)
{
	t_block		*block;
	void		*ptr;

	// ft_putstr("\033[38;5;206m-- Enter in add_block --\033[0m\n");
	block = ((*heap)->metadata_block);
	(((*heap)->count))++;
	(((*heap)->free_size)) -= (size + sizeof(t_block));
	// ft_putstr("\033[34mSizeof t_block (hexa): \033[36m"), ft_put64hexa(sizeof(t_block)), ft_putstr("\033[0m\n");
	if (block == NULL)
	{
		block = (t_block*)((void*)*heap + sizeof(t_heap));
		ptr = (void*)((void*)block + sizeof(t_block));
		*block = (t_block){NULL, NULL, size, FALSE, ptr, 0};
		((*heap)->metadata_block) = block;
		// ft_putstr("\033[34mNew block add = \033[36m0x"), ft_put64hexa((uint64_t)&*block), ft_putstr("\033[0m\n");
		// ft_putstr("\033[34mNew ptr block add = \033[36m0x"), ft_put64hexa((uint64_t)&*ptr), ft_putstr("\033[0m\n");
		// ft_putstr("\033[35m-- Out of print_all_heap --\033[0m\n");
		return (block->ptr);
	}
	while (block->next != NULL)
		block = block->next;
	block->next = (t_block*)((void*)block->ptr + block->size);
	ptr = (void*)((void*)block->next + sizeof(t_block));
	*(block->next) = (t_block){block, NULL, size, FALSE, ptr, 0};
	// ft_putstr("\033[34mNew block add = \033[36m0x"), ft_put64hexa((uint64_t)&*(block->next)), ft_putstr("\033[0m\n");
	// ft_putstr("\033[34mNew ptr block add = \033[36m0x"), ft_put64hexa((uint64_t)&*ptr), ft_putstr("\033[0m\n");
	// print_all_blocks();
	// ft_putstr("\033[35m-- Out of add_block --\033[0m\n");
	return (block->next->ptr);
}

t_block		*check_if_block_exist(const void *const ptr)
{
	t_heap	*heaps;
	t_block	*blocks;

	heaps = g_heap;
	while (heaps != NULL)
	{
		blocks = heaps->metadata_block;
		while (blocks != NULL)
		{
			if (blocks->ptr == ptr)
				return (blocks);
			blocks = blocks->next;
		}
		heaps = heaps->next;
	}
	return (NULL);
}

void		print_all_blocks(void)
{
	t_heap	*heaps;
	t_block	*blocks;

	heaps = (t_heap*)g_heap;
	ft_putstr("\033[38;5;206m-- Enter in print_all_blocks --\033[0m\n");
	while (heaps != NULL)
	{
		blocks = (t_block*)heaps->metadata_block;
		while (blocks != NULL)
		{
			ft_putstr("\033[34mBlock address: \033[0m\033[36m0x");
			ft_put64hexa((uint64_t)&*blocks);
			ft_putstr("\033[0m\n");
			blocks = blocks->next;
		}
		heaps = heaps->next;
	}
	ft_putstr("\033[35m-- Out of print_all_blocks --\033[0m\n");

}
