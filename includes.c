#include "bsq.h"

void    	ft_putchar(char c)
{
    write(1, &c, 1);   
}

void    	ft_putstr(char *str)
{
    while(*str)
        ft_putchar(*str++);
}

void		ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + 48);
}

char		*ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i])
		{
			dest[i] = src[i];
			i++;
		}
	dest[i] = src[i];
	return (dest);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
