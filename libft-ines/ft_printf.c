/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:43:06 by inbennou          #+#    #+#             */
/*   Updated: 2024/02/13 17:44:58 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		res;

	if (format == 0)
		return (0);
	i = 0;
	res = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			res += check_format(format, i, args);
			i++;
		}
		else
			res += ft_putlenchar(format[i]);
		i++;
	}
	va_end(args);
	return (res);
}
// int	main(void)
// {
// 	unsigned int	p = 0;
// 	int i;
// 	int j;
// 	i = printf("%x\n", p);
// 	j = ft_printf("%x\n", p);
// 	printf("%d %d", i, j);
// }