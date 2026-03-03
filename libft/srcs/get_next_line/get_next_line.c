/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:53:52 by dminh             #+#    #+#             */
/*   Updated: 2026/01/23 19:57:20 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_line(char *buffer, int fd, char *line, size_t	*len)
{
	ssize_t	reading;

	reading = 1;
	while (!ft_is_nl(line) && reading > 0)
	{
		reading = read(fd, buffer, BUFFER_SIZE);
		if (reading == -1)
		{
			if (line)
				free(line);
			buffer[0] = '\0';
			return (NULL);
		}
		if (reading == 0)
			break ;
		buffer[reading] = '\0';
		line = ft_set_line(line, buffer, len);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	size_t		len;
	static char	buffer[MAX_FD][BUFFER_SIZE + 1];

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	len = 0;
	if (buffer[fd][0])
	{
		line = ft_set_line(line, buffer[fd], &len);
		if (!line)
			return (NULL);
	}
	line = ft_read_line(buffer[fd], fd, line, &len);
	if (!line)
		return (NULL);
	ft_del_printed(buffer[fd]);
	return (line);
}

//int	main(int ac, char **av)
//{
//int	i;
//
//if (ac > 1)
//{
//char	*tab;
//tab =  0;
//i = 0;
//int	fd = open(av[1], O_RDONLY);
//while ((tab = get_next_line(fd)) != NULL && i < 3)
//{
//printf("%s", tab);
//free(tab);
//tab = NULL;
//i++;
//}
//if (tab)
//free(tab);
//close(fd);
//}
//return (0);
//}
