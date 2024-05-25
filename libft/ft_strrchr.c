/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:27:09 by cassassa          #+#    #+#             */
/*   Updated: 2024/03/22 15:27:10 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	j;

	j = ft_strlen(str);
	if (c == '\0')
		return ((char *)str + j);
	while (j >= 0)
	{
		if (str[j] == c)
			return ((char *)str + j);
		j--;
	}
	return (NULL);
}
