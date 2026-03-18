/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:37:03 by dminh             #+#    #+#             */
/*   Updated: 2026/03/18 12:25:52 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_operator(t_token **token, char *line, int *i)
{
	int	err;

	err = 0;
	if (ft_strncmp(">>", &line[*i], 2) == 0)
		err = ft_handle_redir(token, line, i, TOKEN_APPEND);
	else if (ft_strncmp("<<", &line[*i], 2) == 0)
		err = ft_handle_redir(token, line, i, TOKEN_HEREDOC);
	else
	{
		if (line[*i] == '|')
		{
			err = ft_token_addback(token, ft_strdup("|"), TOKEN_PIPE);
			(*i)++;
		}
		else if (line[*i] == '<') 
			err = ft_handle_redir(token, line, i, TOKEN_REDIR_IN);
		else if (line[*i] == '>')
			err = ft_handle_redir(token, line, i, TOKEN_REDIR_OUT);

	}
	return (err);
}

static int	ft_handle_word(t_token **token, char *line, int *start)
{
	char	quote;
	int		end;

	end = *start;
	quote = '\0';
	while (line[end] && !ft_is_operator(line[end]) && !ft_is_blank(line[end]))
	{
		if (line[end] == D_QUOTE || line[end] == S_QUOTE)
		{
			if (ft_handle_quotes(line, &end, &quote))
			{
				ft_putstr_fd("Unclosed quote. Returning to prompt\n", 2);
				return (1);
			}
		}
		else
			end++;
	}
	if (ft_add_word(token, end - *start, &line[*start]) == false)
		return (1);
	*start = end;
	return (0);
}

t_token	*ft_lexer(t_args *args)
{
	t_token	*token_list;
	int		i;
	int		status;

	token_list = NULL;
	status = 0;
	i = 0;
	while (args->input[i])
	{
		while (args->input[i] && ft_is_blank(args->input[i]))
			i++;
		if (!args->input[i] || status)
			break ;
		if (ft_is_operator(args->input[i]) == true)
			status = ft_handle_operator(&token_list, args->input, &i);
		else
			status = ft_handle_word(&token_list, args->input, &i);
	}
	if (status)
	{
		args->return_val = status;
		ft_token_clear(&token_list);
		return (NULL);
	}
	return (token_list);
}
//int	main(void)
//{
//	t_token	*node;
//	t_token *tmp;
//	char	*input;
//
//	while (true)
//	{
//		input = readline(PROMPT);
//		node = ft_lexer(input);
//		tmp = node;
//		while (tmp)
//		{
//			printf("content = %s, type = %d\n", tmp->content, tmp->type);
//			tmp = tmp->next;
//		}
//		ft_token_clear(&node);
//	}
//	return (EXIT_SUCCESS);
//}
