/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:41:49 by inbennou          #+#    #+#             */
/*   Updated: 2024/02/13 17:45:02 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthexa_p(unsigned long long nbl)
{
	ssize_t	ret;

	ret = 0;
	if (nbl == 0)
		ret = write(1, "(nil)", 5);
	else
	{
		write(1, "0x", 2);
		ret = ft_hexa_not0(nbl);
	}
	return (ret);
}

int	size_p(unsigned long long nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= 16;
		i++;
	}
	return (i);
}

int	ft_hexa_not0(unsigned long long nbl)
{
	unsigned long long	n;

	n = nbl;
	if (nbl < 0)
	{
		write(1, "-", 1);
		nbl *= -1;
	}
	if (nbl >= 16)
	{
		ft_hexa_not0((nbl / 16));
		ft_hexa_not0((nbl % 16));
	}
	if (nbl >= 0 && nbl <= 9)
		ft_putchar(nbl + '0');
	if ((nbl >= 10) && (nbl <= 15))
		ft_putchar(nbl + 87);
	return (size_p(n) + 2);
}
// int	main(void)
// {
// 	printf("%d", ft_puthexa_fd_p(123456, 1));
// }