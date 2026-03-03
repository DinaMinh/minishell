/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:15:17 by dminh             #+#    #+#             */
/*   Updated: 2026/01/22 16:39:16 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	long	i;
	int		count;

	i = n;
	count = 0;
	if (i < 0)
	{
		i = -i;
		ft_putchar_fd('-', fd);
	}
	if (i > 9)
		ft_putnbr_fd(i / 10, fd);
	count += ft_putchar_fd(i % 10 + 48, fd);
	return (count);
}
