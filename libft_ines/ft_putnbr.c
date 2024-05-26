/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:10:34 by inbennou          #+#    #+#             */
/*   Updated: 2024/02/13 17:45:10 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putdec(int n)
{
	long int	nbl;
	char		result;

	nbl = n;
	result = 0;
	if (nbl < 0)
	{
		write(1, "-", 1);
		nbl *= -1;
	}
	if (nbl >= 0 && nbl <= 9)
	{
		result = nbl + '0';
		write(1, &result, 1);
	}
	if (nbl >= 10)
	{
		ft_putdec(nbl / 10);
		ft_putdec(nbl % 10);
	}
	return (size_dec(n));
}

int	ft_unsignedputnbr(unsigned int n)
{
	long int	nbl;
	char		result;

	nbl = n;
	result = 0;
	if (nbl < 0)
	{
		write(1, "-", 1);
		nbl *= -1;
	}
	if (nbl >= 0 && nbl <= 9)
	{
		result = nbl + '0';
		write(1, &result, 1);
	}
	if (nbl >= 10)
	{
		ft_unsignedputnbr(nbl / 10);
		ft_unsignedputnbr(nbl % 10);
	}
	return (size_u(n));
}
