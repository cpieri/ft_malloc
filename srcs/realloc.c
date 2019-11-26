/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   realloc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cpieri <cpieri@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/21 11:33:06 by cpieri       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 11:52:54 by cpieri      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	size_t	size_cpy;
	t_block	*block;

	if (!size)
		size = ROUNDUP;
	if ((block = check_if_block_exist(ptr)) != NULL)
	{
		if ((new_ptr = malloc(size)) == NULL)
			return (NULL);
		size_cpy = (size < block->size) ? size : block->size;
		new_ptr = ft_memcpy(new_ptr, ptr, size_cpy);
		free(ptr);
		return (new_ptr);
	}
	if ((new_ptr = malloc(size)) == NULL)
		return (NULL);
	return (new_ptr);
}
