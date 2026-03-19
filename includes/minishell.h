/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:11:03 by dminh             #+#    #+#             */
/*   Updated: 2026/03/19 01:27:18 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdbool.h>
# include <signal.h>
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
# define HEREDOC ".tmp_heredoc"

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

extern int	g_sig;

typedef enum e_token_type
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
	bool			local;
	struct s_env	*next;
}	t_env;	

typedef struct s_token
{
	char					*content;
	t_token_type			type;
	struct s_token			*next;
}	t_token;

typedef struct s_fd
{
	char			*filename;
	char			*delimiter;
	t_token_type	file_type;
	int				fd;
	struct s_fd		*next;
}	t_fd;

typedef struct s_cmd
{
	char			**cmd;
	char			*path;
	bool			built_in;
	bool			append;
	t_fd			*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_args
{
	char			**envp;
	int				fd[2];
	char			*input;
	int				lines;
	int				nb_forks;
	int				total_heredoc;
	int				heredoc;
	int				nb_cmd;
	int				return_val;
	t_token			*token_head;
	t_cmd			*cmd;
	t_env			*env;
}	t_args;

t_cmd		*ft_cmd(t_token *token, t_args *args, t_cmd *cmd, int *nb_cmd);
t_fd		*ft_fd_new(char *filename, t_token_type file_type);
t_fd		*ft_fd_addback(t_fd **redir, char *filename,
				t_token_type file_type);
int			ft_get_path(t_cmd *cmd, t_token *token);
int			ft_check_built_in(t_args *args);
void		ft_free_all(t_args *args);

char		*ft_set_heredoc_name(t_args *args);
int			ft_init_heredoc(t_token **token, t_fd **redir, t_args *args,
				t_token_type type);
int			ft_check_status(t_args *args, int status);
int			ft_check_heredoc(t_args *args, char *input, char *delimiter,
				int fd);

int			ft_exit(t_args *args, t_token *token, int exit_code);

t_token		*ft_lexer(t_args *args);
t_token		*ft_token_new(char *str, t_token_type type);
int			ft_handle_quotes(char *line, int *end, char *quote);
int			ft_handle_filename(t_token **token, char *line, int *start);
int			ft_add_word(t_token **token, int len, char *line);
int			ft_token_addback(t_token **head, char *str, t_token_type type);
void		ft_token_clear(t_token **head);

int			ft_is_blank(char c);
int			ft_is_operator(char c);
int			ft_handle_redir(t_token **token, char *line, int *i,
				t_token_type type);

void		ft_close_fds(t_cmd *cmd, int fd[2], int *reading);
void		ft_exec(t_args *args, t_token *token);
void		ft_built_in(t_args *args, t_cmd *cmd, t_token *token, int *reading);
void		ft_built_in_only(t_args *args, t_token *token, int *reading);
void		ft_print_interrupt(t_args *args, int status, bool *print);
int			ft_check_fork(t_args *args, t_cmd *cmd, int pid);
int			ft_open_fds(t_cmd *cmd, int fd[2]);
int			ft_pipe(t_cmd *cmd, t_args *args);
int			ft_open_fds(t_cmd *cmd, int fd[2]);

t_env		*init_env(char **envp);
t_env		*create_env_node(char *env_str, bool is_local);
t_env		*find_env_node(t_env *env_list, char *key);
char		*ft_append_char(char *str, char c);
char		*ft_append_str(char *s1, char *s2);
void		env_add_back(t_env **env_list, t_env *new_node);
void		update_env(t_env **env_list, char *key, char *value, bool is_local);
void		free_env_node(t_env *node);
void		sort_and_print_env(t_env *env_list, int fd_out);
void		ft_expand_tokens(t_token *tokens, t_args *args);
int			builtin_env(t_env *env_list, int fd_out);
int			builtin_export(t_args *cmd_node, t_env **env_list);
int			builtin_pwd(int fd_out);
int			builtin_unset(t_args *cmd_node, t_env **env_list);
int			builtin_cd(char **args, t_env **env);
int			builtin_echo(char **args, int fd_out);
int			builtin_exit(t_args *main, t_token *token, char **cmd);
int			is_valid_env_name(char *str);
int			ft_handle_local_vars(t_args *args, t_cmd *cmd);

void		ft_print_error_cmd(char *cmd);

char		**env_list_to_array(t_env *env_list);
void		free_env_array(char **envp);

void		setup_interactive_signals(void);
void		setup_heredoc_signals(void);
void		setup_parent_signals(void);
void		setup_child_signals(void);

#endif
