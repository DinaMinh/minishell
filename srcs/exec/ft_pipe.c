/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:37:16 by dminh             #+#    #+#             */
/*   Updated: 2026/03/18 10:47:12 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_open_infile(t_fd *redir)
{
	redir->fd = open(redir->filename, O_RDONLY);
	if (redir->fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->filename);
		exit(1);
	}
	dup2(redir->fd, STDIN_FILENO);
}

static void	ft_open_outfile(t_fd *redir, t_token_type file_type)
{
	if (file_type == TOKEN_REDIR_OUT)
		redir->fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		redir->fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (redir->fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->filename);
		exit(1);
	}
	dup2(redir->fd, STDOUT_FILENO);
}

void	ft_open_fds(t_cmd *cmd, int fd[2])
{
	t_fd	*tmp;

	tmp = cmd->redir;
	if (cmd->next)
		dup2(fd[PIPE_WRITE], STDOUT_FILENO);
	while (tmp)
	{
		if (tmp->file_type == TOKEN_REDIR_IN || tmp->file_type == TOKEN_HEREDOC)
			ft_open_infile(tmp);
		else if (tmp->file_type == TOKEN_REDIR_OUT
			|| tmp->file_type == TOKEN_APPEND)
			ft_open_outfile(tmp, tmp->file_type);
		tmp = tmp->next;
	}
}

static void	ft_child(t_cmd *cmd, int fd[2], int *reading, char **envp)
{
	if (*reading != 0)
		dup2(*reading, STDIN_FILENO);
	ft_open_fds(cmd, fd);
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

	i = 0;
	cmd = args->cmd;
	while (i < args->nb_cmd)
	{
		if (cmd->next)
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
			ft_built_in_only(args, token, &reading);
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
