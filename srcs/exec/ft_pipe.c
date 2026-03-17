/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:37:16 by dminh             #+#    #+#             */
/*   Updated: 2026/03/17 23:13:39 by ebourdet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_child(t_cmd *cmd, int fd[2], int *reading, char **envp)
{
	setup_child_signals();
	if (*reading != 0)
		dup2(*reading, STDIN_FILENO);
	if (cmd->infile)
	{
		cmd->in_fd = open(cmd->infile, O_RDONLY);
		if (cmd->in_fd < 0)
			exit(1);
		dup2(cmd->in_fd, STDIN_FILENO);
	}
	if (cmd->next)
		dup2(fd[PIPE_WRITE], STDOUT_FILENO);
	if (cmd->outfile)
	{
		cmd->out_fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		if (cmd->out_fd < 0)
			exit(1);
		dup2(cmd->out_fd, STDOUT_FILENO);
	}
	ft_close_fds(cmd, fd, reading);
	execve(cmd->path, cmd->cmd, envp);
	ft_print_error_cmd(cmd->cmd[0]);
	exit(127);
}

static void	ft_parent(t_cmd *cmd, int fd[2], int *reading)
{
	if (*reading != 0)
		close(*reading);
	if (cmd->next)
	{
		close(fd[PIPE_WRITE]);
		*reading = fd[PIPE_READ];
	}
}

void	ft_exec_child(t_args *args, t_cmd *cmd, t_token *token, int *reading)
{
	if (cmd->built_in)
		ft_built_in(args, cmd, token, reading);
	else
		ft_child(cmd, args->fd, reading, args->envp);
}

void	ft_exec_loop(t_args *args, t_token *token, int *reading)
{
	t_cmd	*cmd;
	int		pid;
	int		i;

	setup_parent_signals();
	i = 0;
	cmd = args->cmd;
	while (i < args->nb_cmd)
	{
		if (args->cmd->next)
			pipe(args->fd);
		pid = fork();
		if (pid == CHILD)
			ft_exec_child(args, cmd, token, reading);
		else
			ft_parent(cmd, args->fd, reading);
		if (cmd->next)
			cmd = cmd->next;
		i++;
	}
}

void	ft_exec(t_args *args, t_token *token)
{
	int		i;
	int		status;
	int		reading;

	i = 0;
	reading = 0;
	if (args->nb_cmd == 1)
	{
		if (args->cmd->built_in)
		{
			ft_built_in_only(args, token);
			return ;
		}
	}
	ft_exec_loop(args, token, &reading);
	while (i < args->nb_cmd)
	{
		wait(&status);
		args->return_val = WEXITSTATUS(status);
		i++;
	}
}
