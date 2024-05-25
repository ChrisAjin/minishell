/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prt_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:28:21 by cassassa          #+#    #+#             */
/*   Updated: 2024/03/22 15:28:21 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	prt_str(char const *str)
{
	if (str == NULL)
		return (write(STDOUT_FILENO, "(null)", 6));
	else
		return (write(STDOUT_FILENO, str, ft_strlen(str)));
}
