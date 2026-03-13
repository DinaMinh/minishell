/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:37:16 by dminh             #+#    #+#             */
/*   Updated: 2026/03/13 17:59:38 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_pipe_child(t_cmd *cmd, int fd[2], int *reading)
{
	if (*reading != 0)
	{
		dup2(*reading, STDIN_FILENO);
		close(*reading);
	}
	if (cmd->next)
	{
		dup2(fd[PIPE_WRITE], STDOUT_FILENO);
		close(fd[PIPE_WRITE]);
		close(fd[PIPE_READ]);
	}
	execve(cmd->cmd_path, cmd->cmd, NULL);
}

static void	ft_pipe_parent(t_cmd *cmd, int fd[2], int *reading)
{
	if (*reading != 0)
		close(*reading);
	if (cmd->next)
	{
		close(fd[PIPE_WRITE]);
		*reading = fd[PIPE_READ];
	}
}

void	ft_exec_built_in(t_args *args, int *reading)
{
	(void)reading;
	if (!cmd->next)
	{
		if (ft_strncmp(args->cmd->cmd[0], ECHO, ECHO_LEN) == 0)
			return ;
		else if (ft_strncmp(args->cmd->cmd[0], CD, CD_LEN) == 0)
			return ;
		else if (ft_strncmp(args->cmd->cmd[0], PWD, PWD_LEN) == 0)
			builtin_pwd(STDOUT_FILENO);
		else if (ft_strncmp(args->cmd->cmd[0], EXPORT, EXPORT_LEN) == 0)
			builtin_export(args, &args->env);
		else if (ft_strncmp(args->cmd->cmd[0], UNSET, UNSET_LEN) == 0)
			builtin_unset(args, &args->env);
		else if (ft_strncmp(args->cmd->cmd[0], ENV, ENV_LEN) == 0)
			builtin_env(args->env, STDOUT_FILENO);
		else if (ft_strncmp(args->cmd->cmd[0], EXIT, EXIT_LEN) == 0)
			return ;
	}
	else
}

void	ft_exec_child(t_token *token, t_args *args, int *reading)
{
	if (token->type == TOKEN_REDIR_IN)
		ft_infile_child(args->cmd, args->fd, reading);
	else if (token->type == TOKEN_REDIR_OUT)
		ft_outfile_child(args->cmd, args->fd, reading);
	else if (args->cmd->built_in)
		ft_exec_built_in(args, reading);
	else
		ft_pipe_child(args->cmd, args->fd, reading);
}

void	ft_exec_parent(t_token *token, t_args *args, int *reading)
{
	if (token->type == TOKEN_REDIR_IN)
		ft_infile_parent(args->cmd, args->fd, reading);
	else if (token->type == TOKEN_REDIR_OUT)
		ft_outfile_parent(args->cmd, args->fd, reading);
	else
		ft_pipe_parent(args->cmd, args->fd, reading);
}

void	ft_exec_pipe(t_token *token, t_args *args)
{
	int		pid;
	int		reading;
	int		i;
	int		j;

	i = -1;
	j = -1;
	reading = 0;
	while (++i < args->nb_cmd)
	{
		if (args->cmd->next)
			pipe(args->fd);
		pid = fork();
		if (pid == CHILD)
			ft_exec_child(token, args, &reading);
		else
			ft_exec_parent(token, args, &reading);
		if (args->cmd->next)
			args->cmd = args->cmd->next;
		token = token->next;
		while (token && token->type == TOKEN_WORD)
			token = token->next;
	}
	while (++j < args->nb_cmd)
		wait(NULL);
}
