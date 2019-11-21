/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:38:43 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/21 14:23:42 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <execinfo.h>

static void		*malloc_core(size_t size)
{
	void		*ptr;

	size = (size + (ROUNDUP - 1)) & (-ROUNDUP);
	if ((ptr = choose_block(size)))
		return (ptr);
	if ((create_heap(size)) == NULL)
		return (NULL);
	ptr = choose_block(size);
	return (ptr);
}

void			*malloc(size_t size)
{
	void		*ptr;

	if (!size)
		return (NULL);
	if ((ptr = malloc_core(size)) == NULL)
		return (NULL);
	ptr = ft_memset(ptr, 0xaa, size);
	// ft_putstr("\033[32mptr = 0x"), ft_put64hexa((uint64_t)&*ptr), ft_putstr("\033[0m\n");
	return (ptr);
}
