/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:10:36 by dminh             #+#    #+#             */
/*   Updated: 2026/03/04 14:44:27 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*To be implemented functions prototypes*/
void	ft_exec_outfile();
void	ft_cmd_parsing();

void	ft_child_infile(char *path, char **cmd, int fd2, int infile);

//void	ft_exec_infile(char *path, char **cmd, int fd[2])
//{
//	char	*infile_name;
//	char	*cat;
//	char	buf[100];
//	int		pid;
//	int		infile;
//	int		bytes;
//
//	infile_name = cmd[0];
//	cat = "cat";
//	pipe(fd);
//	pid = fork();
//	if (pid == CHILD)
//	{
//		infile = open(infile_name, O_RDONLY);
//		dup2(infile, STDIN_FILENO);
//		dup2(fd[PIPE_WRITE], STDOUT_FILENO);
//		close(fd[PIPE_WRITE]);
//		close(fd[PIPE_READ]);
//		close(infile);
//		if (cmd[1])
//			execve(path, &cmd[1], NULL);
//		else if (!cmd[1])
//			execve(path, &cat, NULL);
//	}
//	else
//	{
//		close(fd[PIPE_WRITE]);
//		bytes = 1;
//		while (bytes > 0)
//		{
//			bytes = read(fd[PIPE_READ], buf, 1);
//			write(2, &buf[0], 1);
//		}
//		close(fd[PIPE_READ]);
//		waitpid(pid, NULL, 0);
//	}
//}

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
	t_args	args;
	
	ft_memset(&args, 0, sizeof(args));
	while (true)
	{
		args.input_name = NULL;
		args.input_name = readline(PROMPT);
		printf("input = %s\n", args.input_name);
		add_history(args.input_name);
		if (!ft_strncmp(args.input_name, EXIT, EXIT_LEN))
			exit(EXIT_SUCCESS);
		if (args.input_name)
		{
			if (!ft_get_cmd(&args))
				printf("minishell: %s: command not found\n", args.input_name);
			//if (args.redirect == INFILE)
			//	ft_exec_infile(args.cmd_path, args.cmd, args.fd);
			//else
			ft_exec_cmd(args.cmd_path, args.cmd);
			free(args.input_name);
		}
	}
	return (EXIT_SUCCESS);
}
