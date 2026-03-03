/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:15:17 by dminh             #+#    #+#             */
/*   Updated: 2026/01/22 16:39:17 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	long	i;
	int		count;

	i = n;
	count = 0;
	if (i < 0)
	{
		i = -i;
		ft_putchar('-');
	}
	if (i > 9)
		ft_putnbr(i / 10);
	count += ft_putchar(i % 10 + 48);
	return (count);
}
