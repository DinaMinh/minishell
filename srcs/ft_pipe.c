/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:37:16 by dminh             #+#    #+#             */
/*   Updated: 2026/03/09 16:37:54 by dminh            ###   ########.fr       */
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
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
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

void	ft_exec_pipe(t_cmd *cmd, int fd[2], int nb_cmd)
{
	int		pid;
	int		reading;
	int		i;
	int		j;

	i = -1;
	j = 0;
	reading = 0;
	while (++i < nb_cmd)
	{
		if (cmd->next)
			pipe(fd);
		pid = fork();
		if (pid == CHILD)
			ft_pipe_child(cmd, fd, &reading);
		else
			ft_pipe_parent(cmd, fd, &reading);
		if (cmd->next)
			cmd = cmd->next;
	}
	while (j < nb_cmd)
	{
		wait(NULL);
		j++;
	}
}
