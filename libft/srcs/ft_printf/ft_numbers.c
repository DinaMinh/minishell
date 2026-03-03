/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:05:59 by dminh             #+#    #+#             */
/*   Updated: 2026/01/22 16:32:53 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_len(int n)
{
	char	*number;
	int		len;

	number = NULL;
	number = ft_itoa(n);
	len = 0;
	while (number[len])
	{
		write(1, &number[len], 1);
		len++;
	}
	free(number);
	return (len);
}

int	ft_putlong_len(long n)
{
	int	written;

	written = 0;
	if (n > 9)
		written += ft_putlong_len(n / 10);
	return (written += ft_putchar_len(n % 10 + 48));
}

int	ft_putudec_len(unsigned int n)
{
	int	written;

	written = 0;
	if (n > 9)
		written += ft_putudec_len(n / 10);
	return (written += ft_putchar_len(n % 10 + 48));
}

int	ft_to_hex(unsigned int n, int spec)
{
	int		written;
	char	*hex;

	written = 0;
	hex = "0123456789abcdef";
	if (n < 16)
	{
		if (spec == 'X' && hex[n] >= 'a' && hex[n] <= 'f')
			return (written += ft_putchar_len(hex[n] - 32));
		else
			return (written += ft_putchar_len(hex[n]));
	}
	written += ft_to_hex(n / 16, spec);
	written += ft_to_hex(n % 16, spec);
	return (written);
}

int	ft_putnbr_hex(unsigned int n, int spec)
{
	int	written;

	if (n == 0)
		return (write(1, "0", 1));
	written = 0;
	return (written += ft_to_hex(n, spec));
}
