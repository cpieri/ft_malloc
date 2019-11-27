/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cpieri <cpieri@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/10 11:38:43 by cpieri       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/27 14:58:32 by cpieri      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

static void		*malloc_core(size_t size)
{
	void		*ptr;

	size = (size + (ROUNDUP - 1)) & (-(size_t)ROUNDUP);
	if ((ptr = choose_block(size)))
	{
		return (ptr);
	}
	if ((create_heap(size)) == NULL)
		return (NULL);
	ptr = choose_block(size);
	return (ptr);
}

void			*malloc(size_t size)
{
	void		*ptr;

	if (!size)
		size = ROUNDUP;
	if ((ptr = malloc_core(size)) == NULL)
		return (NULL);
	ptr = ft_memset(ptr, 0xaa, size);
	return (ptr);
}
