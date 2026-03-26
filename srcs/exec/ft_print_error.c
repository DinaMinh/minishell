/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 11:17:27 by dminh             #+#    #+#             */
/*   Updated: 2026/03/26 11:59:41 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_error_cmd(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

void	ft_print_not_exec(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
}

void	ft_handle_errors(t_args *args, t_token *token, t_cmd *cmd)
{
	if (access(cmd->path, F_OK) != 0)
	{
		ft_print_error_cmd(cmd->path);
		ft_exit(args, token, 127);
	}
	else if (access(cmd->path, X_OK) != 0)
	{
		ft_print_not_exec(cmd->path);
		ft_exit(args, token, NOT_EXEC);
	}
}
