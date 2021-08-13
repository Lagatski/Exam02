#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int result;
int width;
int dot;

static void ft_putchar(char c)
{
    write(1, &c, 1);
    result += 1;
}

static void ft_putstr(char *str, int len)
{
    while (*str != '\0' && len > 0)
    {
        ft_putchar(*str);
        str++;
        len--;
    }
}

static int ft_strlen(char *str)
{
    int len = 0;
    while (*str++ != '\0')
        len++;
    return (len);
}

static char *ft_itoa(unsigned long nbr, int base)
{
    unsigned long temp_nbr = nbr;
    int len = 0;
    char *str = NULL;
    if (nbr == 0)
        len++;
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
            str[len - 1] += 'a' - 10;
        else
            str[len - 1] += '0';
        nbr /= base;
        len--;
    }
    return (str);
}

static void ft_printf_x(unsigned long nbr)
{
    char *str;
    str = ft_itoa(nbr, 16);
    int len = ft_strlen(str);

    if (dot != -1 && dot > len)
        len = dot;
    while (width > len)
        { ft_putchar(' '); width--; }
    while (len > ft_strlen(str))
        { ft_putchar('0'); len--; }
    ft_putstr(str, ft_strlen(str));
    free(str);
}

static void ft_printf_d(long nbr)
{
    char *str;
    int minus = 0;
    if (nbr < 0)
    {
		minus = 1;
		nbr *= -1;
	}
    str = ft_itoa(nbr, 10);
    int len = ft_strlen(str);

    if (dot != -1 && dot > len) // если есть точность и она больше разрядности числа -> разрядность = точности
        len = dot;
    if (minus == 1 && width > 0) // если число отрицательное, то уменьшим ширину на 1, для знака -
    	width--;
    while (width > len) // пока ширина больше разрядности будем писать пробелы
    {
		ft_putchar(' ');
		width--;
	}
    if (minus == 1) // пишем знак "-" если число отрицательное 
    	ft_putchar('-');
    while (len > ft_strlen(str)) // пишем нули, если точность больше разрядности
    {
		ft_putchar('0');
		len--;
	}
	if ((nbr != 0 && dot == 0) || dot )
    	ft_putstr(str, ft_strlen(str)); // пишем само число
    free(str);
}

static void ft_printf_s(char *str)
{
    int len = ft_strlen(str);

    if (dot != -1 && dot < len)
        len = dot;
    while (width > len)
        { ft_putchar(' '); width--; }
    ft_putstr(str, len);
}

int ft_printf(const char *str, ... )
{
    result = 0;
    int i = 0;
    va_list arg;

    va_start(arg, str);
    while (str[i] != '\0')
    {
        if (str[i] == '%' && str[i+1] != '\0')
        {
            i++;
            width = 0;
            dot = -1;
            while (str[i] >= '0' && str[i] <= '9')
            {
                width = width * 10 + (str[i] - '0');
                i++;
            }
            if (str[i] == '.')
            {
                dot = 0;
                i++;
                while (str[i] >= '0' && str[i] <= '9')
                {
                    dot = dot * 10 + (str[i] - '0');
                    i++;
                }
            }
            if (str[i] == 's')
                ft_printf_s(va_arg(arg, char *));
            else if (str[i] == 'x')
                ft_printf_x(va_arg(arg, unsigned int));
            else if (str[i] == 'd')
                ft_printf_d(va_arg(arg, int));
            else
                ft_putchar(str[i]);
        }
        else
            ft_putchar(str[i]);
        i++;

    }
    va_end(arg);
    return (result);
}

int main(void)
{
	int res;

	res = ft_printf("|string is %.1d|", 0);
	printf("\nres is %d\n", res);
	res = printf("|string is %.1d|", 0);
	printf ("\nres is %d\n", res);
	return (0);
}
