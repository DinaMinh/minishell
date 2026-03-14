/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 17:28:54 by dminh             #+#    #+#             */
/*   Updated: 2026/03/14 11:49:55 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_infile_child(t_cmd *cmd, int fd[2], int *reading)
{
	int		infile;

	if (cmd->cmd[1])
	{
		if (*reading != 0)
		{
			dup2(*reading, STDIN_FILENO);
			close(*reading);
		}
		printf ("%s\n", cmd->path);
		infile = open(cmd->infile, O_RDONLY);
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
		execve(cmd->path, cmd->cmd, NULL);
	}
}

void	ft_infile_parent(t_cmd *cmd, int fd[2], int *reading)
{
	if (*reading != 0)
		close(*reading);
	if (cmd->next)
	{
		close(fd[PIPE_WRITE]);
		*reading = fd[PIPE_READ];
	}
}
