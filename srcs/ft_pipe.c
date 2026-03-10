/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:37:16 by dminh             #+#    #+#             */
/*   Updated: 2026/03/10 17:32:13 by dminh            ###   ########.fr       */
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

static void	ft_infile_child(t_cmd *cmd, int fd[2], int *reading)
{
	char	*infile_name;
	int		infile;

	infile_name = cmd->cmd[0];
	(void)reading;
	if (cmd->cmd[1])
	{
		infile = open(infile_name, O_RDONLY);
		if (cmd->next)
		{
			dup2(infile, STDIN_FILENO);
			dup2(fd[PIPE_WRITE], STDOUT_FILENO);
			close(fd[PIPE_WRITE]);
			close(fd[PIPE_READ]);
			close(infile);
		}
		else
		{
			dup2(infile, STDIN_FILENO);
			close(infile);
		}
		printf("%s\n", cmd->cmd_path);
		execve(cmd->cmd_path, &cmd->cmd[1], NULL);
	}
}

static void	ft_infile_parent(t_cmd *cmd, int fd[2], int *reading)
{
	if (cmd->next)
	{
		close(fd[PIPE_WRITE]);
		if (*reading != 0)
			close(*reading);
		*reading = fd[PIPE_READ];
	}
}

void	ft_exec_pipe(t_token *token, t_cmd *cmd, int fd[2], int nb_cmd)
{
	int		pid;
	int		reading;
	int		i;
	int		j;

	i = -1;
	j = -1;
	reading = 0;
	(void)token;
	while (++i < nb_cmd)
	{
		if (cmd->next)
			pipe(fd);
		pid = fork();
		if (pid == CHILD)
		{
			if (token->type == TOKEN_REDIR_IN)
				ft_infile_child(cmd, fd, &reading);
			else
				ft_pipe_child(cmd, fd, &reading);
		}
		else
		{
			if (token->type == TOKEN_REDIR_IN)
				ft_infile_parent(cmd, fd, &reading);
			else
				ft_pipe_parent(cmd, fd, &reading);
		}
		if (cmd->next)
			cmd = cmd->next;
		token = token->next;
		while (token && token->type == TOKEN_WORD)
			token = token->next;
	}
	while (++j < nb_cmd)
		wait(NULL);
}
