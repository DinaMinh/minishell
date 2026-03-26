/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:47:18 by dminh             #+#    #+#             */
/*   Updated: 2026/03/26 10:47:18 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_free_envp(char **envp, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	return (NULL);
}

static int	ft_env_size(t_env *env_list)
{
	int	size;

	size = 0;
	while (env_list->next)
	{
		size++;
		env_list = env_list->next;
	}
	return (size);
}

static char	*ft_shlvl_envp(char *new_envp, char *new_shlvl)
{
	new_envp = ft_strjoin("SHLVL=", new_shlvl);
	if (!new_envp)
		return (NULL);
	return (new_envp);
}

char	**ft_shlvl_update(t_env **env_list, char **envp, char *new_shlvl)
{
	t_env	*tmp;
	char	**new_envp;
	int		i;
	int		size;

	i = 0;
	tmp = *env_list;
	size = ft_env_size(*env_list);
	new_envp = ft_calloc(size + 1, sizeof(*new_envp));
	if (!new_envp)
		return (NULL);
	while (i < size)
	{
		if (ft_strncmp(tmp->key, "SHLVL", 5) == 0)
			new_envp[i] = ft_shlvl_envp(new_envp[i], new_shlvl);
		else
			new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
			return (ft_free_envp(new_envp, i));
		tmp = tmp->next;
		i++;
	}
	return (new_envp);
}
