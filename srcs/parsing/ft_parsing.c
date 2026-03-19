/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:45:38 by dminh             #+#    #+#             */
/*   Updated: 2026/03/19 10:35:53 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_built_in(t_args *args)
{
	t_cmd	*tmp;

	tmp = args->cmd;
	while (tmp && tmp->cmd)
	{
		if (tmp->cmd[0] && ft_strnstr(BUILT_IN_CMD, tmp->cmd[0], BUILT_IN_LEN))
			tmp->built_in = true;
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_is_binary(t_cmd *cmd)
{
	char	*tmp;
	int		i;

	i = ft_strlen(cmd->cmd[0]) - 1;
	while (cmd->cmd[0][i] && cmd->cmd[0][i] != '/')
		i--;
	cmd->path = ft_strdup(cmd->cmd[0]);
	if (!cmd->path)
		return (EXIT_FAILURE);
	tmp = ft_strdup(&cmd->cmd[0][i + 1]);
	if (!tmp)
		return (EXIT_FAILURE);
	free(cmd->cmd[0]);
	cmd->cmd[0] = tmp;
	return (EXIT_SUCCESS);
}

int	ft_check_path(t_cmd *cmd)
{
	int	cmd_len;
	int	cmd_index;

	cmd_index = 0;
	cmd_len = ft_strlen(cmd->cmd[cmd_index]) + PATH_LEN;
	cmd->path = ft_calloc(cmd_len + 1, sizeof(*cmd->path));
	if (!cmd->path)
		return (EXIT_FAILURE);
	ft_strlcpy(cmd->path, PATH, PATH_LEN);
	cmd->path = ft_strncat(cmd->path, cmd->cmd[cmd_index],
			cmd_len);
	return (EXIT_SUCCESS);
}

int	ft_has_blank(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_get_path(t_cmd *cmd, t_token *token)
{
	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return (EXIT_SUCCESS);
	if (ft_strchr(cmd->cmd[0], '/') && !ft_has_blank(cmd->cmd[0]))
		return (ft_is_binary(cmd));
	if (!cmd->built_in)
	{
		if (ft_check_path(cmd))
			return (EXIT_FAILURE);
	}
	if (cmd->next)
	{
		token = token->next;
		while (token && token->type == TOKEN_WORD)
			token = token->next;
		while (token && token->type == TOKEN_PIPE)
			token = token->next;
		if (ft_get_path(cmd->next, token))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
