/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:38:43 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/20 11:02:37 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <execinfo.h>

static void		*malloc_core(size_t size)
{
	t_block		*block;
	void		*ptr = NULL;

	// ft_putstr("\033[38;5;206m-- Enter in malloc_core --\033[0m\n");
	size = (size + (ROUNDUP - 1)) & (-ROUNDUP);
	if ((block = choose_block(size)))
	{
		// ft_putstr("\033[35m-- Out in malloc_core --\033[0m\n");
		return ((void*)block + sizeof(t_block));
	}
	if ((create_heap(size)) == NULL)
		return (NULL);
	// ft_putstr("g_heap = 0x"), ft_put64hexa((uint64_t)&*g_heap), ft_putchar('\n');
	block = choose_block(size);
	// ft_putstr("g_heap = 0x"), ft_put64hexa((uint64_t)&*g_heap), ft_putchar('\n');
	ptr = ((void*)block + sizeof(t_block));
	// ptr = ft_memset(ptr, 0x00, size);
	// ft_putstr("\033[35m-- Out in malloc_core --\033[0m\n");
	return (ptr);
}

void		*malloc(size_t size)
{
	// void		*caller_address[2];
	void		*ptr;

	// backtrace(caller_address, 2);
	// backtrace_symbols_fd(caller_address + 1, 1, 1);
	if (!size)
		return (NULL);
	// ft_putstr("\033[33mPrint size: "), ft_putnbr(size), ft_putstr("\033[0m\n");
	ptr = malloc_core(size);
	// ft_putstr("\033[32mptr = 0x"), ft_put64hexa((uint64_t)&*ptr), ft_putstr("\033[0m\n");
	ptr = ft_memset(ptr, 0xaa, size);
	// ft_putstr("\033[32mptr = 0x"), ft_put64hexa((uint64_t)&*ptr), ft_putstr("\033[0m\n");
	return (ptr);
}