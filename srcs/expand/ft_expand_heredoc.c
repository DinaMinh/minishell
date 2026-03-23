/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 23:06:11 by dminh             #+#    #+#             */
/*   Updated: 2026/03/20 11:45:04 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_heredoc(char *body, t_args *args)
{
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	if (!body)
		return (NULL);
	while (body[i])
	{
		if (body[i] == '$')
			i += handle_dollar(body, i + 1, &res, args);
		else
			res = ft_append_char(res, body[i]);
		i++;
	}
	free(body);
	if (!res)
		return (ft_strdup(""));
	return (res);
}

char	*ft_strip_quotes_delimiter(char *str)
{
	int		i;
	int		in_sq;
	int		in_dq;
	char	*res;

	i = 0;
	in_sq = 0;
	in_dq = 0;
	res = NULL;
	while (str[i])
	{
		if (str[i] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (str[i] == '"' && !in_sq)
			in_dq = !in_dq;
		else
			res = ft_append_char(res, str[i]);
		i++;
	}
	free(str);
	return (res);
}
