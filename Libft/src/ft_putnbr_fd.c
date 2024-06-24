/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:41:54 by cassassa          #+#    #+#             */
/*   Updated: 2024/05/27 14:41:54 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	x;
	char			c;

	if (n < 0)
	{
		write(fd, "-", 1);
		x = -n;
	}
	else
		x = n;
	while (x >= 10)
	{
		ft_putnbr_fd(x / 10, fd);
		x %= 10;
	}
	c = x + '0';
	write(fd, &c, 1);
}
