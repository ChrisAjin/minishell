<<<<<<< HEAD:libft/src/ft_putstr_fd.c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:41:48 by cassassa          #+#    #+#             */
/*   Updated: 2024/05/27 14:41:48 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	while (s[++i])
		write(fd, &s[i], 1);
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:11:00 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/13 20:11:20 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// :(
>>>>>>> origin/ines_3:src/builtins/unset.c