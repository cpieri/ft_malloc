/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:42:41 by cpieri            #+#    #+#             */
/*   Updated: 2019/10/31 15:54:11 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_core.h"

t_block_meta		*g_zones[3] = {NULL, NULL, NULL};

static void		*create_zone(size_t type)
{
	const size_t	page_size = getpagesize();
	size_t			size_reclaim;
	void			*ptr;

	if (type == 0)
		size_reclaim = (TINY_MAX % page_size) * ROUNDED_UP;
	else if (type == 1)
		size_reclaim = (SMALL_MAX % page_size) * ROUNDED_UP;
	else
		size_reclaim = (type % page_size) * ROUNDED_UP;
	ptr = mmap(0, size_reclaim, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE,
		-1, 0);
	// if (type != 0 || type != 1)
	// 	return (ptr);
	g_zones[type] = ptr;
	printf("ptr = %p, g_zones = %p\n\n", ptr, g_zones[type]);
	return (NULL);
}

// void			*allocate(size_t size, size_t zone_type)
// {
// 	void	*ptr;

// 	g_zones[zone_type]
// 	return (ptr);
// }

void			*create_and_allocate(size_t size)
{
	int		zone_type;
	void	*ptr = NULL;

	zone_type = 0;
	if (size > TINY_SIZE && size <= SMALL_SIZE)
		zone_type = 1;
	else if (size > SMALL_SIZE)
	{
		ptr = create_zone(size);
		printf("tiny address: %p, small address: %p, other address: %p\n", g_zones[0], g_zones[1], g_zones[2]);
		return (ptr);
	}
	create_zone(zone_type);
	printf("tiny address: %p, small address: %p, other address: %p\n", g_zones[0], g_zones[1], g_zones[2]);
	// ptr = allocate(size, zone_type);
	return (ptr);
}