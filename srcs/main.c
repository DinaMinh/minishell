/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:10:36 by dminh             #+#    #+#             */
/*   Updated: 2026/03/18 14:10:25 by dminh            ###   ########.fr       */
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
}

int	ft_minishell(t_token *token, t_args *args)
{
	setup_interactive_signals();
	args->input = readline(PROMPT);
	if (!args->input)
	{
		printf("exit\n");
		ft_free_all(args);
		exit(args->return_val);
	}
	if (args->input && *args->input)
		add_history(args->input);
	token = ft_lexer(args);
	if (token)
		ft_expand_tokens(token, args);
	args->cmd = ft_cmd(token, args->cmd, &args->nb_cmd);
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
