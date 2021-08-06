/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anwoonbe <anwoonbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 11:42:28 by anwoonbe          #+#    #+#             */
/*   Updated: 2021/08/06 10:52:08 by anwoonbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_pars
{
	int	cnt;
	int	fmt;
	int	nbr;
	int	str;
}				t_pars;

typedef struct s_mod
{
	int	width;
	int	acc;
	int	dot;
}				t_mod;

t_pars ft_init_p()
{
	t_pars p;

	p.cnt = 0;
	p.fmt = 0;
	p.nbr = 0;
	p.str = 0;
	return(p);
}

t_mod ft_init_mod()
{
	t_mod	mod;

	mod.width = 0;
	mod.acc = 0;
	mod.dot = 0;
	return (mod);
}

void	ft_putnbr(int n)
{
	char	c;

	if (n == -2147483648)
	{
		write (1, "-2147483648", 11);
	}
	else
	{
		if (n < 0)
		{
			write (1, "-", 1);
			n *= -1;
			ft_putnbr(n);
		}
		else if(n < 10)
		{
			c = n + 48;
			write (1, &c, 1);
		}
		else
		{
			ft_putnbr(n / 10);
			c = (n % 10) + 48;
			write (1, &c, 1);
		}
	}
}

void	ft_putstrchar(char ch, int num)
{
	int i;
	
	i = 0;
	while (i < num)
	{
		write(1, &ch, 1);
		i++;
	}
}

int	ft_output(char spec, va_list arg, t_mod mod)
{
	int		count;
	int		i;
	int		res;
	char	*s;

	if (spec == 'd')
	{
		res = 0;
		i = va_arg(arg, int);
		count = i;
		while (count)
		{
			count = count / 10;
			res++;
		}
		if (mod.width > mod.acc)
		{
			if (mod.acc > res)
			{
				if (i == 0)
				{
					ft_putstrchar(' ', mod.width - mod.acc);
					ft_putstrchar('0', mod.acc - res);
					count = mod.width;
				}
				else if (i < 0)
				{
					ft_putstrchar(' ', mod.width - mod.acc - 1);
					write(1, "-", 1);
					i *= -1;
					ft_putstrchar('0', mod.acc - res);
					ft_putnbr(i);
					count = mod.width;
				}
				else
				{
					ft_putstrchar(' ', mod.width - mod.acc);
					ft_putstrchar('0', mod.acc - res);
					ft_putnbr(i);
					count = mod.width;
				}
			}
			else if (mod.acc <= res)
			{
				if (i == 0)
				{
					ft_putstrchar(' ', mod.width - res);
					if (mod.width > res)
						count = mod.width;
					else
						count = res;
				}
				else if (i < 0)
				{
					ft_putstrchar(' ', mod.width - res - 1);
					write(1, "-", 1);
					i *= -1;
					ft_putnbr(i);
					if (mod.width > res)
						count = mod.width;
					else
						count = res + 1;
				}
				else
				{
					ft_putstrchar(' ', mod.width - res);
					ft_putnbr(i);
					if (mod.width > res)
						count = mod.width;
					else
						count = res;
				}
			}
		}
		else if (mod.width <= mod.acc)
		{
			if (mod.acc > res)
			{
				if (i == 0)
				{
					ft_putstrchar('0', mod.acc - res);
					count = mod.acc;
				}
				else if (i < 0)
				{
					write (1, "-", 1);
					i *= -1;
					ft_putstrchar('0', mod.acc - res);
					ft_putnbr(i);
					count = mod.acc + 1;
				}
				else
				{
					ft_putstrchar('0', mod.acc - res);
					ft_putnbr(i);
					count = mod.acc;
				}
			}
			else if (mod.acc <= res)
			{
				if (i == 0)
					count = 0;
				else if (i < 0)
				{
					ft_putnbr(i);
					count = res + 1;
				}
				else
				{
					ft_putnbr(i);
					count = res;
				}
			}
		}
	}
	// else if (spec == 's')
	// {

	// }
	else if (spec == 'x')
	{
		if (i % 16 > 10)
	}
	return (count);
}

int	ft_flag(const char *s, int i, va_list arg)
{
	int		count;
	t_mod	mod;

	count = 0;
	mod = ft_init_mod();
	i++;
	if (s[i] >= '0' && s[i] <= '9')
	{
		while (s[i] != 'd' && s[i] != 's' && s[i] != 'x' && s[i] != '.' && s[i])
		{
			if (mod.width == 0)
				mod.width = s[i] - 48;
			else
				mod.width *= 10 + s[i] - 48;
			i++;
		}
	}
	if ((s[i] == '.' && (s[i + 1] >= '0' && s[i + 1] <= '9') && s[i]) || s[i] == '.')
	{
		mod.dot = 1;
		i++;
		while (s[i] >= '0' && s[i] <= '9')
		{
			if (mod.acc == 0)
				mod.acc = s[i] - 48;
			else
				mod.acc *= 10 + s[i] - 48;
			i++;
		}
	}
	// printf ("\nDot is %d", mod.dot);
	// printf ("\nWidth is %d", mod.width);
	// printf ("\nAcc is %d", mod.acc);
	count = ft_output(s[i], arg, mod);
	return (count);
}

int	ft_parsing(const char *s, va_list arg)
{
	t_pars	p;

	p = ft_init_p();
	while (s[p.cnt])
	{
		if (s[p.cnt] == '%' && s[p.cnt + 1])
		{
			p.str = p.cnt;
			p.cnt++;
			p.fmt += 2;
			while (s[p.cnt] && (s[p.cnt] != 's' || s[p.cnt] != 'd' 
				|| s[p.cnt] != 'x'))
			{				
				if (s[p.cnt] && (s[p.cnt] == 's' || s[p.cnt] == 'd' 
				|| s[p.cnt] == 'x'))
				{
					p.nbr = ft_flag(s, p.str, arg);
					p.cnt++;
				}
				else if (s[p.cnt])
				{
					p.cnt++;
					p.fmt++;
				}
			}
			p.cnt--;
			p.fmt--;
		}
		else if ((s[p.cnt] && s[p.cnt + 1]) || s[p.cnt] != '%')
		{
			write (1, &s[p.cnt], 1);
			p.cnt++;
		}
		else
			break;
	}
	return (p.cnt - p.fmt + p.nbr);
}

int	ft_printf(const char *s, ...)
{
	int	count;
	va_list	arg;

	va_start(arg, s);
	count = ft_parsing(s, arg);
	va_end(arg);
	return (count);
}

int	main(void)
{
	int res;

	res = ft_printf("|string is %.5d|", 0);
	printf("\nres is %d\n", res);
	res = printf("|string is %.5d|", 0);
	printf ("\nres is %d\n", res);
	return (0);
}