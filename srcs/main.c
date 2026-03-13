/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:10:36 by dminh             #+#    #+#             */
/*   Updated: 2026/03/13 16:52:49 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*To be implemented functions prototypes*/
void	ft_exec_outfile();
void	ft_cmd_parsing();

int	ft_minishell(t_token *token, t_args args, char **envp)
{
	(void)envp;
	args.input = readline(PROMPT);
	add_history(args.input);
	token = ft_lexer(args.input);
	args.cmd = ft_cmd(token, args.cmd, &args.nb_cmd);
	if (args.input)
	{
		if (!ft_exit(&args, token))
		{
			ft_check_built_in(&args, token);
			if (ft_get_path(args.cmd, token))
				printf("minishell: %s: command not found\n", args.input);
			ft_exec_pipe(token, &args);
		}
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_token	*token;
	t_args	args;

	ft_memset(&args, 0, sizeof(args));
	args.envp = envp;
	token = NULL;
	args.env = init_env(envp);
	if (ac != 1 || av[1])
		return (EXIT_FAILURE);
	while (true)
	{
		ft_minishell(token, args, envp);
		ft_free_all(&args);
		ft_token_clear(&token);
	}
	return (EXIT_SUCCESS);
}
