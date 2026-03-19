/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 09:55:50 by dminh             #+#    #+#             */
/*   Updated: 2026/03/19 13:45:05 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_print_err(t_args *args, char *delimiter, int fd)
{
	char	*nb_lines;

	nb_lines = ft_itoa(args->lines);
	if (!nb_lines)
	{
		close(fd);
		return (1);
	}
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putstr_fd(nb_lines, 2);
	free(nb_lines);
	ft_putstr_fd(" delimited by end-of-line (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("\')\n", 2);
	return (0);
}

int	ft_check_heredoc(t_args *args, char *input, char *delimiter, int fd)
{
	if (!input)
	{
		if (ft_print_err(args, delimiter, fd))
			args->return_val = 1;
		else
			args->return_val = 0;
		close(fd);
		return (1);
	}
	if (ft_strcmp(input, delimiter) == 0)
	{
		free(input);
		close(fd);
		args->return_val = 0;
		return (1);
	}
	return (0);
}

int	ft_check_status(t_args *args, int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT)
		{
			args->return_val = WTERMSIG(status) + 128;
			return (1);
		}
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		args->return_val = SIGINT + 128;
		return (1);
	}
	else if (WIFEXITED(status))
	{
		args->return_val = WEXITSTATUS(status);
		if (args->return_val != 0)
			return (1);
		return (0);
	}
	return (0);
}

char	*ft_set_heredoc_name(t_args *args)
{
	char	*name;
	char	*nb;
	int		i;

	i = 0;
	nb = ft_itoa(i + args->heredoc);
	if (!nb)
		return (NULL);
	name = ft_strjoin(HEREDOC, nb);
	if (!name)
		return (NULL);
	free(nb);
	while (access(name, F_OK) == 0)
	{
		i++;
		nb = ft_itoa(i + args->heredoc);
		if (!nb)
			return (NULL);
		free(name);
		name = ft_strjoin(HEREDOC, nb);
		if (!name)
			return (NULL);
		free(nb);
	}
	return (name);
}
