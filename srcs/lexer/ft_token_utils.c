/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:43:04 by dminh             #+#    #+#             */
/*   Updated: 2026/03/20 15:29:35 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_token_new(char *str, t_token_type type)
{
	t_token	*node;

	node = ft_calloc(1, sizeof(*node));
	if (!node)
		return (NULL);
	node->content = str;
	node->type = type;
	node->exp_heredoc = false;
	node->next = NULL;
	return (node);
}

int	ft_token_addback(t_token **head, char *str, t_token_type type)
{
	t_token	*node;
	t_token	*tmp;

	node = ft_token_new(str, type);
	if (!node)
		return (1);
	if (!*head)
	{
		node->next = *head;
		*head = node;
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	return (0);
}

void	ft_token_clear(t_token **head)
{
	t_token	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		if ((*head)->content)
			free((*head)->content);
		free(*head);
		*head = tmp;
	}
	*head = NULL;
}

void	ft_token_del(t_token **head, t_token *to_delete)
{
	t_token	*current;

	if (!head || !*head || !to_delete)
		return ;
	if (*head == to_delete)
	{
		*head = to_delete->next;
		if (to_delete->content)
			free(to_delete->content);
		free(to_delete);
		return ;
	}
	current = *head;
	while (current && current->next != to_delete)
		current = current->next;
	if (current && current->next == to_delete)
	{
		current->next = to_delete->next;
		if (to_delete->content)
			free(to_delete->content);
		free(to_delete);
	}
}

void	ft_expand_word(char *expanded, t_token *tmp,
	t_token **tokens, t_args *args)
{
	expanded = expand_and_strip(tmp->content, args);
	free(tmp->content);
	tmp->content = NULL;
	if (!expanded)
		ft_token_del(tokens, tmp);
	else
		tmp->content = expanded;
}
