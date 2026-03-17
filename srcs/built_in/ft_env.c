/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:39:28 by ebourdet          #+#    #+#             */
/*   Updated: 2026/03/17 10:39:34 by ebourdet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_env(t_env *env_list, int fd_out)
{
	t_env	*current;

	current = env_list;
	while (current != NULL)
	{
		if (current->value != NULL)
		{
			ft_putstr_fd(current->key, fd_out);
			ft_putchar_fd('=', fd_out);
			ft_putstr_fd(current->value, fd_out);
			ft_putchar_fd('\n', fd_out);
		}
		current = current->next;
	}
	return (0);
}
