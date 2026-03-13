/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:45:38 by dminh             #+#    #+#             */
/*   Updated: 2026/03/13 16:34:20 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_built_in(t_args *args, t_token *token)
{
	t_cmd	*tmp;
	int	index;

	index = 0;
	if (token && token->type != TOKEN_WORD && token->type != TOKEN_PIPE)
		index = 1;
	tmp = args->cmd;
	printf("%s\n", args->cmd->cmd[index]);
	while (tmp && tmp->cmd)
	{
		if (ft_strnstr(BUILT_IN_CMD, tmp->cmd[index], BUILT_IN_LEN))
			tmp->built_in = true;
		tmp = tmp->next;
	}
	return (0);
}

int	ft_check_path(t_cmd *cmd, t_token *token)
{
	int	cmd_len;
	int	cmd_index;

	cmd_index = 0;
	if (token && token->type != TOKEN_WORD && token->type != TOKEN_PIPE && cmd->cmd[1])
		cmd_index = 1;
	cmd_len = ft_strlen(cmd->cmd[cmd_index]) + PATH_LEN;
	cmd->cmd_path = ft_calloc(cmd_len + 1, sizeof(*cmd->cmd_path));
	if (!cmd->cmd_path)
		return (1);
	ft_strlcpy(cmd->cmd_path, PATH, PATH_LEN);
	cmd->cmd_path = ft_strncat(cmd->cmd_path, cmd->cmd[cmd_index],
			cmd_len);
	if (access(cmd->cmd_path, F_OK) == -1)
		return (1);
	return (0);
}

int	ft_get_path(t_cmd *cmd, t_token *token)
{
	if (!cmd->built_in)
	{
		if (ft_check_path(cmd, token))
			return (1);
	}
	if (cmd->next)
	{
		token = token->next;
		while (token && token->type == TOKEN_WORD)
			token = token->next;
		if (ft_get_path(cmd->next, token))
			return (1);
	}
	return (0);
}
