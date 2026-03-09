/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:09:13 by dminh             #+#    #+#             */
/*   Updated: 2026/03/09 14:32:10 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_clear(t_cmd **head)
{
	t_cmd	*tmp;
	int		i;

	while (*head)
	{
		tmp = (*head)->next;
		i = 0;
		while ((*head)->cmd[i])
		{
			free((*head)->cmd[i]);
			i++;
		}
		free((*head)->cmd);
		free((*head)->cmd_path);
		(*head)->cmd_path = NULL;
		free(*head);
		*head = tmp;
	}
	*head = NULL;
}

void	ft_free_all(t_args *args)
{
	ft_cmd_clear(&args->cmd);
	free(args->input);
	args->input = NULL;
	args->nb_cmd = 0;
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
