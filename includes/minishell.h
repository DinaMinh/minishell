/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:11:03 by dminh             #+#    #+#             */
/*   Updated: 2026/03/04 13:39:21 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "minishell$ "

/* PARSING */
# define PATH "/usr/bin/"
# define PATH_LEN 10
# define EXIT "exit"
# define EXIT_LEN 4
# define INFILE 1
# define CMD_NOT_FOUND "command not found"

/* EXEC */
# define CHILD 0
# define PIPE_READ 0
# define PIPE_WRITE 1

typedef struct s_args
{
	char	**cmd;
	int		fd[2];
	char	*input_name;
	char	*cmd_path;
	int		redirect;
	int		return_value;
}	t_args;

char	**ft_get_cmd(t_args *args);

#endif
