/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 22:59:06 by ebourdet          #+#    #+#             */
/*   Updated: 2026/03/17 23:36:33 by ebourdet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_global_env(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		if (env->local == false && env->value != NULL)
			size++;
		env = env->next;
	}
	return (size);
}

static void	fill_env_array(t_env *env, char **envp)
{
	char	*temp_str;
	int		i;

	i = 0;
	while (env)
	{
		if (env->local == false && env->value != NULL)
		{
			temp_str = ft_strjoin(env->key, "=");
			envp[i] = ft_strjoin(temp_str, env->value);
			free(temp_str);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
}

char	**env_list_to_array(t_env *env_list)
{
	char	**envp;
	int		size;

	size = count_global_env(env_list);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	fill_env_array(env_list, envp);
	return (envp);
}

void	free_env_array(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
