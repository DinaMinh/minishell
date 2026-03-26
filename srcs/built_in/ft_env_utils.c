/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:38:21 by ebourdet          #+#    #+#             */
/*   Updated: 2026/03/26 10:56:52 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(char *env_str, bool is_local)
{
	t_env	*node;
	char	*equal_sign;
	int		key_len;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	equal_sign = ft_strchr(env_str, '=');
	if (equal_sign != NULL)
	{
		key_len = equal_sign - env_str;
		node->key = ft_substr(env_str, 0, key_len);
		node->value = ft_strdup(equal_sign + 1);
	}
	else
		node->key = ft_strdup(env_str);
	node->local = is_local;
	if (!node->key || (equal_sign != NULL && !node->value))
	{
		free_env_node(node);
		return (NULL);
	}
	return (node);
}

void	free_env_node(t_env *node)
{
	free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

void	env_add_back(t_env **env_list, t_env *new_node)
{
	t_env	*current;

	if (!env_list || !new_node)
		return ;
	if (*env_list == NULL)
	{
		*env_list = new_node;
		return ;
	}
	current = *env_list;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}

static char	**increment_shlvl(t_env **env_list, char **envp)
{
	t_env	*shlvl;
	char	**new_envp;
	char	*new_value_str;
	int		new_value;

	shlvl = find_env_node(*env_list, "SHLVL");
	if (shlvl && shlvl->value)
	{
		new_value = ft_atoi(shlvl->value) + 1;
		if (new_value < 0)
			new_value = 0;
		new_value_str = ft_itoa(new_value);
		update_env(env_list, "SHLVL", new_value_str, false);
		new_envp = ft_shlvl_update(env_list, envp, new_value_str);
		if (!new_value_str || !new_envp)
			return (free(new_value_str), envp);
		free(new_value_str);
	}
	else
	{
		update_env(env_list, "SHLVL", "1", false);
		new_envp = envp;
	}
	return (new_envp);
}

t_env	*init_env(char **envp, t_args *args)
{
	t_env	*env_list;
	t_env	*new_node;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		new_node = create_env_node(envp[i], false);
		if (new_node != NULL)
			env_add_back(&env_list, new_node);
		i++;
	}
	args->envp = increment_shlvl(&env_list, envp);
	return (env_list);
}
