/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_local_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:50:25 by ebourdet          #+#    #+#             */
/*   Updated: 2026/03/17 23:19:05 by ebourdet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_assignment(char *str)
{
	char	*eq;
	char	*key;
	int		valid;

	eq = ft_strchr(str, '=');
	if (!eq)
		return (0);
	key = ft_substr(str, 0, eq - str);
	valid = is_valid_env_name(key);
	free(key);
	return (valid);
}

int	ft_handle_local_vars(t_args *args, t_cmd *cmd)
{
	int		i;
	char	*eq;
	char	*key;

	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return (0);
	if (!is_assignment(cmd->cmd[0]))
		return (0);
	i = 0;
	while (cmd->cmd[i] && is_assignment(cmd->cmd[i]))
	{
		eq = ft_strchr(cmd->cmd[i], '=');
		key = ft_substr(cmd->cmd[i], 0, eq - cmd->cmd[i]);
		update_env(&args->env, key, eq + 1, true); 
		free(key);
		i++;
	}
	if (cmd->cmd[i] == NULL)
		return (1);
	return (0);
}
