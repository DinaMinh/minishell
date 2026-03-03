/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:52:12 by dminh             #+#    #+#             */
/*   Updated: 2026/01/22 16:32:55 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_len(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_len(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (len += ft_putstr_len("(null)"));
	while (str[len])
	{
		write(1, &str[len], 1);
		len++;
	}
	return (len);
}
