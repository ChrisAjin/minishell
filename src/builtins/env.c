/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:22:27 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/04 19:10:17 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tester dans le bash pour confirmer les cas d'erreurs
void	env_cmd(char **tab, char **env)
{
	if (tab[1] == NULL)
	{
		printf_tab(env);
		return ;
	}
	if (tab[1][0] == '-')
	{
		ft_putstr_fd("invalid option -- ", 2);
		ft_putendl_fd(tab[1], 2);
	}
	else
	{
		ft_putstr_fd("No such file or directory: ", 2);
		ft_putendl_fd(tab[1], 2);
	}
}

void	printf_tab(char **tab)
{
	int	y;

	y = 0;
	while (tab[y])
	{
		printf("%s\n", tab[y]);
		y++;
	}
}
