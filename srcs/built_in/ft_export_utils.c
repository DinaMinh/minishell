/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:09:55 by ebourdet          #+#    #+#             */
/*   Updated: 2026/03/17 10:37:14 by ebourdet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static void	print_export_node(t_env *node, int fd_out)
{
	ft_putstr_fd("declare -x ", fd_out);
	ft_putstr_fd(node->key, fd_out);
	if (node->value != NULL)
	{
		ft_putstr_fd("=\"", fd_out);
		ft_putstr_fd(node->value, fd_out);
		ft_putstr_fd("\"", fd_out);
	}
	ft_putstr_fd("\n", fd_out);
}

static t_env	**create_env_array(t_env *env_list, int size)
{
	t_env	**arr;
	int		i;

	arr = malloc(sizeof(t_env *) * size);
	if (!arr)
		return (NULL);
	i = 0;
	while (env_list)
	{
		arr[i++] = env_list;
		env_list = env_list->next;
	}
	return (arr);
}

static void	sort_env_array(t_env **arr, int size)
{
	t_env	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(arr[j]->key, arr[j + 1]->key,
					ft_strlen(arr[j]->key) + 1) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	sort_and_print_env(t_env *env_list, int fd_out)
{
	t_env	**arr;
	int		size;
	int		i;

	size = get_env_size(env_list);
	if (size == 0)
		return ;
	arr = create_env_array(env_list, size);
	if (!arr)
		return ;
	sort_env_array(arr, size);
	i = 0;
	while (i < size)
	{
		print_export_node(arr[i], fd_out);
		i++;
	}
	free(arr);
}
