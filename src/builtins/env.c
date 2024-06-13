/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:22:27 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/13 16:36:59 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// voir si quand plusieurs childs le texte s'ecrit quand mm dans le bon ordre
// tester dans le bash pour confirmer les cas d'erreurs
int	env_cmd(t_data *minishell)
{
	if (minishell->cmd->cmd_param[1][0] == '-')
	{
		ft_putstr_fd("invalid option -- ", 2);
		ft_putendl_fd(minishell->cmd->cmd_param[1], 2);
		// free_all(minishell, NULL, -1);
		return (125);
	}
	else if (minishell->cmd->cmd_param[1][0] != '\0')
	{
		// free_all(minishell, NULL, -1);
		ft_putstr_fd("No such file or directory: ", 2);
		ft_putendl_fd(minishell->cmd->cmd_param[1], 2);
		return (127);
	}
	// free_all(minishell, NULL, -1);
	return (print_lst(minishell->env));
}

int	print_lst(t_list *lst)
{
	while (lst)
	{
		if (printf("%s\n", lst->str) < 0)
		{
			perror("printf");
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}
