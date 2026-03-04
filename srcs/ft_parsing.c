/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:45:38 by dminh             #+#    #+#             */
/*   Updated: 2026/03/04 13:54:37 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_redir(t_args *args)
{
	char	*tmp;

	if (args->input_name[0] == '<' && args->input_name[1])
	{
		tmp = ft_strdup(&args->input_name[1]);
		free(args->input_name);
		args->redirect = INFILE;
		return (tmp);
	}
	args->redirect = 0;
	return (args->input_name);
}

char	**ft_get_cmd(t_args *args)
{
	int	cmd_len;

	args->input_name = ft_check_redir(args);
	args->cmd = ft_split(args->input_name, ' ');
	if (!args->cmd)
		return (NULL);
	cmd_len = ft_strlen(args->cmd[0]) + PATH_LEN;
	args->cmd_path = ft_calloc(cmd_len + 1, sizeof(*args->cmd_path));
	if (!args->cmd_path)
		return (NULL);
	ft_strlcpy(args->cmd_path, PATH, PATH_LEN);
	args->cmd_path = ft_strncat(args->cmd_path, args->cmd[0], cmd_len);
	if (access(args->cmd_path, F_OK) == -1)
		return (NULL);
	return (args->cmd);
}
