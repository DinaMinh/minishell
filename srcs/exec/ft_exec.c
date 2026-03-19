/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:30:16 by dminh             #+#    #+#             */
/*   Updated: 2026/03/19 10:24:50 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_child(t_cmd *cmd, t_args *args, t_token *token, int *reading)
{
	setup_child_signals();
	if (*reading != 0)
		dup2(*reading, STDIN_FILENO);
	if (ft_open_fds(cmd, args->fd))
		ft_exit(args, token, EXIT_FAILURE);
	ft_close_fds(cmd, args->fd, reading);
	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		ft_exit(args, token, 0);
	execve(cmd->path, cmd->cmd, args->envp);
	ft_print_error_cmd(cmd->cmd[0]);
	ft_exit(args, token, 127);
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
		ft_child(cmd, args, token, reading);
}

static int	ft_exec_loop(t_args *args, t_token *token, int *reading)
{
	t_cmd	*cmd;
	int		pid;
	int		i;

	setup_parent_signals();
	i = 0;
	cmd = args->cmd;
	while (i < args->nb_cmd)
	{
		if (ft_pipe(cmd, args))
			return i;
		pid = fork();
		if (ft_check_fork(args, cmd, pid))
			return i;
		if (pid == CHILD)
			ft_exec_child(args, cmd, token, reading);
		else
			ft_parent(cmd, args->fd, reading);
		if (cmd->next)
			cmd = cmd->next;
		i++;
	}
	return (i);
}

void	ft_exec(t_args *args, t_token *token)
{
	int		i;
	int		status;
	int		reading;
	bool	print;

	i = -1;
	reading = 0;
	print = false;
	if (args->nb_cmd == 1)
	{
		if (args->cmd->built_in)
		{
			ft_built_in_only(args, token, &reading);
			return ;
		}
	}
	args->nb_forks = ft_exec_loop(args, token, &reading);
	while (++i < args->nb_forks)
	{
		wait(&status);
		if (WIFEXITED(status))
			args->return_val = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ft_print_interrupt(args, status, &print);
	}
}
