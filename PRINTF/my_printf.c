#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

int res = 0;
int dot;
int width;

static void ft_putchar(char c)
{
	write(1, &c, 1);
	res += 1;
}

static void ft_putstr(char *str, int len)
{
	while (str && len > 0)
	{
		ft_putchar(*str);
		str++;
		len --;
	}
}

static int ft_strlen(char *str)
{
	int	len = 0;
	while (str[len])
		len++;
	return(len);
}


static char *ft_itoa(unsigned long nbr, int base)
{
	unsigned long temp_nbr = nbr;
	int len = 0;
	char *str = NULL;

	if (nbr == 0)
		len = 1;
	while (temp_nbr > 0)
	{
		temp_nbr /= base;
		len++;
	}
	str = malloc(len + 1);
	str[len] = '\0';
	while (len > 0)
	{
		str[len - 1] = nbr % base;
		if (nbr % base > 9)
			str[len] += 'a' - 10;
		else
			str[len] += 48;
		nbr /= base;
		len--;
	}
	return (str);
}

int	ft_printf(const char *str, ...)
{
	int i;
	va_list arg;
	
	va_start(arg, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i+1] != '\0')
		{
			width = 0;
			dot = -1;
			i++;
			while (str[i] > '0' && str[i] < '9')
			{
				width = width * 10 + str[i] - 48;
				i++;
			}
			if (str[i] == '.')
			{
				dot == 0;
				i++;
				while (str[i] > '0' && str[i] < '9')
				{
					dot = dot * 10 + str[i] - 48;
					i++;
				}
			}
			if (str[i] == 's')
				ft_print_s(va_arg(arg, char *));
			else if (str[i] == 'd'	)
				ft_print_d(va_arg(arg, int));
			else if (str[i] == 'x')
				ft_print_x(va_arg(arg, unsigned int));
			else
				ft_putchar(str[i]);
		}
		else
			ft_putchar(str[i]);
		i++;
	}
	va_end(arg);
	return(res);
}

int	main(void)
{
	int a;

	a = ft_printf("hello %d", 5);
	printf("res %d", a);
	a = printf("hello %d", 5);
	printf("res %d", a);
	return (0);
}
