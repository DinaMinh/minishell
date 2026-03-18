/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 16:07:19 by dminh             #+#    #+#             */
/*   Updated: 2026/03/15 16:07:57 by dminh            ###   ########.fr       */
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
