/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:33:06 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/26 11:10:01 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	t_block	*block;

	if (!size)
		size = ROUNDUP;
	if ((block = check_if_block_exist(ptr)) != NULL)
	{
		if ((new_ptr = malloc(size)) == NULL)
			return (NULL);
		new_ptr = ft_memcpy(new_ptr, ptr, block->size);
		free(ptr);
		return (new_ptr);
	}
	if ((new_ptr = malloc(size)) == NULL)
		return (NULL);
	return (new_ptr);
}
