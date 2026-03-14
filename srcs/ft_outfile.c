/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 17:30:57 by dminh             #+#    #+#             */
/*   Updated: 2026/03/14 16:06:45 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_outfile_child(t_cmd *cmd, int fd[2], int *reading)
{
	int		outfile;

	if (*reading != 0)
	{
		close(fd[PIPE_WRITE]);
		dup2(*reading, STDIN_FILENO);	
	}
	outfile = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	dup2(outfile, STDOUT_FILENO);
	if (*reading != 0)
		close(fd[PIPE_READ]);
	close(fd[outfile]);
}

void	ft_outfile_parent(t_cmd *cmd, int fd[2], int *reading)
{
	if (*reading != 0)
		close(*reading);
	if (cmd->next)
	{
		close(fd[PIPE_WRITE]);
		*reading = fd[PIPE_READ];
	}
}
