/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:14:54 by dminh             #+#    #+#             */
/*   Updated: 2026/01/22 16:32:59 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_size(int n)
{
	size_t	size;

	size = 1;
	if (n < 0)
		size++;
	while (n / 10)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

static char	*ft_attribution(char *itoa, size_t i, long n)
{
	if (n == 0)
	{
		itoa[0] = '0';
		itoa[i] = '\0';
		return (itoa);
	}
	if (n < 0)
	{
		n = -n;
		itoa[0] = '-';
	}
	itoa[i] = '\0';
	i -= 1;
	while (n / 10)
	{
		itoa[i] = n % 10 + 48;
		n /= 10;
		i--;
	}
	itoa[i] = n % 10 + 48;
	return (itoa);
}

char	*ft_itoa(int n)
{
	size_t	i;
	char	*itoa;

	i = ft_get_size(n);
	itoa = (char *)ft_calloc(i + 1, sizeof(char));
	if (!itoa)
		return (NULL);
	ft_attribution(itoa, i, n);
	return (itoa);
}
