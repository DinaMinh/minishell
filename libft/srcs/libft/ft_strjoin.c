/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:04:14 by dminh             #+#    #+#             */
/*   Updated: 2026/01/22 16:33:07 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	char	*d;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	d = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!d)
		return (NULL);
	while (*s1)
	{
		d[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		d[i] = *s2;
		s2++;
		i++;
	}
	d[i] = '\0';
	return (d);
}
