/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:38:38 by inbennou          #+#    #+#             */
/*   Updated: 2023/11/27 17:05:36 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (write(fd, &s[i], 1) < 0)
				perror("write error");
			i++;
		}
	}
	if (write(fd, "\n", 1) < 0)
		perror("write error");
}

/*
int	main(void)
{
	ft_putendl_fd("bonjour", 1);
} */
