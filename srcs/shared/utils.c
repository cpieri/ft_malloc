/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:06:47 by cpieri            #+#    #+#             */
/*   Updated: 2019/11/20 10:36:50 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar('-');
		nb = nb * -1;
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + 48);
}

void	ft_putstr(char *s)
{
	int		i = 0;

	while (s[i])
		i++;
	write(1, s, i);
}

static void	put_64hexa(uint64_t nb)
{
	if (nb > 15)
		put_64hexa(nb / 16);
	nb %= 16;
	if (nb < 10)
		ft_putnbr(nb);
	else
		ft_putchar(nb + 'a' - 10);
}

void		ft_put64hexa(uint64_t nb)
{
	if (nb < 16)
		ft_putchar('0');
	put_64hexa(nb);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*s;

	i = 0;
	// ft_putstr("here\n");
	s = (unsigned char*)b;
	while (i != len)
	{
		s[i] = c;
		// ft_putnbr(i), ft_putchar(' ');
		i++;
	}
	// ft_putchar('\n');
	return (s);
}