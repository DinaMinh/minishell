/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:09:13 by dminh             #+#    #+#             */
/*   Updated: 2026/03/20 12:28:26 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_clear(t_fd **redir)
{
	t_fd	*tmp;

	while (*redir)
	{
		tmp = (*redir)->next;
		if ((*redir)->file_type == TOKEN_HEREDOC)
		{
			unlink((*redir)->filename);
			free((*redir)->filename);
		}
		free(*redir);
		*redir = tmp;
	}
}

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
		ft_redir_clear(&(*head)->redir);
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
	int		i;

	ft_free_all(args);
	while (args->env)
	{
		tmp = args->env->next;
		free_env_node(args->env);
		args->env = tmp;
	}
	if (args->dup_in != -1)
		close(args->dup_in);
	if (args->dup_out != -1)
		close(args->dup_out);
	i = 0;
	while (args->envp[i])
		i++;
	ft_free_envp(args->envp, i);
	ft_token_clear(&token);
	rl_clear_history();
	exit(exit_code);
}
