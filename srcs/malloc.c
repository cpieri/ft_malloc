/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:38:43 by cpieri            #+#    #+#             */
/*   Updated: 2019/06/14 16:33:15 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"


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
void	*malloc(size_t size)
{
	void	*new_alloc;

	if (size <= 0)
		return (NULL);
	new_alloc = NULL;
	(void)size;
	return (new_alloc);
}
