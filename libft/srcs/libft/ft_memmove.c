/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:16:42 by dminh             #+#    #+#             */
/*   Updated: 2026/01/22 16:33:07 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	char			*d;
	unsigned char	*temp;

	d = (char *)dest;
	temp = (unsigned char *)src;
	i = -1;
	if (!src && !dest)
		return (NULL);
	if (dest > src)
	{
		i = n;
		while (i-- > 0)
			d[i] = temp[i];
	}
	else
	{
		while (++i < n)
			d[i] = temp[i];
	}
	return (d);
}
