/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:54:00 by ebourdet          #+#    #+#             */
/*   Updated: 2026/03/26 15:04:12 by ebourdet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_home(t_env *env, char *path)
{
	t_env	*home_node;

	home_node = find_env_node(env, "HOME");
	if (!home_node || !home_node->value)
		return (1);
	if (ft_strcmp(path, home_node->value) != 0)
		return (1);
	return (0);
}

int	ft_check_path_oldpwd(t_env **env, char *old_pwd, char *path)
{
	if (old_pwd == NULL && ft_is_home(*env, path))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(path);
		free(old_pwd);
		return (1);
	}
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		free(old_pwd);
		return (1);
	}
	return (0);
}
