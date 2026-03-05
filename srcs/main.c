/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:10:36 by dminh             #+#    #+#             */
/*   Updated: 2026/03/05 18:12:57 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*To be implemented functions prototypes*/
void	ft_exec_outfile();
void	ft_cmd_parsing();

void	ft_child_infile(char *path, char **cmd, int fd2, int infile);

void	ft_exec_infile(char *path, char **cmd, int fd[2])
{
	char	*infile_name;
	char	buf[100];
	int		pid;
	int		infile;
	int		bytes;

	infile_name = cmd[0];
	pipe(fd);
	pid = fork();
	if (pid == CHILD)
	{
		if (cmd[1])
		{
				printf("%s\n", cmd[1]);
				infile = open(infile_name, O_RDONLY);
				dup2(infile, STDIN_FILENO);
				dup2(fd[PIPE_WRITE], STDOUT_FILENO);
				close(fd[PIPE_WRITE]);
				close(fd[PIPE_READ]);
				close(infile);
				execve(path, &cmd[1], NULL);
			}
		}
		else
		{
			if (cmd[1])
			{
				close(fd[PIPE_WRITE]);
				bytes = 1;
				while (bytes > 0)
				{
					bytes = read(fd[PIPE_READ], buf, 1);
					write(2, &buf[0], 1);
				}
				close(fd[PIPE_READ]);
			}
			waitpid(pid, NULL, 0);
	}
}

void	ft_exec_cmd(char *path, char **cmd)
{
	int	pid;

	pid = fork();
	if (pid == CHILD)
		execve(path, cmd, NULL);
	else
		waitpid(pid, NULL, 0);
}

int	main(void)
{
	t_token	*token;
	//t_token *tmp;
	t_args	args;

	ft_memset(&args, 0, sizeof(args));
	while (true)
	{
		args.input = readline(PROMPT);
		add_history(args.input);
		token = ft_lexer(args.input);
		//tmp = token;
		args.cmd = ft_cmd(token);
//		while (tmp)
//		{
//			printf("content = %s, type = %d\n", tmp->content, tmp->type);
//			tmp = tmp->next;
//		}
//		for(int i = 0; args.cmd[i]; i++)
//			printf("cmd[i] = %s\n", args.cmd[i]);
		if (args.input)
		{
			if (!ft_exit(&args, token))
			{
			if (ft_get_cmd(&args, token))
				printf("minishell: %s: command not found\n", args.input);
			printf("%s\n", args.cmd_path);
			//			if (args.redirect == INFILE)
			//				ft_exec_infile(args.cmd_path, args.cmd, args.fd);
			//			else
			ft_exec_cmd(args.cmd_path, args.cmd);
			}
		}
		ft_free_all(&args);
		ft_token_clear(&token);
	}
	return (EXIT_SUCCESS);
}
