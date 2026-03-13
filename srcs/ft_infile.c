/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 17:28:54 by dminh             #+#    #+#             */
/*   Updated: 2026/03/13 17:29:48 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_infile_child(t_cmd *cmd, int fd[2], int *reading)
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
		execve(cmd->cmd_path, &cmd->cmd[1], NULL);
	}
}

void	ft_infile_parent(t_cmd *cmd, int fd[2], int *reading)
{
	close(fd[PIPE_WRITE]);
	if (*reading != 0)
		close(*reading);
	if (cmd->next)
		*reading = fd[PIPE_READ];
}
