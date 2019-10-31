/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:38:43 by cpieri            #+#    #+#             */
/*   Updated: 2019/10/31 15:53:20 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>
#include <stdio.h>

int		g_malloc_init = 0;

/*
**	Malloc is a function that allocates memory and returns a pointer containing
**	the block address
**
**	Operation:
**		Malloc allocates 3 zones `tiny` `small` `large`...
**
**	Params:
**		"size_t size" it's the size of request to allocation
*/
void			*ft_malloc(size_t size)
{
	void	*new_alloc = NULL;

	if (size <= 0)
		return (NULL);
	if (g_malloc_init)
		new_alloc = NULL;
	else
		new_alloc = create_and_allocate(size);
	return (new_alloc);
}

void			*ft_no_malloc(size_t size)
{
	(void)size;
	return (NULL);
}

int		main(void)
{
	ft_malloc(150);
	return (1);
}
