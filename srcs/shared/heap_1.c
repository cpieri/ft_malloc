/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 10:03:47 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/26 10:57:20 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_heap			*g_heap;

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
		if (tmp == heap)
		{
			if (prev != 0x00)
				prev->next = tmp->next;
			else if (prev == 0x00)
				g_heap = (t_heap*)next;
			if (next != 0x00)
				next->prev = prev;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

t_heap			*choose_heap(const size_t size)
{
	t_helper_group		hlp;
	t_heap				*heap;

	// ft_putstr("\033[38;5;206m-- Enter in choose_heap --\033[0m\n");
	heap = (t_heap*)g_heap;
	hlp = select_helper_group(size);
	while (heap != NULL)
	{
		if (heap->group == hlp.group
			&& heap->free_size > (size + sizeof(t_block))
			&& heap->count < hlp.max)
		{
			// ft_putstr("\033[34mHeap selected: \033[36m0x"), ft_put64hexa((uint64_t)&*heap), ft_putstr("\033[0m\n");
			// ft_putstr("\033[35m-- Out of choose_heap --\033[0m\n");
			return (heap);
		}
		heap = heap->next;
	}
	// ft_putstr("\033[35m-- Out of choose_heap --\033[0m\n");
	return (NULL);
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

void			print_all_heap(void)
{
	t_heap	*heaps;

	heaps = (t_heap*)g_heap;
	ft_putstr("\033[38;5;206m-- Enter in print_all_heap --\033[0m\n");
	ft_putstr("\033[34mSizeof t_heap (hexa): \033[36m"), ft_put64hexa(sizeof(t_heap)), ft_putstr("\033[0m\n");
	while (heaps != NULL)
	{
		ft_putstr("\033[34mHeap address: \033[0m\033[36m0x");
		ft_put64hexa((uint64_t)&*heaps);
		ft_putstr(" -> ");
		ft_put64hexa((uint64_t)&*(void*)((void*)heaps + sizeof(t_heap)));
		ft_putstr("\033[0m\n");
		heaps = heaps->next;
	}
	ft_putstr("\033[35m-- Out of print_all_heap --\033[0m\n");
}
