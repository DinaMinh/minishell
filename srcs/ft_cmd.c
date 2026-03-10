/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:24:34 by dminh             #+#    #+#             */
/*   Updated: 2026/03/10 12:37:43 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_init_cmd(int size)
{
	t_cmd	*node;

	node = ft_calloc(1, sizeof(*node));
	if (!node)
		return (NULL);
	node->cmd = ft_calloc(size + 1, sizeof(*node->cmd));
	if (!node->cmd)
		return (NULL);
	node->cmd_path = NULL;
	node->next = NULL;
	return (node);
}

t_cmd	*ft_get_cmd_size(t_token *token)
{
	t_cmd	*cmd;
	int		size;

	size = 0;
	while (token && token->type == TOKEN_WORD)
	{
		size++;
		token = token->next;
	}
	cmd = ft_init_cmd(size);
	return (cmd);
}

t_cmd	*ft_cmd(t_token *token, t_cmd *cmd, int *nb_cmd)
{
	int		i;

	if (!token)
		return (NULL);
	while (token && token->type != TOKEN_WORD)
		token = token->next;
	cmd = ft_get_cmd_size(token);
	if (!cmd->cmd)
		return (NULL);
	i = 0;
	while (token && token->type == TOKEN_WORD)
	{
		cmd->cmd[i] = ft_strdup(token->content);
		if (!cmd->cmd[i])
			return (NULL);
		token = token->next;
		i++;
	}
	(*nb_cmd)++;
	if (token && token->type != TOKEN_WORD)
		cmd->next = ft_cmd(token->next, cmd->next, nb_cmd);
	return (cmd);
}
