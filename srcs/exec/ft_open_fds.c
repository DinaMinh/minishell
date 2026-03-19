/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 10:05:34 by dminh             #+#    #+#             */
/*   Updated: 2026/03/19 10:05:59 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_open_infile(t_fd *redir)
{
	redir->fd = open(redir->filename, O_RDONLY);
	if (redir->fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->filename);
		return (1);
	}
	dup2(redir->fd, STDIN_FILENO);
	return (0);
}

static int	ft_open_outfile(t_fd *redir, t_token_type file_type)
{
	if (file_type == TOKEN_REDIR_OUT)
		redir->fd = open(redir->filename, O_CREAT | O_WRONLY
				| O_TRUNC, S_IRWXU);
	else
		redir->fd = open(redir->filename, O_CREAT | O_WRONLY
				| O_APPEND, S_IRWXU);
	if (redir->fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->filename);
		return (1);
	}
	dup2(redir->fd, STDOUT_FILENO);
	return (0);
}

int	ft_open_fds(t_cmd *cmd, int fd[2])
{
	t_fd	*tmp;

	tmp = cmd->redir;
	if (cmd->next)
		dup2(fd[PIPE_WRITE], STDOUT_FILENO);
	while (tmp)
	{
		if (tmp->file_type == TOKEN_REDIR_IN || tmp->file_type == TOKEN_HEREDOC)
		{
			if (ft_open_infile(tmp))
				return (1);
		}
		else if (tmp->file_type == TOKEN_REDIR_OUT
			|| tmp->file_type == TOKEN_APPEND)
		{
			if (ft_open_outfile(tmp, tmp->file_type))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
