/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 22:20:36 by ebourdet          #+#    #+#             */
/*   Updated: 2026/03/17 10:40:33 by ebourdet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env_node(t_env *env_list, char *key)
{
	size_t	len_key;
	size_t	len_node;

	if (!key)
		return (NULL);
	len_key = ft_strlen(key);
	while (env_list != NULL)
	{
		len_node = ft_strlen(env_list->key);
		if (len_key == len_node && ft_strncmp(env_list->key, key, len_key) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

int	is_valid_env_name(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static void	process_export_arg(t_env **env, char *arg)
{
	char	*key;
	char	*equal_pos;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
	{
		key = ft_substr(arg, 0, equal_pos - arg);
		update_env(env, key, equal_pos + 1);
		free(key);
	}
	else
	{
		if (!find_env_node(*env, arg))
			update_env(env, arg, NULL);
	}
}

int	builtin_export(t_args *cmd_node, t_env **env_list)
{
	int		i;
	int		exit_status;
	char	**args;

	args = cmd_node->cmd;
	exit_status = 0;
	if (args[1] == NULL)
	{
		sort_and_print_env(*env_list, 1);
		return (0);
	}
	i = 1;
	while (args[i] != NULL)
	{
		if (!is_valid_env_name(args[i]))
			exit_status = export_error(args[i]);
		else
			process_export_arg(env_list, args[i]);
		i++;
	}
	cmd_node->return_val = exit_status;
	return (exit_status);
}
