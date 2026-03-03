/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:04:40 by dminh             #+#    #+#             */
/*   Updated: 2026/01/22 16:33:07 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*found;

	if (!big && !len)
		return (NULL);
	i = 0;
	found = (char *)big;
	if (little[0] == 0 || little == big)
		return (found);
	while (found[i] && i < len)
	{
		j = 0;
		while (found[i + j] && found[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return (&found[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
