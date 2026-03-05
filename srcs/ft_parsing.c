/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:45:38 by dminh             #+#    #+#             */
/*   Updated: 2026/03/05 17:22:23 by dminh            ###   ########.fr       */
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

int	ft_get_cmd(t_args *args, t_token *token)
{
	int	cmd_len;
	int	cmd_index;

	cmd_index = 0;
	if (token && token->type != TOKEN_WORD && args->cmd[1])
		cmd_index = 1;
	cmd_len = ft_strlen(args->cmd[cmd_index]) + PATH_LEN;
	args->cmd_path = ft_calloc(cmd_len + 1, sizeof(*args->cmd_path));
	if (!args->cmd_path)
		return (1);
	ft_strlcpy(args->cmd_path, PATH, PATH_LEN);
	args->cmd_path = ft_strncat(args->cmd_path, args->cmd[cmd_index], cmd_len);
	if (access(args->cmd_path, F_OK) == -1 && args->redirect == 0)
		return (1);
	return (0);
}
