/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:05:11 by ebourdet          #+#    #+#             */
/*   Updated: 2026/03/20 15:24:24 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_node(t_env **env_list, char *key, char *value, bool is_local)
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
	new_node->local = is_local;
	new_node->next = NULL;
	env_add_back(env_list, new_node);
}

void	update_env(t_env **env_list, char *key, char *value, bool is_local)
{
	t_env	*node;

	node = find_env_node(*env_list, key);
	if (node != NULL)
	{
		if (!is_local)
			node->local = false;
		if (node->value != NULL)
			free(node->value);
		if (value != NULL)
			node->value = ft_strdup(value);
		else
			node->value = NULL;
	}
	else
		add_env_node(env_list, key, value, is_local);
}

static void	update_pwd_vars(t_env **env, char *old_pwd)
{
	char	*new_pwd;

	if (old_pwd)
	{
		update_env(env, "OLDPWD", old_pwd, false);
		free(old_pwd);
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		update_env(env, "PWD", new_pwd, false);
		free(new_pwd);
	}
}

static int	ft_check_home(t_env *env, char **path)
{
	t_env	*home_node;

	home_node = find_env_node(env, "HOME");
	if (!home_node || !home_node->value)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	*path = home_node->value;
	return (0);
}

int	builtin_cd(char **args, t_env **env)
{
	char	*old_pwd;
	char	*path;

	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	path = NULL;
	if (!args[1])
	{
		if (ft_check_home(*env, &path))
			return (1);
	}
	else
		path = args[1];
	old_pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		free(old_pwd);
		return (1);
	}
	update_pwd_vars(env, old_pwd);
	return (0);
}
