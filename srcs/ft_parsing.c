/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:45:38 by dminh             #+#    #+#             */
/*   Updated: 2026/03/14 15:35:07 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_built_in(t_args *args)
{
	t_cmd	*tmp;

	tmp = args->cmd;
	while (tmp && tmp->cmd )
	{
		if (tmp->cmd[0] && ft_strnstr(BUILT_IN_CMD, tmp->cmd[0], BUILT_IN_LEN))
			tmp->built_in = true;
		tmp = tmp->next;
	}
	return (0);
}

int	ft_check_path(t_cmd *cmd)
{
	int	cmd_len;
	int	cmd_index;

	if (!cmd->cmd[0])
		return (0);
	cmd_index = 0;
	cmd_len = ft_strlen(cmd->cmd[cmd_index]) + PATH_LEN;
	cmd->path = ft_calloc(cmd_len + 1, sizeof(*cmd->path));
	if (!cmd->path)
		return (1);
	ft_strlcpy(cmd->path, PATH, PATH_LEN);
	cmd->path = ft_strncat(cmd->path, cmd->cmd[cmd_index],
			cmd_len);
	if (access(cmd->path, F_OK) == -1)
		return (1);
	return (0);
}

int	ft_get_path(t_cmd *cmd, t_token *token)
{
	if (!cmd->built_in)
	{
		if (ft_check_path(cmd))
			return (1);
	}
	if (cmd->next)
	{
		token = token->next;
		while (token && token->type == TOKEN_WORD)
			token = token->next;
		while (token && token->type == TOKEN_PIPE)
			token = token->next;
		if (ft_get_path(cmd->next, token))
			return (1);
	}
	return (0);
}
