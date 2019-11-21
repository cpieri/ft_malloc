/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:28:16 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/21 15:15:19 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

/*
**	Includes
*/
# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>

/*
**	Macros General
*/
# define ROUNDUP				16
# define ALIGN_ZONE				((getpagesize() - 1)) & (-getpagesize())
# define TINY_SIZE				(4 * getpagesize())
# define TINY_SIZE_ALLOCATION	(TINY_SIZE + ALIGN_ZONE)
# define TINY_BLOCK_SIZE		(TINY_SIZE_ALLOCATION / 128)
# define SMALL_SIZE				(32 * getpagesize())
# define SMALL_SIZE_ALLOCATION	(SMALL_SIZE + ALIGN_ZONE)
# define SMALL_BLOCK_SIZE		(SMALL_SIZE_ALLOCATION / 128)
# define MMAP_PROT				(PROT_READ | PROT_WRITE)
# define MMAP_FLAGS				(MAP_PRIVATE | MAP_ANON)
# define FAILURE				-1
# define SUCCESS				0

/*
**	Enums
*/
typedef enum			e_groups
{
	TINY = 0,
	SMALL = 1,
	LARGE = 2
}						t_groups;

typedef enum			e_bool
{
	TRUE,
	FALSE
}						t_bool;

/*
**	Structures
*/
typedef struct			s_helper_group
{
	t_groups			group;
	size_t				max;
	size_t				alloc_size;
	size_t				free_size;
}						t_helper_group;

typedef struct			s_block
{
	struct s_block		*prev;
	struct s_block		*next;
	size_t				size;
	t_bool				is_free;
	void				*ptr;
}						t_block;

typedef struct			s_heap
{
	struct s_heap		*prev;
	struct s_heap		*next;
	t_block				*metadata_block;
	t_groups			group;
	size_t				total_size;
	size_t				free_size;
	size_t				count;
}						t_heap;

/*
**	Global Variable
*/
extern t_heap		*g_heap;

/*
**	Defination of functions: LibMalloc
*/
void					free(void *ptr);
void					show_alloc_mem(void);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);

/*
**	Defination of functions: Heap
*/
t_heap					*create_heap(const size_t size);
int						destroy_heap(const t_heap *heap);
t_heap					*choose_heap(const size_t size);
t_heap					*find_heap(const t_block *block);
t_heap					*check_heap_exist(const t_heap *heap);
t_heap const			*add_to_g_heap(const t_heap *new_heap);
int						rm_to_g_heap(const t_heap *heap);
t_helper_group			select_helper_group(const size_t size);

/*
**	Defination of functions: Blocks
*/
void					*choose_block(const size_t size);
t_block					*add_block(t_heap **heap, const size_t size);

/*
**	Defination of functions: LibFt
*/
void					ft_putstr(char *s);
void					ft_putnbr(int n);
void					ft_putchar(char c);
void					ft_put64hexa(uint64_t nb);
void					*ft_memset(void *b, int c, size_t len);
void					*ft_memcpy(void *dst, const void *src, size_t n);

#endif
