/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:15:42 by dminh             #+#    #+#             */
/*   Updated: 2026/01/22 16:33:07 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*last;

	i = 0;
	last = (char *)str;
	while (*str)
	{
		if (*str++ == (unsigned char)c)
		{
			last = (char *)(str - 1);
			i = 1;
		}
	}
	if (i == 1)
		return (last);
	if ((unsigned char)c == '\0')
		return ((char *)str);
	else
		return (NULL);
}
