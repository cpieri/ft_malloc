/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mini_libft_0.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cpieri <cpieri@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/15 14:06:47 by cpieri       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 11:22:14 by cpieri      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

void		ft_putnbr(int n)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar('-');
		nb = nb * -1;
	}
	if (nb > 9)
		ft_putnbr((int)(nb / 10));
	ft_putchar(nb % 10 + 48);
}

void		ft_putstr(char *s)
{
	size_t	i;

	i = 0;
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
		ft_putnbr((int)nb);
	else
		ft_putchar((char)(nb + 'a' - 10));
}

void		ft_put64hexa(uint64_t nb)
{
	if (nb < 16)
		ft_putchar('0');
	put_64hexa(nb);
}
