/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:33:06 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/21 14:23:14 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	t_block	*block;
	// t_block	*new_block;

	if (!size || ptr == NULL)
		return (NULL);
	// ft_putstr("Enter in realloc\n");
	block = (t_block*)(ptr - sizeof(t_block));
	// ft_putstr("Block size value: "), ft_putnbr(block->size), ft_putstr("\n");
	// ft_putstr("Size value: "), ft_putnbr(size), ft_putstr("\n");
	// print_heap();
	if ((new_ptr = malloc(size)) == NULL)
		return (NULL);
	// new_block = (t_block*)(new_ptr - sizeof(t_block));
	// ft_putstr("Block size value: "), ft_putnbr(new_block->size), ft_putstr("\n");
	// ft_putstr("Size value: "), ft_putnbr(size), ft_putstr("\n");
	// ft_putstr("Memcpy in realloc\n");
	new_ptr = ft_memcpy(new_ptr, ptr, block->size);
	// ft_putstr("Free in realloc\n");
	free(ptr);
	return (new_ptr);
}