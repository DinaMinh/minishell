/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 14:23:19 by dminh             #+#    #+#             */
/*   Updated: 2026/03/26 23:14:48 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_next_token(t_token *token, t_args *args)
{
	if (token->type != TOKEN_WORD && token->type != TOKEN_FILENAME)
	{
		if (!token->next || (token->next->type != TOKEN_WORD
				&& token->next->type != TOKEN_FILENAME))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			if (token->next)
				ft_putstr_fd(token->next->content, 2);
			else
				ft_putstr_fd("newline", 2);
			ft_putstr_fd("'\n", 2);
			args->return_val = 2;
			return (1);
		}
	}
	return (0);
}

int	ft_check_pipe(t_token *token, t_args *args)
{
	if (token->type == TOKEN_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(token->content, 2);
		ft_putstr_fd("'\n", 2);
		args->return_val = 2;
		return (1);
	}
	return (0);
}

static int	ft_check_double_pipe(t_token *token, t_args *args)
{
	if (!token->next || token->next->type == TOKEN_PIPE)
	{
		if (!token->next)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
			ft_putstr_fd("`newline'\n", 2);
		}
		else
			ft_check_pipe(token->next, args);
		args->return_val = 2;
		return (1);
	}
	return (0);
}

int	ft_valid_syntax(t_token *token, t_args *args)
{
	t_token	*tmp;

	tmp = token;
	if (tmp && tmp->type == TOKEN_PIPE)
		return (ft_check_pipe(tmp, args));
	while (tmp)
	{
		if (tmp->type != TOKEN_WORD && tmp->type != TOKEN_FILENAME
				&& tmp->type != TOKEN_PIPE)
		{
			if (ft_check_next_token(tmp, args))
				return (EXIT_FAILURE);
		}
		else if (tmp->type == TOKEN_PIPE)
		{
			if (ft_check_double_pipe(tmp, args))
				return (EXIT_FAILURE);
		}
		tmp = tmp->next;
	}
	return (0);
}
