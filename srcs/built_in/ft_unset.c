/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:35:10 by ebourdet          #+#    #+#             */
/*   Updated: 2026/03/17 10:40:44 by ebourdet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_node(t_env **env_list, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!env_list || !*env_list || !key)
		return ;
	current = *env_list;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				*env_list = current->next;
			else
				prev->next = current->next;
			free(current->key);
			if (current->value != NULL)
				free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	builtin_unset(t_args *cmd_node, t_env **env_list)
{
	int		i;
	int		exit_status;
	char	**args;

	args = cmd_node->cmd;
	exit_status = 0;
	i = 1;
	if (args[1] == NULL)
		return (0);

	while (args[i] != NULL)
	{
		if (!is_valid_env_name(args[i]) || ft_strchr(args[i], '='))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_status = 1;
		}
		else
			remove_env_node(env_list, args[i]);
		i++;
	}
	cmd_node->return_val = exit_status;
	return (exit_status);
}
