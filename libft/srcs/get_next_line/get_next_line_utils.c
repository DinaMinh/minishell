/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:53:55 by dminh             #+#    #+#             */
/*   Updated: 2026/01/23 19:57:31 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_is_nl(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\n')
			return (&str[i]);
		i++;
	}
	return (NULL);
}

char	*ft_set_line(char *s1, char *s2, size_t *len)
{
	char	*joined;
	ssize_t	i;
	size_t	s2_len;

	if (!s2 || !s2[0])
		return (free(s1), NULL);
	s2_len = 0;
	while (s2[s2_len] && s2[s2_len] != '\n')
		s2_len++;
	if (s2[s2_len] == '\n')
		s2_len++;
	joined = malloc(sizeof(*joined) * (*len + s2_len + 1));
	if (!joined)
		return (free(s1), NULL);
	i = -1;
	while (++i < (ssize_t)(*len))
		joined[i] = s1[i];
	i = -1;
	while (++i < (ssize_t)s2_len)
		joined[i + (ssize_t)(*len)] = s2[i];
	joined[i + (ssize_t)(*len)] = '\0';
	*len += s2_len;
	free(s1);
	return (joined);
}

void	ft_del_printed(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			while (buffer[++i])
				buffer[j++] = buffer[i];
			buffer[j] = '\0';
			return ;
		}
		i++;
	}
	buffer[0] = '\0';
}
