/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:10:36 by dminh             #+#    #+#             */
/*   Updated: 2026/03/19 00:36:27 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

static void	execute_commands(t_args *args, t_token *token)
{
	int	status;

	ft_check_built_in(args);
	if (ft_handle_local_vars(args, args->cmd) == 1)
	{
		args->return_val = 0;
		return ;
	}
	status = ft_get_path(args->cmd, token);
	if (status == 1)
		args->return_val = status;
	ft_exec(args, token);
	args->lines++;
}

static void	ft_count_heredocs(t_token *token, t_args *args)
{
	while (token)
	{
		if (token->type == TOKEN_HEREDOC)
			args->total_heredoc++;
		token = token->next;
	}
	if (args->total_heredoc >= 16)
	{
		ft_putstr_fd("minishell: maximum here-document count exceeded", 2);
		ft_exit(args, token, 2);
	}
}

int	ft_minishell(t_token *token, t_args *args)
{
	g_sig = 0;
	setup_interactive_signals();
	args->input = readline(PROMPT);
	if (g_sig != 0)
		args->return_val = g_sig + 128;
	if (!args->input)
	{
		printf("exit\n");
		ft_exit(args, token, args->return_val);
	}
	if (*args->input)
		add_history(args->input);
	token = ft_lexer(args);
	if (token)
	{
		args->token_head = token;
		ft_expand_tokens(token, args);
	}
	ft_count_heredocs(token, args);
	args->cmd = ft_cmd(token, args, args->cmd, &args->nb_cmd);
	if (args->cmd)
		execute_commands(args, token);
	ft_free_all(args);
	ft_token_clear(&token);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_token	*token;
	t_args	args;

	ft_memset(&args, 0, sizeof(args));
	token = NULL;
	args.envp = envp;
	args.env = init_env(envp);
	if (ac != 1 || av[1])
		return (EXIT_FAILURE);
	while (true)
		ft_minishell(token, &args);
	return (EXIT_SUCCESS);
}
