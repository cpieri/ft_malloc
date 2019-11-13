/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 10:22:29 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/20 11:13:17 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block		*choose_block(const size_t size)
{
	t_heap		*heap;
	t_block		*block;

	// ft_putstr("\033[33m-- Enter in choose_block --\033[0m\n");
	block = NULL;
	if ((heap = choose_heap(size)) == NULL)
	{
		// ft_putstr("\033[31mError: choose_block l-21: Heap not exist (return null)\033[0m\n");
		return (NULL);
	}
	if ((block = heap->metadata_block) == NULL)
	{
		block = add_block(&heap, size);
		// ft_putstr("1 Out block address: 0x"), ft_put64hexa((uint64_t)&*block), ft_putchar('\n');
		return (block);
	}
	while (block->next != NULL)
	{
		if (block->is_free == TRUE && block->size == size)
		{
			block->is_free = FALSE;
			return (block);
		}
		block = block->next;
	}
	block = add_block(&heap, size);
	// ft_putstr("2 Out of choose_block: block address "), ft_put64hexa((uint64_t)&*block), ft_putchar('\n');
	return (block);
}

t_block		*add_block(t_heap **heap, const size_t size)
{
	t_block		*block;

	block = ((*heap)->metadata_block);
	// ft_putstr("metadata address 0x"), ft_put64hexa((uint64_t)&*block), ft_putchar('\n');
	(((*heap)->count))++;
	(((*heap)->free_size)) -= (size + sizeof(t_block));
	if (block == NULL)
	{
		block = (t_block*)((void*)*heap + sizeof(t_heap));
		*block = (t_block){NULL, NULL, size, FALSE, ((void*)block + sizeof(t_block))};
		((*heap)->metadata_block) = block;
		return (block);
	}
	while (block->next != NULL)
		block = block->next;
	// ft_putstr("block to next address 0x"), ft_put64hexa((uint64_t)&*block), ft_putchar('\n');
	// ft_putstr("block ptr address 0x"), ft_put64hexa((uint64_t)&*block->ptr), ft_putchar('\n');
	block->next = (t_block*)(block->ptr + block->size);
	// ft_putstr("next block address 0x"), ft_put64hexa((uint64_t)&*block->next), ft_putchar('\n');
	*(block->next) = (t_block){block, NULL, size, FALSE, ((void*)block->next + sizeof(t_block))};
	// ft_putstr("block next ptr address 0x"), ft_put64hexa((uint64_t)&*block->next->ptr), ft_putchar('\n');
	// ft_putstr("final return\n");
	return (block->next);
}
