/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:17:10 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/21 11:26:36 by cpieri           ###   ########.fr       */
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
