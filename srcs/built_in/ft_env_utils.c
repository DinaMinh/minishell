/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:38:21 by ebourdet          #+#    #+#             */
/*   Updated: 2026/03/17 10:38:27 by ebourdet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(char *env_str)
{
	t_env	*node;
	char	*equal_sign;
	int		key_len;

	node = malloc(sizeof(t_env));
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
	{
		node->key = ft_strdup(env_str);
		node->value = NULL;
	}
	node->next = NULL;
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
	{
		current = current->next;
	}
	current->next = new_node;
}

t_env	*init_env(char **envp)
{
	t_env	*env_list;
	t_env	*new_node;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		new_node = create_env_node(envp[i]);
		if (new_node != NULL)
			env_add_back(&env_list, new_node);
		i++;
	}
	return (env_list);
}
