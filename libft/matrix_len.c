/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:28:00 by cassassa          #+#    #+#             */
/*   Updated: 2024/03/22 15:28:00 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	matrix_len(char **matrix)
{
	size_t	i;

	if (!matrix)
		return (0);
	while (matrix[i])
		i += 1;
	return (i);
}
