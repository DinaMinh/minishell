/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:11:03 by dminh             #+#    #+#             */
/*   Updated: 2026/03/09 14:27:30 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdbool.h>
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
# define D_QUOTE 34
# define S_QUOTE 39

/* EXEC */
# define CHILD 0
# define PIPE_READ 0
# define PIPE_WRITE 1

typedef enum  e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_token
{
	char					*content;
	t_token_type			type;
	struct s_token			*next;
}	t_token;

typedef struct s_cmd
{
	char			**cmd;
	char			*cmd_path;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_args
{
	int				fd[2];
	char			*input;
	int				nb_cmd;
	int				redirect;
	int				return_value;
	t_cmd			*cmd;
}	t_args;

t_cmd		*ft_cmd(t_token *token, t_cmd *cmd, int *nb_cmd);
int			ft_get_cmd(t_cmd *cmd, t_token *token);
void		ft_free_all(t_args *args);

int			ft_exit(t_args *args, t_token *token);

t_token		*ft_token_new(char *str, t_token_type type);
t_token		*ft_lexer(char *line);
int			ft_token_addback(t_token **head, char *str, t_token_type type);
void		ft_token_clear(t_token **head);

int			ft_is_blank(char c);
int			ft_is_operator(char c);
int			ft_handle_operator(t_token **token, char *line, int *i);
int			ft_handle_word(t_token **token, char *line, int *start);

void		ft_exec_pipe(t_cmd *cmd, int fd[2], int nb_cmd);

#endif
