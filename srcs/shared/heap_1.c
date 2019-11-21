/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 10:03:47 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/21 15:15:39 by cpieri           ###   ########.fr       */
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
