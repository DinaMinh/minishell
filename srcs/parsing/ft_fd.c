/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 22:05:30 by dminh             #+#    #+#             */
/*   Updated: 2026/03/18 01:00:49 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd	*ft_fd_new(char *filename, t_token_type file_type)
{
	t_fd	*node;

	node = ft_calloc(1, sizeof(*node));
	if (!node)
		return (NULL);
	if (file_type == TOKEN_HEREDOC)
		node->filename = ft_strdup(filename);
	else
		node->filename = filename;
	if (!node->filename)
	{
		free(node);
		return (NULL);
	}
	node->fd = -1;
	node->file_type = file_type;
	return (node);
}

t_fd	*ft_fd_addback(t_fd **redir, char *filename, t_token_type file_type)
{
	t_fd	*tmp;
	t_fd	*new;

	new = ft_fd_new(filename, file_type);
	if (!new)
		return (NULL);
	if (!*redir)
	{
		*redir = new;
		return (*redir);
	}
	tmp = *redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (*redir);
}
