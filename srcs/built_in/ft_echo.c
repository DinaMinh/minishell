/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:37:54 by ebourdet          #+#    #+#             */
/*   Updated: 2026/03/17 10:37:59 by ebourdet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool is_n_flag(char *arg)
{
	int	i;

	if (arg[0] != '-' || arg[1] != 'n')
		return (false);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	builtin_echo(char **args, int fd_out)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = false;
	while (args[i] && is_n_flag(args[i]))
	{
		n_flag = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], fd_out);
		if (args[i + 1])
			ft_putstr_fd(" ", fd_out);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", fd_out);
	return (0);
}
