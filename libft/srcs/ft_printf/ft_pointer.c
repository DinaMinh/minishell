/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:05:31 by dminh             #+#    #+#             */
/*   Updated: 2026/01/22 16:32:54 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hex_ptr(unsigned long long ptr)
{
	char	*hex;
	int		written;

	hex = "0123456789abcdef";
	written = 0;
	if (ptr < 16)
		return (written += ft_putchar_len(hex[ptr]));
	written += ft_hex_ptr(ptr / 16);
	written += ft_hex_ptr(ptr % 16);
	return (written);
}

int	ft_putptr_len(size_t ptr)
{
	int	written;

	written = 0;
	if (!ptr)
		return (written += ft_putstr_len("(nil)"));
	written += ft_putstr_len("0x");
	written += ft_hex_ptr(ptr);
	return (written);
}
