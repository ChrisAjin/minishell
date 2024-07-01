/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:40:25 by inbennou          #+#    #+#             */
/*   Updated: 2024/02/13 17:44:38 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
int		ft_putdec(int n);
int		ft_puthexa(unsigned int n);
int		ft_puthexa_low(unsigned int n);
int		ft_puthexa_p(unsigned long long nbl);
int		ft_hexa_not0(unsigned long long nbl);
int		ft_unsignedputnbr(unsigned int n);
void	ft_putchar(char c);
int		ft_putlenchar(char c);
int		ft_putlenstr(char *s);
int		check_format(const char *format, int i, va_list args);
int		size_hexa(unsigned int n);
int		size_dec(int n);
int		size_u(unsigned int n);
int		size_p(unsigned long long nbr);

#endif