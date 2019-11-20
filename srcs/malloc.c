/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:38:43 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/20 11:38:08 by cpieri           ###   ########.fr       */
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
	ptr = malloc_core(size);
	ptr = ft_memset(ptr, 0xaa, size);
	return (ptr);
}
