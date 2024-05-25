/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:55:55 by inbennou          #+#    #+#             */
/*   Updated: 2024/03/18 15:07:44 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	ch;

	i = 0;
	ch = c;
	while ((str[i] != ch) && (str[i]))
		i++;
	if (str[i] == ch)
		return ((char *)(str + i));
	else if (str[i] == '\0')
		return (0);
	else
		return ((char *)(str + ft_strlen(str)));
}

// int	main(void)
// {
// 	printf("ma fonction : %s \n", ft_strchr("chane", 105));
// 	printf("la vraie fonction : %s", strchr("chane", 105));
// }
