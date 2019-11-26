/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   show_alloc_mem.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cpieri <cpieri@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/21 14:40:55 by cpieri       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 11:24:40 by cpieri      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

static size_t	print_blocks(t_heap *heap)
{
	t_block		*blocks;
	void		*max;
	size_t		total;

	blocks = (t_block*)heap->metadata_block;
	total = 0;
	while (blocks != NULL)
	{
		max = (void*)(blocks->ptr + blocks->size);
		ft_putstr("0x");
		ft_put64hexa((uint64_t)(&(*blocks->ptr)));
		ft_putstr(" - ");
		ft_put64hexa((uint64_t)(&(*max)));
		ft_putstr(" : ");
		total += blocks->size;
		ft_putnbr((int)blocks->size);
		ft_putstr(" octets\n");
		blocks = blocks->next;
	}
	return (total);
}

static void		print_group(t_groups group, void *ptr_heap)
{
	if (group == TINY)
		ft_putstr("TINY : 0x");
	else if (group == SMALL)
		ft_putstr("SMALL : 0x");
	else
		ft_putstr("LARGE : 0x");
	ft_put64hexa((uint64_t)(&(*ptr_heap)));
	ft_putstr("\n");
}

static size_t	print_heap(t_groups group)
{
	t_heap	*heap;
	size_t	total;

	heap = (t_heap*)g_heap;
	total = 0;
	while (heap != NULL)
	{
		if (heap->group == group)
		{
			print_group(group, heap);
			total = print_blocks(heap);
		}
		heap = heap->next;
	}
	return (total);
}

void			show_alloc_mem(void)
{
	size_t	total;

	total = 0;
	total += print_heap(TINY);
	total += print_heap(SMALL);
	total += print_heap(LARGE);
	ft_putstr("Total : ");
	ft_putnbr((int)total);
	ft_putstr(" octets\n");
}
