/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:24:41 by cassassa          #+#    #+#             */
/*   Updated: 2024/03/22 15:24:41 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*mem_allocated;
	unsigned int	total;
	size_t			i;

	if (nmemb == 0 || size == 0)
		return (NULL);
	total = nmemb * size;
	mem_allocated = malloc(total);
	if (mem_allocated == NULL)
		return (NULL);
	i = 0;
	while (total-- > 0)
		mem_allocated[i++] = 0;
	return ((void *)mem_allocated);
}
