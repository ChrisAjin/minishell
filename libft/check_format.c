/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:41:46 by inbennou          #+#    #+#             */
/*   Updated: 2024/02/13 17:44:52 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_format(const char *format, int i, va_list args)
{
	if (format[i + 1] == 'c')
		return (ft_putlenchar(va_arg(args, int)));
	if (format[i + 1] == 's')
		return (ft_putlenstr(va_arg(args, char *)));
	else if (format[i + 1] == 'p')
		return (ft_puthexa_p(va_arg(args, unsigned long long)));
	else if ((format[i + 1] == 'd') || (format[i + 1] == 'i'))
		return (ft_putdec(va_arg(args, int)));
	else if (format[i + 1] == 'u')
		return (ft_unsignedputnbr(va_arg(args, unsigned int)));
	else if (format[i + 1] == 'x')
		return (ft_puthexa(va_arg(args, unsigned int)));
	else if (format[i + 1] == 'X')
		return (ft_puthexa_low(va_arg(args, unsigned int)));
	else if (format[i + 1] == '%')
		return (ft_putlenchar('%'));
	return (0);
}
