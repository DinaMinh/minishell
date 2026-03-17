/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:37:03 by dminh             #+#    #+#             */
/*   Updated: 2026/03/16 14:51:34 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_operator(t_token **token, char *line, int *i)
{
	int	err;

	err = 0;
	if (ft_strncmp("<<", &line[*i], 2) == 0)
	{
		err = ft_token_addback(token, ft_strdup("<<"), TOKEN_HEREDOC);
		*i += 2;
	}
	else if (ft_strncmp(">>", &line[*i], 2) == 0)
	{
		err = ft_token_addback(token, ft_strdup(">>"), TOKEN_APPEND);
		*i += 2;
	}
	else
	{
		if (line[*i] == '|')
			err = ft_token_addback(token, ft_strdup("|"), TOKEN_PIPE);
		else if (line[*i] == '<' || line[*i] == '>')
			err = ft_handle_redir(token, line, i);
		(*i)++;
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
	status = args->return_val;
	i = 0;
	while (args->input[i])
	{
		while (args->input[i] && ft_is_blank(args->input[i]))
			i++;
		if (!args->input[i] || args->return_val == 1)
			break ;
		if (ft_is_operator(args->input[i]) == true)
			args->return_val = ft_handle_operator(&token_list, args->input, &i);
		else
			args->return_val = ft_handle_word(&token_list, args->input, &i);
	}
	if (args->return_val)
	{
		ft_token_clear(&token_list);
		return (NULL);
	}
	args->return_val = status;
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
