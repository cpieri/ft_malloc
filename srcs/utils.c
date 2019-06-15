/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:06:47 by cpieri            #+#    #+#             */
/*   Updated: 2019/06/15 14:12:17 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
**	Global Variable for Malloc.
*/
size_t	g_pages_size;
size_t	g_tiny_min = 1;
size_t	g_tiny_max;
size_t	g_small_min;
size_t	g_small_max;
size_t	g_large_min;

/*
**
*/
void	set_zones_var(void)
{
	g_pages_size = getpagesize();
	g_tiny_max = g_pages_size * 1;
	g_small_min = g_tiny_min + 1;
	g_small_max = g_pages_size * 2;
	g_large_min = g_small_max + 1;
}