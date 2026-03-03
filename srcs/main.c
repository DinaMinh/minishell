/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:10:36 by dminh             #+#    #+#             */
/*   Updated: 2026/03/03 16:05:34 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_cmd(char *input_name)
{
	char	**output;
	char	*cmd_path;
	int		cmd_len;

	cmd_len = ft_strlen(input_name) + PATH_LEN;
	cmd_path = ft_calloc(cmd_len + 1, sizeof(*cmd_path));
	if (!cmd_path)
		return (NULL);
	ft_strlcpy(cmd_path, PATH, PATH_LEN);
	cmd_path = ft_strncat(cmd_path, input_name, cmd_len);
	if (access(cmd_path, F_OK) == -1)
		return (NULL);
	output = &cmd_path;
	return (output);
}

int	main(void)
{
	t_args	args;
	
	ft_memset(&args, 0, sizeof(args));
	while (true)
	{
		args.input_name = NULL;
		args.input_name = readline(PROMPT);
		if (!ft_strncmp(args.input_name, EXIT, EXIT_LEN))
			exit(EXIT_SUCCESS);
		if (args.input_name)
		{
			if (!get_cmd(args.input_name))
				printf("minishell: %s: command not found\n", args.input_name);
			add_history(args.input_name);
			free(args.input_name);
		}
	}
	return (EXIT_SUCCESS);
}
