/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:28:16 by cpieri            #+#    #+#             */
/*   Updated: 2019/06/14 16:18:25 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

/*
**	Includes
*/
# include <string.h>

/*
**	Macros General
*/
# define ROUNDED_UP	16

/*
**	Macros for Max Size of Zones
*/
# define TINY_MAX	992
# define SMALL_MAX	14999
# define LARGE_MAX	127000

/*
**	Structures
*/
typedef struct			s_block_meta
{
	size_t				size;
	int					free;
	struct block_meta	*next;
	void				*adrr;

}						t_block_meta;

/*
**	Defination of functions: LibMalloc
*/
void					free(void *ptr);
void					show_alloc_mem(void);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);

#endif
