/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 11:48:09 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/21 12:35:59 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void		*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char*)b;
	while (i != len)
	{
		s[i] = c;
		i++;
	}
	return (s);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dest;
	char		*srcs;

	dest = (char*)dst;
	srcs = (char*)src;
	i = 0;
	while (i != n)
	{
		dest[i] = srcs[i];
		i++;
	}
	return (dest);
}
