/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:43:01 by inbennou          #+#    #+#             */
/*   Updated: 2024/02/13 17:45:07 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthexa(unsigned int n)
{
	unsigned int	nbl;
	char			result;

	nbl = n;
	result = 0;
	if (nbl >= 16)
	{
		ft_puthexa(nbl / 16);
		ft_puthexa(nbl % 16);
	}
	if (nbl >= 0 && nbl <= 9)
	{
		result = nbl + '0';
		write(1, &result, 1);
	}
	if ((nbl >= 10) && (nbl <= 15))
	{
		nbl += 87;
		write(1, &nbl, 1);
	}
	return (size_hexa(n));
}

int	ft_puthexa_low(unsigned int n)
{
	unsigned int	nbl;
	char			result;

	nbl = n;
	result = 0;
	if (nbl >= 16)
	{
		ft_puthexa_low(nbl / 16);
		ft_puthexa_low(nbl % 16);
	}
	if (nbl >= 0 && nbl <= 9)
	{
		result = nbl + '0';
		write(1, &result, 1);
	}
	if ((nbl >= 10) && (nbl <= 15))
	{
		nbl += 55;
		write(1, &nbl, 1);
	}
	return (size_hexa(n));
}
