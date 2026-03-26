/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 21:48:05 by dminh             #+#    #+#             */
/*   Updated: 2026/03/26 12:30:16 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*ft_check_env_path(t_env *env, t_cmd *cmd)
{
	if (!env)
	{
		cmd->path = ft_set_default_path(cmd);
		if (!cmd)
			return (NULL);
	}
	else
	{
		if (ft_check_path(cmd, env))
			return (NULL);
	}
	return (cmd->path);
}

char	*ft_set_default_path(t_cmd *cmd)
{
	char	*default_path;
	char	*add_slash;

	add_slash = ft_strdup("./");
	if (!add_slash)
		return (NULL);
	default_path = ft_strjoin(add_slash, cmd->cmd[0]);
	free(add_slash);
	if (!default_path)
		return (NULL);
	return (default_path);
}

int	ft_path_loop(t_cmd *cmd, char **paths, char *add_slash, int i)
{
	while (paths[i])
	{
		add_slash = ft_strjoin(paths[i], "/");
		if (!add_slash)
			return (EXIT_FAILURE);
		cmd->path = ft_strjoin(add_slash, cmd->cmd[0]);
		if (!cmd->path)
		{
			free(add_slash);
			return (EXIT_FAILURE);
		}
		if (access(cmd->path, F_OK | X_OK) == 0)
			return (free(add_slash), 0);
		else
		{
			free(cmd->path);
			free(add_slash);
			i++;
		}
	}
	cmd->path = ft_strdup(cmd->cmd[0]);
	if (!cmd->path)
		return (EXIT_FAILURE);
	return (0);
}
