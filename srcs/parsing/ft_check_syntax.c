/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 14:23:19 by dminh             #+#    #+#             */
/*   Updated: 2026/03/20 14:23:47 by dminh            ###   ########.fr       */
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
