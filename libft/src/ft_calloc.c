/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:38:58 by cassassa          #+#    #+#             */
/*   Updated: 2024/05/27 14:38:58 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*tmp;

	if (count != 0 && size != 0 && size > 2147483647 / count)
		return (NULL);
	i = -1;
	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	while (++i < count * size)
		tmp[i] = 0;
	return (tmp);
}
