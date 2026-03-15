/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 14:26:00 by dminh             #+#    #+#             */
/*   Updated: 2026/03/05 14:26:00 by dminh            ###   ########.fr       */
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

int	ft_handle_operator(t_token **token, char *line, int *i)
{
	int	err;

	err = 0;
	if (ft_strncmp("<<", &line[*i], 2) == 0)
	{
		err = ft_token_addback(token, ft_strdup("<<"), TOKEN_HEREDOC);
		*i += 2;
	}
	else if (ft_strncmp(">>", &line[*i], 2) == 0)
	{
		err = ft_token_addback(token, ft_strdup(">>"), TOKEN_APPEND);
		*i += 2;
	}
	else
	{
		if (line[*i] == '|')
			err = ft_token_addback(token, ft_strdup("|"), TOKEN_PIPE);
		else if (line[*i] == '<' || line[*i] == '>')
			err = ft_handle_redir(token, line, i);
		(*i)++;
	}
	return (err);
}

int	ft_add_word(t_token **token, int len, char *line, char quote)
{
	char	*res;

	if (quote != 0)
		res = ft_substr(line, 0, len - 1);
	else
		res = ft_substr(line, 0, len);
	if (!res || ft_token_addback(token, res, TOKEN_WORD))
		return (false);
	return (true);
}

int	ft_handle_word(t_token **token, char *line, int *start)
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
	if (ft_add_word(token, end - *start, &line[*start], quote) == false)
		return (1);
	*start = end;
	return (0);
}
