/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 16:07:19 by dminh             #+#    #+#             */
/*   Updated: 2026/03/19 11:45:57 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_redir(t_fd *redir)
{
	while (redir)
	{
		close(redir->fd);
		redir = redir->next;
	}
}

void	ft_close_fds(t_cmd *cmd, int fd[2], int *reading)
{
	if (*reading != 0)
		close(*reading);
	if (cmd->next)
	{
		close(fd[PIPE_READ]);
		close(fd[PIPE_WRITE]);
	}
	if (cmd->redir)
		ft_close_redir(cmd->redir);
}

void	ft_print_interrupt(t_args *args, int status, bool *print)
{
	if (!*print)
	{
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", STDOUT_FILENO);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
		*print = true;
	}
	args->return_val = WTERMSIG(status) + 128;
}

int	ft_pipe(t_cmd *cmd, t_args *args)
{
	if (cmd->next)
	{
		if (pipe(args->fd) == -1)
		{
			perror("minishell: pipe");
			args->return_val = 1;
			return (1);
		}
	}
	return (0);
}

int	ft_check_fork(t_args *args, t_cmd *cmd, int pid)
{
	if (pid == -1)
	{
		args->return_val = 1;
		if (cmd->next)
		{
			close(args->fd[PIPE_READ]);
			close(args->fd[PIPE_WRITE]);
		}
		return (1);
	}
	return (0);
}
