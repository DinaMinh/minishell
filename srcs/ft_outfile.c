/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 17:30:57 by dminh             #+#    #+#             */
/*   Updated: 2026/03/13 17:31:47 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_outfile_child(t_cmd *cmd, int fd[2], int *reading)
{
	char	buf[100];
	int		bytes;
	int		outfile;
	int		i;

	close(fd[PIPE_WRITE]);
	outfile = open(cmd->cmd[0], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	dup2(*reading, STDIN_FILENO);	
	dup2(outfile, STDOUT_FILENO);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(*reading, buf, sizeof(buf));
		if (bytes == -1)
			return ;
		write(outfile, buf, bytes);
	}
	i = 0;
	if (cmd->cmd[1])
	{
		while (cmd->cmd[++i])
			write(outfile, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
	}
	close(fd[PIPE_READ]);
	close(fd[outfile]);
}

void	ft_outfile_parent(t_cmd *cmd, int fd[2], int *reading)
{
	close(fd[PIPE_WRITE]);
	if (cmd->next)
	{
		if (*reading != 0)
			close(*reading);
	}
}
