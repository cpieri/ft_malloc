/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:28:16 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/05 14:26:10 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

/*
**	Includes
*/
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h>

/*
**	Macros General
*/
# define TINY_SIZE_ALLOCATION	(4 * getpagesize())
# define TINY_BLOCK_SIZE		(TINY_SIZE_ALLOCATION / 128)
# define SMALL_SIZE_ALLOCATION	(16 * getpagesize())
# define SMALL_BLOCK_SIZE		(TINY_SIZE_ALLOCATION / 128)

# define MMAP_PROT				(PROT_READ | PROT_WRITE)
# define MMAP_FLAGS				(MAP_PRIVATE | MAP_ANON)

# define FREE					1
# define NOT_FREE				0

# define FAILURE				-1
# define SUCCESS				0

# define TINY					0
# define SMALL					1
# define LARGE					2

/*
**	Structures
*/
typedef struct			s_zone
{
	uint8_t				type;
	size_t				max;
	size_t				alloc_size;
}						t_zone;

typedef struct			s_block
{
	struct s_block		*prev;
	struct s_block		*next;
	size_t				size;
	int					is_free;
	void				*ptr;
}						t_block;

typedef struct			s_heap
{
	struct s_heap		*prev;
	struct s_heap		*next;
	t_block				*metadata_block;
	size_t				total_size;
	size_t				free_size;
	size_t				count;
	uint16_t			zone_type;
}						t_heap;

/*
**	Global Variable
*/
static t_heap					*g_heap = NULL;

/*
**	Defination of functions: LibMalloc
*/
void					free(void *ptr);
void					show_alloc_mem(void);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);

/*
**	Defination of functions: LibFt
*/
void					ft_putstr(char *s);
void					ft_putnbr(int n);
void					ft_putchar(char c);
void					ft_put64hexa(uint64_t nb);

#endif
