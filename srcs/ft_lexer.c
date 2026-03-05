/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:37:03 by dminh             #+#    #+#             */
/*   Updated: 2026/03/05 15:43:08 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_token	*ft_lexer(char *line)
{
	t_token	*token_list;
	int		i;
	int		err;

	token_list = NULL;
	i = 0;
	err = 0;
	while (line[i] && err == 0)
	{
		while (line[i] && ft_is_blank(line[i]))
			i++;
		if (!line[i])
			break ;
		if (ft_is_operator(line[i]) == true)
			err = ft_handle_operator(&token_list, line, &i);
		else
			err = ft_handle_word(&token_list, line, &i);
	}
	if (err)
	{
		ft_token_clear(&token_list);
		return (NULL);
	}
	return (token_list);
}

char	**ft_cmd(t_token *token)
{
	t_token	*tmp;
	char	**cmd;
	int		size;
	int		i;

	while (token && token->type != TOKEN_WORD)
		token = token->next;
	tmp = token;
	size = 0;
	while (tmp && tmp->type == TOKEN_WORD)
	{
		size++;
		tmp = tmp->next;
	}
	cmd = ft_calloc(size + 1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	i = 0;
	while (token && token->type == TOKEN_WORD)
	{
		cmd[i] = ft_strdup(token->content);
		if (!cmd[i])
			return (NULL);
		token = token->next;
		i++;
	}
	return (cmd);
}

//int	main(void)
//{
//	t_token	*node;
//	t_token *tmp;
//	char	**cmd;
//	char	*input;
//
//	while (true)
//	{
//		input = readline(PROMPT);
//		node = ft_lexer(input);
//		tmp = node;
//		cmd = ft_cmd(node);
//		while (tmp)
//		{
//			printf("content = %s, type = %d\n", tmp->content, tmp->type);
//			tmp = tmp->next;
//		}
//		for(int i = 0; cmd[i]; i++)
//			printf("cmd[i] = %s\n", cmd[i]);
//		ft_token_clear(&node);
//	}
//	return (EXIT_SUCCESS);
//}
