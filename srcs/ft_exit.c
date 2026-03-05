/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:09:13 by dminh             #+#    #+#             */
/*   Updated: 2026/03/05 18:09:13 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_all(t_args *args)
{
	int	i;

	i = 0;
	while (args->cmd[i])
	{
		free(args->cmd[i]);
		i++;
	}
	free(args->cmd);
	args->cmd = NULL;
	free(args->cmd_path);
	args->cmd_path = NULL;
	free(args->input);
	args->input = NULL;
}

int	ft_exit(t_args *args, t_token *token)
{
	if (ft_strncmp(args->input, EXIT, EXIT_LEN) == 0)
	{
		ft_free_all(args);
		ft_token_clear(&token);
		rl_clear_history();
		exit(EXIT_SUCCESS);
	}
	return (0);
}
