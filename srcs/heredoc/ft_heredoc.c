/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 12:44:13 by dminh             #+#    #+#             */
/*   Updated: 2026/03/18 12:44:13 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_heredoc(char *delimiter, char *filename)
{
	char	*input;
	int		fd;
	int		len;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd < 0)
		return (1) ;
	while (true)
	{
		len = 0;
		input = readline("> ");
		if (ft_strcmp(input, delimiter) == 0)
		{
			free(input);
			close(fd);
			break ;
		}
		if (input)
			len = ft_strlen(input);
		write(fd, input, len);
		write(fd, "\n", 1);
		free(input);
	}
	return (0);
}

int	ft_init_heredoc(t_token **token, t_fd **redir, int *nb, t_token_type type)
{
	char	*heredoc_nb;
	char	*filename;

	heredoc_nb = ft_itoa(*nb);
	if (!heredoc_nb)
		return (1);
	filename = ft_strjoin(HEREDOC, heredoc_nb);
	if (!filename)
		return (1);
	if (ft_heredoc((*token)->content, filename))
		return (1);
	if (!ft_fd_addback(redir, filename, type))
		return (1);
	free(heredoc_nb);
	free(filename);
	(*nb)++;
	return (0);
}
