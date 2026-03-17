/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:05:11 by ebourdet          #+#    #+#             */
/*   Updated: 2026/03/17 10:36:24 by ebourdet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_node(t_env **env_list, char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	env_add_back(env_list, new_node);
}

void	update_env(t_env **env_list, char *key, char *value)
{
	t_env	*node;

	node = find_env_node(*env_list, key);
	if (node != NULL)
	{
		if (node->value != NULL)
			free(node->value);
		if (value != NULL)
			node->value = ft_strdup(value);
		else
			node->value = NULL;
	}
	else
		add_env_node(env_list, key, value);
}

static void	update_pwd_vars(t_env **env, char *old_pwd)
{
	char	*new_pwd;

	if (old_pwd)
	{
		update_env(env, "OLDPWD", old_pwd);
		free(old_pwd);
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		update_env(env, "PWD", new_pwd);
		free(new_pwd);
	}
}

int	builtin_cd(char **args, t_env **env)
{
	char	*old_pwd;

	if (!args[1])
		return (0);
	if (args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(args[1]) == -1)
	{
		perror("minishell: cd");
		free(old_pwd);
		return (1);
	}
	update_pwd_vars(env, old_pwd);
	return (0);
}
