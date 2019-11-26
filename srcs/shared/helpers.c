/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   helpers.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cpieri <cpieri@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/21 11:17:10 by cpieri       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 11:15:16 by cpieri      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
