/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:55:42 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/29 12:10:10 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

static int	ft_othercases(char *c)
{
	char	str[3];

	str[0] = '%';
	str[1] = *c;
	str[2] = '\0';
	ft_putstr_errnull(str, 1);
	return (2);
}

static int	ft_format_arg(char c, va_list arg, int fd)
{
	int	siz;

	if (c == '%')
		siz = ft_putchar('%', fd);
	else if (c == 'c')
		siz = ft_putchar(va_arg(arg, int), fd);
	else if (c == 's')
		siz = ft_putstr_errnull(va_arg(arg, char *), fd);
	else if (c == 'p')
		siz = ft_putaddress(va_arg(arg, void *));
	else if (c == 'x')
		siz = ft_putunsint(va_arg(arg, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		siz = ft_putunsint(va_arg(arg, unsigned int), "0123456789ABCDEF");
	else if (c == 'd' || c == 'i')
		siz = ft_putnbr(va_arg(arg, int), "0123456789", fd);
	else if (c == 'u')
		siz = ft_putunsint(va_arg(arg, unsigned int), "0123456789");
	else
		siz = ft_othercases(va_arg(arg, char *));
	return (siz);
}

int	ft_printf(const char *format, ...)
{
	va_list	ptr;
	int		i;
	int		siz;

	i = 0;
	siz = 0;
	if (!format)
		return (-1);
	va_start(ptr, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			siz += ft_format_arg(format[i], ptr, 1);
		}
		else
		{
			ft_putchar(format[i], 1);
			siz++;
		}
		i++;
	}
	va_end(ptr);
	return (siz);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	ptr;
	int		i;
	int		siz;

	i = 0;
	siz = 0;
	if (!format)
		return (-1);
	va_start(ptr, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			siz += ft_format_arg(format[i], ptr, fd);
		}
		else
		{
			ft_putchar(format[i], fd);
			siz++;
		}
		i++;
	}
	va_end(ptr);
	return (siz);
}
