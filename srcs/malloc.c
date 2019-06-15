/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:38:43 by cpieri            #+#    #+#             */
/*   Updated: 2019/06/15 14:12:40 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "malloc.h"
#include <unistd.h>
#include <stdio.h>

/*
**	Global Variable for Malloc.
*/
static int		g_malloc_init = 0;

static void		create_zones(void)
{

}

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
	void	*new_alloc;

	if (size <= 0)
		return (NULL);
	if (g_malloc_init)
		new_alloc = NULL;
	create_zones();
	return (new_alloc);
}

int		main(void)
{
	ft_malloc(10);
	return (1);
}
