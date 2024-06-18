/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:22:27 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/18 17:51:05 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// voir pourquoi env -i ./minishell on a quand mm pwd et old pwd
// voir si quand plusieurs childs le texte s'ecrit quand mm dans le bon ordre
// tester dans le bash pour confirmer les cas d'erreurs
int	env_cmd(t_data *minishell)
{
	if (!minishell->cmd->cmd_param[1] || minishell->cmd->cmd_param[1] == NULL)
		return (print_lst(minishell->env));
	if (minishell->cmd->cmd_param[1][0] == '-')
	{
		ft_putstr_fd("env: invalid option -- ", 2);
		ft_putendl_fd(minishell->cmd->cmd_param[1], 2);
		return (125);
	}
	else
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(minishell->cmd->cmd_param[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
}

int	print_lst(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (1);
	// temp = lst;
	// if (printf("%s\n", temp->str) < 0)
	// {
	// 	perror("printf");
	// 	return (1);
	// }
	temp = lst->next;
	while (temp != lst)
	{
		if (printf("%s\n", temp->str) < 0)
		{
			perror("printf");
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}
