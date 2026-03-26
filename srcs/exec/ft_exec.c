/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:30:16 by dminh             #+#    #+#             */
/*   Updated: 2026/03/26 11:59:32 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_child(t_cmd *cmd, t_args *args, t_token *token, int *reading)
{
	setup_child_signals();
	if (*reading != 0)
		dup2(*reading, STDIN_FILENO);
	if (ft_open_fds(cmd, args->fd))
	{
		ft_close_fds(cmd, args->fd, reading);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		ft_exit(args, token, EXIT_FAILURE);
	}
	ft_close_fds(cmd, args->fd, reading);
	if (!cmd || !cmd->cmd || !cmd->cmd[0])
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		ft_exit(args, token, 0);
	}
	execve(cmd->path, cmd->cmd, args->envp);
	ft_handle_errors(args, token, cmd);
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
			return (i);
		pid = fork();
		if (ft_check_fork(args, cmd, pid))
			return (i);
		args->last_pid = pid;
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
	int		pid;
	int		status;
	int		reading;
	bool	print;

	i = -1;
	reading = 0;
	print = false;
	if (ft_check_nb_cmd(args, token, &reading))
		return ;
	args->nb_forks = ft_exec_loop(args, token, &reading);
	while (++i < args->nb_forks)
	{
		pid = wait(&status);
		if (WIFEXITED(status))
		{
			if (pid == args->last_pid)
				args->return_val = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
			ft_print_interrupt(args, status, &print);
	}
}
