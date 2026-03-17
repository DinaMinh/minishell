/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:10:36 by dminh             #+#    #+#             */
/*   Updated: 2026/03/17 14:20:56 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_minishell(t_token *token, t_args *args)
{
	int	status;

	args->input = readline(PROMPT);
	add_history(args->input);
	token = ft_lexer(args);
	ft_expand_tokens(token, args);
	args->cmd = ft_cmd(token, args->cmd, &args->nb_cmd);
	if (args->return_val == 1)
		;
	else if (args->input)
	{
		ft_check_built_in(args);
		status = ft_get_path(args->cmd, token);
		if (status == 1)
			args->return_val = status;
		ft_exec(args, token);
	}
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
	args.env = init_env(envp);
	if (ac != 1 || av[1])
		return (EXIT_FAILURE);
	while (true)
		ft_minishell(token, &args);
	return (EXIT_SUCCESS);
}
