/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:38:43 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/26 10:57:08 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <execinfo.h>

static void		*malloc_core(size_t size)
{
	void		*ptr;

	// ft_putstr("\033[38;5;206m-- Enter in malloc_core --\033[0m\n");
	size = (size + (ROUNDUP - 1)) & (-ROUNDUP);
	// ft_putstr("\033[34mSize roundup: \033[36m"), ft_putnbr(size), ft_putstr("\033[0m\n");
	// print_all_blocks();
	if ((ptr = choose_block(size)))
	{
		// ft_putstr("\033[32mptr return by malloc_core = 0x"), ft_put64hexa((uint64_t)&*ptr), ft_putstr("\033[0m\n");
		return (ptr);
	}
	if ((create_heap(size)) == NULL)
		return (NULL);
	// print_all_heap();
	ptr = choose_block(size);
	// ft_putstr("\033[32mptr return by malloc_core = 0x"), ft_put64hexa((uint64_t)&*ptr), ft_putstr("\033[0m\n");
	return (ptr);
}

void			*malloc(size_t size)
{
	void		*ptr;
	// void		*caller_address[2];

	// backtrace(caller_address, 2);
	// backtrace_symbols_fd(caller_address + 1, 1, 1);
	// ft_putstr("\033[38;5;206m-- Enter in malloc --\033[0m\n");
	// ft_putstr("\033[34mSize enter in malloc: \033[36m"), ft_putnbr(size), ft_putstr("\033[0m\n");
	if (!size)
		return (NULL);
	if ((ptr = malloc_core(size)) == NULL)
		return (NULL);
	ptr = ft_memset(ptr, 0xaa, size);
	// ft_putstr("\033[32mptr = 0x"), ft_put64hexa((uint64_t)&*ptr), ft_putstr("\033[0m\n");
	// ft_putstr("\033[35m-- Out of malloc --\033[0m\n");
	return (ptr);
}
