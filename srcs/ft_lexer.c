/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:37:03 by dminh             #+#    #+#             */
/*   Updated: 2026/03/09 11:41:39 by dminh            ###   ########.fr       */
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
