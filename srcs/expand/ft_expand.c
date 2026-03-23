/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 23:40:58 by ebourdet          #+#    #+#             */
/*   Updated: 2026/03/20 15:28:35 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_normal_var(char *str, int i, char **new_str, t_args *args)
{
	int		len;
	char	*var_name;
	t_env	*node;

	len = 0;
	while (str[i + len] && (ft_isalnum(str[i + len]) || str[i + len] == '_'))
		len++;
	var_name = ft_substr(str, i, len);
	node = find_env_node(args->env, var_name);
	if (node && node->value)
		*new_str = ft_append_str(*new_str, node->value);
	free(var_name);
	return (len);
}

int	handle_dollar(char *str, int i, char **new_str, t_args *args)
{
	char	*status;

	if (str[i] == '?')
	{
		status = ft_itoa(args->return_val);
		*new_str = ft_append_str(*new_str, status);
		free(status);
		return (1);
	}
	if (!str[i] || (!ft_isalnum(str[i]) && str[i] != '_'))
	{
		*new_str = ft_append_char(*new_str, '$');
		return (0);
	}
	return (expand_normal_var(str, i, new_str, args));
}

char	*expand_and_strip(char *str, t_args *args)
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
		else if (str[i] == '$' && !in_sq)
			i += handle_dollar(str, i + 1, &res, args);
		else
			res = ft_append_char(res, str[i]);
		i++;
	}
	return (res);
}

static char	*ft_handle_heredoc(t_token *token, char *str)
{
	if (ft_strchr(str, '\'') || ft_strchr(str, '"'))
		return (ft_strip_quotes_delimiter(str));
	token->exp_heredoc = true;
	return (str);
}

void	ft_expand_tokens(t_token **tokens, t_args *args, bool heredoc)
{
	t_token	*tmp;
	t_token	*next_node;
	char	*expanded;

	tmp = *tokens;
	expanded = NULL;
	while (tmp)
	{
		next_node = tmp->next;
		if (heredoc)
		{
			tmp->content = ft_handle_heredoc(tmp, tmp->content);
			heredoc = false;
		}
		else if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_FILENAME)
			ft_expand_word(expanded, tmp, tokens, args);
		else if (tmp->type == TOKEN_HEREDOC)
			heredoc = true;
		tmp = next_node;
	}
}
