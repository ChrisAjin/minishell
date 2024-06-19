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
	// char	*del;

	temp = minishell->env->next;
	if (minishell->cmd->cmd_param[1][0] == '-')
	{
		ft_putstr_fd("unset: invalid option: ", 2);
		ft_putendl_fd(minishell->cmd->cmd_param[1], 2);
		return (2);
	}
	if (ft_strchr(minishell->cmd->cmd_param[1], '=') == 0)
		return (0);
	while (temp != minishell->env)
	{
		if (ft_strncmp(minishell->cmd->cmd_param[1], temp->str,
				(ft_strlen_c(minishell->cmd->cmd_param[1], '=') - 1) == 0))
			{
				temp->prev->next = temp->next;
				free(temp->str);
				// free(del);
				minishell->env = temp;
				return (0);
			}
		temp = temp->next;
	}
	return (0);
}
