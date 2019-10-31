/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_core.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:51:37 by cpieri            #+#    #+#             */
/*   Updated: 2019/10/31 15:30:56 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_CORE_H
# define MALLOC_CORE_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>

/*
**	Macros for Max Size of Zones
*/
# define ROUNDED_UP	16
# define TINY_SIZE	9
# define TINY_MAX	992
# define SMALL_SIZE	140
# define SMALL_MAX	14999

/*
**	Structures
*/
typedef struct			s_block_meta
{
	size_t				size;
	int					is_free;
	struct block_meta	*next;
}						t_block_meta;


/*
**	Defination of functions: LibMalloc
*/
void	*allocate(size_t size);
void	*create_and_allocate(size_t size);

#endif