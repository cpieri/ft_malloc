/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mini_libft_1.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cpieri <cpieri@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/20 11:48:09 by cpieri       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 11:22:57 by cpieri      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

void		*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char*)b;
	while (i != len)
	{
		s[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dest;
	const char	*srcs;

	dest = (char*)dst;
	srcs = (const char*)src;
	i = 0;
	while (i != n)
	{
		dest[i] = srcs[i];
		i++;
	}
	return (dest);
}
