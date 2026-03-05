/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:43:04 by dminh             #+#    #+#             */
/*   Updated: 2026/03/05 14:18:59 by dminh            ###   ########.fr       */
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
