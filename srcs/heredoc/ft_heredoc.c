/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 12:44:13 by dminh             #+#    #+#             */
/*   Updated: 2026/03/20 11:53:57 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_heredoc_child(char *delimiter, char *filename, t_args *args,
			bool expand)
{
	char	*input;
	int		fd;
	int		len;

	setup_heredoc_signals();
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd < 0)
		ft_exit(args, args->token_head, EXIT_FAILURE);
	while (true)
	{
		len = 0;
		input = readline("> ");
		if (ft_check_heredoc(args, input, delimiter, fd))
		{
			free(filename);
			ft_exit(args, args->token_head, args->return_val);
		}
		if (input && expand)
			input = ft_expand_heredoc(input, args);
		if (input)
			len = ft_strlen(input);
		write(fd, input, len);
		write(fd, "\n", 1);
		free(input);
	}
}

static int	ft_heredoc(char *delimiter, char *filename, t_args *args,
			bool expand)
{
	int	pid;
	int	status;

	status = 0;
	setup_parent_signals();
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		args->return_val = 1;
		return (EXIT_FAILURE);
	}
	if (pid == CHILD)
		ft_heredoc_child(delimiter, filename, args, expand);
	else
	{
		waitpid(pid, &status, 0);
		if (ft_check_status(args, status))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_init_heredoc(t_token **token, t_fd **redir, t_args *args,
		t_token_type type)
{
	char	*filename;

	args->lines++;
	filename = ft_set_heredoc_name(args);
	if (!filename)
		return (1);
	if (ft_heredoc((*token)->content, filename, args, (*token)->exp_heredoc))
	{
		unlink(filename);
		free(filename);
		return (1);
	}
	if (!ft_fd_addback(redir, filename, type))
	{
		unlink(filename);
		free(filename);
		return (1);
	}
	free(filename);
	args->heredoc++;
	return (0);
}
