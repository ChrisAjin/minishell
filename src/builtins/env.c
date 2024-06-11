/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:22:27 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/11 17:10:28 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// voir si quand plusieurs childs le texte s'ecrit quand mm dans le bon ordre
// tester dans le bash pour confirmer les cas d'erreurs
void	env_cmd(t_data *minishell)
{
	if (minishell->cmd->cmd_param[1][0] == '-')
	{
		ft_putstr_fd("invalid option -- ", 2);
		ft_putendl_fd(minishell->cmd->cmd_param[1], 2);
		// free all
		exit(125);
	}
	else if (minishell->cmd->cmd_param[1][0] != '\0')
	{
		// free all
		ft_putstr_fd("No such file or directory: ", 2);
		ft_putendl_fd(minishell->cmd->cmd_param[1], 2);
		exit(127);
	}
	// free all
	print_lst(minishell->env);
}

void	print_lst(t_list *lst)
{
	while (lst)
	{
		if (printf("%s\n", lst->str) < 0)
		{
			perror("printf");
			exit(1);
		}
		lst = lst->next;
	}
	exit(0);
}
