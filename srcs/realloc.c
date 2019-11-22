/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:33:06 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/26 10:56:28 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	t_block	*block;

	// ft_putstr("\033[38;5;206m-- Enter in realloc --\033[0m\n");
	// ft_putstr("\033[32mptr = 0x"), ft_put64hexa((uint64_t)&*ptr), ft_putstr("\033[0m\n");
	if (!size)
	{
		// ft_putstr("\033[35m-- Out of realloc: NULL --\033[0m\n");
		return (NULL);
	}
	if ((block = check_if_block_exist(ptr)) != NULL)
	{

		if ((new_ptr = malloc(size)) == NULL)
			return (NULL);
		new_ptr = ft_memcpy(new_ptr, ptr, block->size);
		free(ptr);
		// ft_putstr("\033[35m-- Out of realloc --\033[0m\n");
		return (new_ptr);
	}
	if ((new_ptr = malloc(size)) == NULL)
		return (NULL);
	// ft_putstr("\033[35m-- Out of realloc: NULL --\033[0m\n");
	return (new_ptr);
}
