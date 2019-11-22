/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:05:12 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/26 10:56:47 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t count, size_t size)
{
	void	*ptr;

	// ft_putstr("\033[38;5;206m-- Enter in calloc --\033[0m\n");
	if ((ptr = malloc(count * size)) == NULL)
		return (NULL);
	ptr = ft_memset(ptr, 0, count * size);
	// ft_putstr("\033[32mptr = 0x"), ft_put64hexa((uint64_t)&*ptr), ft_putstr("\033[0m\n");
	// ft_putstr("\033[35m-- Out of calloc --\033[0m\n");
	return (ptr);
}