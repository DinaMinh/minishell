/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:37:16 by dminh             #+#    #+#             */
/*   Updated: 2026/03/14 17:40:53 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fds(t_cmd *cmd, int fd[2], int *reading)
{
	if (*reading != 0)
		close(*reading);
	if (cmd->next)
	{
		close(fd[PIPE_READ]);
		close(fd[PIPE_WRITE]);
	}
	if (cmd->in_fd != 0)
		close(cmd->in_fd);
	if (cmd->out_fd != 0)
		close(cmd->out_fd);
}

static void	ft_pipe_child(t_cmd *cmd, int fd[2], int *reading)
{
	if (*reading != 0)
		dup2(*reading, STDIN_FILENO);
	if (cmd->infile)
	{
		cmd->in_fd = open(cmd->infile, O_RDONLY);
		dup2(cmd->in_fd, STDIN_FILENO);
	}
	if (cmd->next)
		dup2(fd[PIPE_WRITE], STDOUT_FILENO);
	if (cmd->outfile)
	{
		cmd->out_fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		dup2(cmd->out_fd, STDOUT_FILENO);
	}
	ft_close_fds(cmd, fd, reading);
	if (cmd->cmd[0])
		execve(cmd->path, cmd->cmd, NULL);
	exit(EXIT_SUCCESS);
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

void	ft_exec_child(t_args *args, int *reading)
{
	if (args->cmd->built_in)
		ft_exec_built_in(args, reading);
	else
		ft_pipe_child(args->cmd, args->fd, reading);
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
	(void)token;
	if (args->nb_cmd == 1)
	{
		if (args->cmd->built_in)
		{
			ft_built_in_only(args);
			return ;
		}
	}
	while (++i < args->nb_cmd)
	{
		if (args->cmd->next)
			pipe(args->fd);
		pid = fork();
		if (pid == CHILD)
			ft_exec_child(args, &reading);
		else
			ft_pipe_parent(args->cmd, args->fd, &reading);
		if (args->cmd->next)
			args->cmd = args->cmd->next;
	}
	while (++j < args->nb_cmd)
		wait(NULL);
}
