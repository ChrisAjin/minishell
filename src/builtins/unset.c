/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:20:37 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/17 18:20:37 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// :(
int	unset(t_data *minishell)
{
	t_list	*temp;
	t_list	*del;

	temp = minishell->env->next;
	if (minishell->cmd->cmd_param[1][0] == '-')
	{
		ft_putstr_fd("unset: invalid option: ", 2);
		ft_putendl_fd(minishell->cmd->cmd_param[1], 2);
		return (2);
	}
	// while (temp != minishell->env)
	// {
		// if (ft_strncmp(minishell->cmd->cmd_param[1], temp->str,
		// 		ft_strlen(minishell->cmd->cmd_param[1]) == 0))
		// 	{
		// 		del = temp->str;
		// 		temp->prev->next = temp->next;
		// 		free(del);
		// 	}
	// }
}
