/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:49:41 by dminh             #+#    #+#             */
/*   Updated: 2026/01/22 16:32:55 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_spec(char spec, va_list ap)
{
	if (spec == 'c')
		return (ft_putchar_len(va_arg(ap, int)));
	else if (spec == 's')
		return (ft_putstr_len(va_arg(ap, char *)));
	else if (spec == 'p')
		return (ft_putptr_len(va_arg(ap, size_t)));
	else if (spec == 'd' || spec == 'i')
		return (ft_putnbr_len(va_arg(ap, int)));
	else if (spec == 'x' || spec == 'X')
		return (ft_putnbr_hex(va_arg(ap, unsigned int), spec));
	else if (spec == 'u')
		return (ft_putudec_len(va_arg(ap, unsigned int)));
	else if (spec == '%')
		return (write(1, "%", 1));
	else if (spec == '@')
		return (ft_putlong_len(va_arg(ap, long)));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		written;

	if (!format)
		return (-1);
	va_start(ap, format);
	written = 0;
	while (*format)
	{
		if (*format == '%')
			written += ft_print_spec(*++format, ap);
		else
			written += write(1, format, 1);
		++format;
	}
	va_end(ap);
	return (written);
}
