/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:39:45 by ebourdet          #+#    #+#             */
/*   Updated: 2026/03/17 14:34:17 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric_argument(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_args *main, t_token *token, char **cmd)
{
	int	exit_code;
	int	last_status;

	ft_putendl_fd("exit", STDERR_FILENO);
	last_status = main->return_val;
	if (cmd[1] == NULL)
		ft_exit(main, token, last_status);
	if (!is_numeric_argument(cmd[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		ft_exit(main, token, 255);
	}
	if (cmd[2] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	exit_code = ft_atoi(cmd[1]);
	ft_exit(main, token, exit_code % 256);
	return (0);
}
