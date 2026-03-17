/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 17:39:26 by dminh             #+#    #+#             */
/*   Updated: 2026/03/17 12:53:45 by dminh            ###   ########.fr       */
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

void	ft_built_in_only(t_args *args, t_token *token)
{
	int	input;
	int	output;

	input = dup(STDIN_FILENO);
	output = dup(STDOUT_FILENO);
	if (args->cmd->infile)
	{
		args->cmd->in_fd = open(args->cmd->infile, O_RDONLY);
		dup2(args->cmd->in_fd, STDIN_FILENO);
	}
	if (args->cmd->outfile)
	{
		args->cmd->out_fd = open(args->cmd->outfile, O_CREAT | O_WRONLY
				| O_TRUNC, S_IRWXU);
		dup2(args->cmd->out_fd, STDOUT_FILENO);
	}
	ft_built_in_cmds(args, NULL, token);
	if (args->cmd->infile)
		close(args->cmd->in_fd);
	if (args->cmd->outfile)
		close(args->cmd->out_fd);
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	close(input);
	close(output);
}

void	ft_built_in(t_args *args, t_cmd *cmd, t_token *token, int *reading)
{
	if (*reading)
		dup2(*reading, STDIN_FILENO);
	if (args->cmd->infile)
	{
		cmd->in_fd = open(cmd->infile, O_RDONLY);
		dup2(cmd->in_fd, STDIN_FILENO);
	}
	if (cmd->next)
		dup2(args->fd[PIPE_WRITE], STDOUT_FILENO);
	if (cmd->outfile)
	{
		cmd->out_fd = open(cmd->outfile, O_CREAT | O_WRONLY
				| O_TRUNC, S_IRWXU);
		dup2(cmd->out_fd, STDOUT_FILENO);
	}
	ft_built_in_cmds(args, cmd, token);
	ft_close_fds(cmd, args->fd, reading);
	exit(EXIT_SUCCESS);
}
