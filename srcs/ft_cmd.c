/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:24:34 by dminh             #+#    #+#             */
/*   Updated: 2026/03/16 13:51:13 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_init_cmd(char *infile, char *outfile, int size)
{
	t_cmd	*node;

	node = ft_calloc(1, sizeof(*node));
	if (!node)
		return (NULL);
	node->cmd = ft_calloc(size + 1, sizeof(*node->cmd));
	if (!node->cmd)
		return (NULL);
	node->path = NULL;
	node->infile = infile;
	node->outfile = outfile;
	node->in_fd = 0;
	node->out_fd = 0;
	node->built_in = false;
	node->append = false;
	node->next = NULL;
	return (node);
}

void	ft_filename(t_token *token, char **in, char **out, t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		*in = token->content;
	else if (type == TOKEN_REDIR_OUT)
		*out = token->content;
}

t_cmd	*ft_get_cmd_size(t_token *token)
{
	t_cmd			*cmd;
	char			*infile;
	char			*outfile;
	int				size;
	t_token_type	file_type;

	infile = NULL;
	outfile = NULL;
	file_type = TOKEN_WORD;
	size = 0;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD)
			size++;
		else if (token->type == TOKEN_REDIR_IN
			|| token->type == TOKEN_REDIR_OUT)
			file_type = token->type;
		else if (token->type == TOKEN_FILENAME)
			ft_filename(token, &infile, &outfile, file_type);
		token = token->next;
	}
	cmd = ft_init_cmd(infile, outfile, size);
	return (cmd);
}

t_cmd	*ft_cmd(t_token *token, t_cmd *cmd, int *nb_cmd)
{
	int		i;

	if (!token)
		return (NULL);
	cmd = ft_get_cmd_size(token);
	if (!cmd || !cmd->cmd)
		return (NULL);
	i = 0;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD)
		{
			cmd->cmd[i] = ft_strdup(token->content);
			if (!cmd->cmd[i])
				return (NULL);
			i++;
		}
		token = token->next;
	}
	(*nb_cmd)++;
	if (token && token->type == TOKEN_PIPE)
		cmd->next = ft_cmd(token->next, cmd->next, nb_cmd);
	return (cmd);
}
