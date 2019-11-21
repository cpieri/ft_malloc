#include <stdlib.h>
# include <unistd.h>

void	putchar(char c)
{
	write(1, &c, 1);
}

void	putnbr(int n)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		putchar('-');
		nb = nb * -1;
	}
	if (nb > 9)
		putnbr(nb / 10);
	putchar(nb % 10 + 48);
}

int main()
{
	int i;
	char *addr;

	i = 0;
	while (i < 1024)
	{
		putnbr(i), putchar('\n');
		addr = (char*)malloc(1024);
		if (i % 2 == 0)
			free(addr);
		i++;
	}
	return (0);
}
