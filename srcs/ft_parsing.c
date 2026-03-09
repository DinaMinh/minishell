/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:45:38 by dminh             #+#    #+#             */
/*   Updated: 2026/03/09 11:43:12 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_redir(t_args *args, t_token *token)
{
	if (token && token->type == TOKEN_REDIR_IN)
	{
		token = token->next;
	}
	return (args->input);
}

int	ft_get_cmd(t_cmd *cmd, t_token *token)
{
	int	cmd_len;
	int	cmd_index;

	cmd_index = 0;
	if (token && token->type != TOKEN_WORD && cmd->cmd[1])
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
	if (cmd->next)
	{
		if (ft_get_cmd(cmd->next, token))
			return (0);
	}
	return (0);
}
