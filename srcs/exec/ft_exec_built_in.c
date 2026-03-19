/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 17:39:26 by dminh             #+#    #+#             */
/*   Updated: 2026/03/19 11:14:49 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_built_in_cmds(t_args *args, t_cmd *cmd, t_token *token)
{
	if (!cmd)
		cmd = args->cmd;
	if (ft_strncmp(cmd->cmd[0], ECHO, ECHO_LEN) == 0)
		args->return_val = builtin_echo(cmd->cmd, STDOUT_FILENO);
	else if (ft_strncmp(cmd->cmd[0], CD, CD_LEN) == 0)
		args->return_val = builtin_cd(cmd->cmd, &args->env);
	else if (ft_strncmp(cmd->cmd[0], PWD, PWD_LEN) == 0)
		args->return_val = builtin_pwd(STDOUT_FILENO);
	else if (ft_strncmp(cmd->cmd[0], EXPORT, EXPORT_LEN) == 0)
		args->return_val = builtin_export(args, &args->env);
	else if (ft_strncmp(cmd->cmd[0], UNSET, UNSET_LEN) == 0)
		args->return_val = builtin_unset(args, &args->env);
	else if (ft_strncmp(cmd->cmd[0], ENV, ENV_LEN) == 0)
		args->return_val = builtin_env(args->env, STDOUT_FILENO);
	else if (ft_strncmp(cmd->cmd[0], EXIT, EXIT_LEN) == 0)
		builtin_exit(args, token, cmd->cmd);
}

static int	ft_check_dup(t_args *args, int input, int output)
{
	if (input < 0 || output < 0)
	{
		args->return_val = 1;
		perror("minishell: dup");
		if (input >= 0)
			close(input);
		if (output >= 0)
			close(output);
		return (1);
	}
	return (EXIT_SUCCESS);
}

static void	ft_reset_dup(int input, int output)
{
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	close(input);
	close(output);
}

void	ft_built_in_only(t_args *args, t_token *token, int *reading)
{
	int	input;
	int	output;

	input = dup(STDIN_FILENO);
	output = dup(STDOUT_FILENO);
	if (ft_check_dup(args, input, output))
		return ;
	if (args->cmd->redir)
	{
		if (ft_open_fds(args->cmd, args->fd))
		{
			dup2(input, STDIN_FILENO);
			dup2(output, STDOUT_FILENO);
			close(input);
			close(output);
			args->return_val = 1;
			return ;
		}
	}
	ft_built_in_cmds(args, NULL, token);
	if (args->cmd->redir)
		ft_close_fds(args->cmd, args->fd, reading);
	ft_reset_dup(input, output);
}

void	ft_built_in(t_args *args, t_cmd *cmd, t_token *token, int *reading)
{
	if (*reading)
		dup2(*reading, STDIN_FILENO);
	if (ft_open_fds(cmd, args->fd))
		ft_exit(args, token, EXIT_FAILURE);
	ft_built_in_cmds(args, cmd, token);
	ft_close_fds(cmd, args->fd, reading);
	ft_exit(args, token, args->return_val);
}
