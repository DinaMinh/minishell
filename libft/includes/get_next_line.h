/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:53:55 by dminh             #+#    #+#             */
/*   Updated: 2026/01/22 00:44:33 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 42
# define MAX_FD 1024

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

char	*ft_is_nl(char *str);
char	*get_next_line(int fd);
char	*ft_read_line(char *res, int fd, char *line, size_t *len);
char	*ft_set_line(char *s1, char *s2, size_t *len);
void	ft_del_printed(char *buffer);
#endif
