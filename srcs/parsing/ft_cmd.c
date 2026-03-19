/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:24:34 by dminh             #+#    #+#             */
/*   Updated: 2026/03/18 23:47:29 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_init_cmd(t_fd *redir, int size)
{
	t_cmd	*node;

	node = ft_calloc(1, sizeof(*node));
	if (!node)
		return (NULL);
	node->cmd = ft_calloc(size + 1, sizeof(*node->cmd));
	if (!node->cmd)
		return (NULL);
	node->redir = redir;
	return (node);
}

int	ft_check_redir(t_token **token, t_fd **redir, t_args *args)
{
	char			*filename;
	t_token_type	file_type;

	file_type = TOKEN_WORD;
	filename = NULL;
	if ((*token)->type == TOKEN_REDIR_IN
		|| (*token)->type == TOKEN_REDIR_OUT || (*token)->type == TOKEN_APPEND
		|| (*token)->type == TOKEN_HEREDOC)
	{
		file_type = (*token)->type;
		*token = (*token)->next;
	}
	if (*token && file_type == TOKEN_HEREDOC)
	{
		if (ft_init_heredoc(token, redir, args, file_type))
			return (1);
	}
	if (*token && (*token)->type == TOKEN_FILENAME)
		filename = (*token)->content;
	if (file_type != TOKEN_HEREDOC)
	{
		if (!ft_fd_addback(redir, filename, file_type))
			return (1);
	}
	return (0);
}

t_cmd	*ft_get_cmd_size(t_token *token, t_args *args)
{
	t_cmd			*cmd;
	t_fd			*redir;
	int				size;

	redir = NULL;
	size = 0;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD)
			size++;
		else
		{
			if (ft_check_redir(&token, &redir, args))
				return (NULL);
		}
		token = token->next;
	}
	cmd = ft_init_cmd(redir, size);
	return (cmd);
}

t_cmd	*ft_cmd(t_token *token, t_args *args, t_cmd *cmd, int *nb_cmd)
{
	int		i;

	if (!token)
		return (NULL);
	cmd = ft_get_cmd_size(token, args);
	if (!cmd || !cmd->cmd)
		return (NULL);
	i = 0;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD)
		{
			cmd->cmd[i] = ft_strdup(token->content);
			if (!cmd->cmd[i])
				return (NULL);
			i++;
		}
		token = token->next;
	}
	(*nb_cmd)++;
	if (token && token->type == TOKEN_PIPE)
		cmd->next = ft_cmd(token->next, args, cmd->next, nb_cmd);
	return (cmd);
}
