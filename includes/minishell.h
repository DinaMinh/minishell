/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:11:03 by dminh             #+#    #+#             */
/*   Updated: 2026/03/16 15:45:18 by dminh            ###   ########.fr       */
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

/* BUILT_IN */
# define BUILT_IN_CMD "echo cd pwd export unset env exit"
# define BUILT_IN_LEN 33
# define ECHO "echo"
# define ECHO_LEN 4
# define CD "cd"
# define CD_LEN 2
# define PWD "pwd"
# define PWD_LEN 3
# define EXPORT "export"
# define EXPORT_LEN 6
# define UNSET "unset"
# define UNSET_LEN 5
# define ENV "env"
# define ENV_LEN 3
# define EXIT "exit"
# define EXIT_LEN 4

typedef enum  e_token_type
{
	TOKEN_WORD,
	TOKEN_FILENAME,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;	

typedef struct s_token
{
	char					*content;
	t_token_type			type;
	struct s_token			*next;
}	t_token;

typedef struct s_cmd
{
	char			**cmd;
	char			*path;
	char			*infile;
	char			*outfile;
	int				in_fd;
	int				out_fd;
	bool			built_in;
	bool			append;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_args
{
	char			**envp;
	int				fd[2];
	char			*input;
	int				nb_cmd;
	int				return_val;
	t_cmd			*cmd;
	t_env			*env;
}	t_args;

t_cmd		*ft_cmd(t_token *token, t_cmd *cmd, int *nb_cmd);
int			ft_get_path(t_cmd *cmd, t_token *token);
int			ft_check_built_in(t_args *args);
void		ft_free_all(t_args *args);

int			ft_exit(t_args *args, t_token *token);

t_token		*ft_lexer(t_args *args);
t_token		*ft_token_new(char *str, t_token_type type);
int			ft_handle_quotes(char *line, int *end, int *start, char *quote);
int			ft_add_word(t_token **token, int len, char *line, char quote);
int			ft_token_addback(t_token **head, char *str, t_token_type type);
void		ft_token_clear(t_token **head);

int			ft_is_blank(char c);
int			ft_is_operator(char c);
int			ft_handle_redir(t_token **token, char *line, int *i);

void		ft_close_fds(t_cmd *cmd, int fd[2], int *reading);
void		ft_exec(t_args *args);
void		ft_exec_built_in(t_args *args, t_cmd *cmd, int *reading);
void		ft_built_in_only(t_args *args);

t_env		*init_env(char **envp);
t_env		*create_env_node(char *env_str);
t_env		*find_env_node(t_env *env_list, char *key);
void		env_add_back(t_env **env_list, t_env *new_node);
void		free_env_node(t_env *node);
int 		builtin_env(t_env *env_list, int fd_out);
int			builtin_export(t_args *cmd_node, t_env **env_list);
int			builtin_pwd(int fd_out);
int			builtin_unset(t_args *cmd_node, t_env **env_list);
int			builtin_cd(char **args, t_env **env);
int			builtin_echo(char **args, int fd_out);
int			builtin_exit(char **args, t_env *env_list, int last_status);
int			is_valid_env_name(char *str);

void	ft_print_error_cmd(char *cmd);

#endif
