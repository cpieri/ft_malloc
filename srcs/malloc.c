/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:38:43 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/12 12:21:48 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*malloc_core(const size_t size)
{
	t_block		*block;
	void		*ptr = NULL;

	if ((block = choose_block(size)))
		return (block + sizeof(t_block));
	
	return (ptr);
}

void		*malloc(size_t size)
{
	void		*ptr;

	if (!size)
		return (NULL);
	ptr = malloc_core(size);
	return (ptr);
}