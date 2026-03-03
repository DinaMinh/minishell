/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:07:19 by dminh             #+#    #+#             */
/*   Updated: 2025/12/03 16:10:46 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

int	ft_printf(const char *spec, ...);
int	ft_putchar_len(int c);
int	ft_putstr_len(char *str);
int	ft_putnbr_len(int n);
int	ft_putlong_len(long n);
int	ft_putnbr_hex(unsigned int n, int spec);
int	ft_putptr_len(size_t ptr);
int	ft_putudec_len(unsigned int n);
#endif
