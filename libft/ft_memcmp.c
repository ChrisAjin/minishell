/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:25:33 by cassassa          #+#    #+#             */
/*   Updated: 2024/03/22 15:25:33 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	const unsigned char	*conv_str1;
	const unsigned char	*conv_str2;
	size_t				i;

	conv_str1 = (unsigned char *)str1;
	conv_str2 = (unsigned char *)str2;
	i = 0;
	if (n == 0)
		return (0);
	while ((conv_str1[i] == conv_str2[i]) && i < (n - 1))
		i++;
	return (conv_str1[i] - conv_str2[i]);
}
