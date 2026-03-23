/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 14:26:00 by dminh             #+#    #+#             */
/*   Updated: 2026/03/17 16:12:11 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

int	ft_is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

int	ft_add_word(t_token **token, int len, char *line)
{
	char	*res;

	res = ft_substr(line, 0, len);
	if (!res)
		return (false);
	if (ft_token_addback(token, res, TOKEN_WORD))
	{
		free(res);
		return (false);
	}
	return (true);
}

int	ft_handle_quotes(char *line, int *end, char *quote)
{
	*quote = line[*end];
	(*end)++;
	while (line[*end] && line[*end] != *quote)
		(*end)++;
	if (!line[*end])
		return (1);
	if (line[*end] == *quote)
		(*end)++;
	return (0);
}
