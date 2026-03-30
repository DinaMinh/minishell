/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 11:17:27 by dminh             #+#    #+#             */
/*   Updated: 2026/03/30 12:40:20 by dminh            ###   ########.fr       */
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

void	ft_print_no_such_file(t_args *args, char *cmd)
{
	ft_putstr_fd("minishell: '", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
	args->return_val = 127;
}

void	ft_handle_errors(t_args *args, t_token *token, t_cmd *cmd)
{
	struct stat	path_stat;

	if (stat(cmd->path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->path, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		ft_exit(args, token, 126);
	}
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
