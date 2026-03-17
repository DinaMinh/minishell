/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:09:13 by dminh             #+#    #+#             */
/*   Updated: 2026/03/16 15:37:11 by dminh            ###   ########.fr       */
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
		free((*head)->path);
		(*head)->path = NULL;
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

int	ft_exit(t_args *args, t_token *token, int exit_code)
{
	t_env	*tmp;

	ft_free_all(args);
	while (args->env)
	{
		tmp = args->env->next;
		free_env_node(args->env);
		args->env = tmp;
	}
	ft_token_clear(&token);
	rl_clear_history();
	exit(exit_code);
}
