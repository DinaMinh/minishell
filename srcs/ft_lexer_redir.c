/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:38:06 by dminh             #+#    #+#             */
/*   Updated: 2026/03/16 00:24:51 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_filename(t_token **token, int len, char *line, char quote)
{
	char	*res;

	if (quote != 0)
		res = ft_substr(line, 0, len - 1);
	else
		res = ft_substr(line, 0, len);
	if (!res || ft_token_addback(token, res, TOKEN_FILENAME))
		return (false);
	return (true);
}

int	ft_handle_filename(t_token **token, char *line, int *start)
{
	char	quote;
	int		end;

	end = *start;
	quote = 0;
	while (line[end] && ft_is_operator(line[end]) == false
		&& ft_is_blank(line[end]) == false)
	{
		if (line[end] == D_QUOTE || line[end] == S_QUOTE)
		{
			if (end == *start)
				(*start)++;
			quote = line[end];
			end++;
			while (line[end] && line[end] != quote)
				end++;
		}
		else
			end++;
	}
	if (ft_add_filename(token, end - *start, &line[*start], quote) == false)
		return (1);
	*start = end;
	return (0);
}

int	ft_handle_redir(t_token **token, char *line, int *i)
{
	int	err;

	err = 0;
	if (line[*i] == '<')
		err = ft_token_addback(token, ft_strdup("<"), TOKEN_REDIR_IN);
	else if (line[*i] == '>')
		err = ft_token_addback(token, ft_strdup(">"), TOKEN_REDIR_OUT);
	(*i)++;
	while (line[*i] && ft_is_blank(line[*i]))
		(*i)++;
	if (!line[*i])
		return (0);
	err = ft_handle_filename(token, line, i);
	return (err);
}
