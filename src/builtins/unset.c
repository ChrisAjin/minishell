/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:45:34 by inbennou          #+#    #+#             */
/*   Updated: 2024/07/04 15:59:58 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unset(t_data *minishell)
{
	t_list	*temp;
	int		i;

	i = 0;
	if (minishell->cmd->cmd_param[1][0] == '-')
		return (unset_inv_opt(minishell->cmd->cmd_param[1]));
	while (minishell->cmd->cmd_param[++i])
	{
		if (!ft_is_there(minishell->cmd->cmd_param[i], '='))
		{
			temp = minishell->env->next;
			while (temp != minishell->env)
			{
				if (unset_valid(minishell->cmd->cmd_param[i], temp->str))
				{
					unset_var(minishell, &temp);
					break ;
				}
				temp = temp->next;
			}
		}
	}
	return (0);
}

int	unset_valid(char *cmd_param, char *temp_str)
{
	if (ft_is_there(temp_str, '=') && ft_strncmp(temp_str, cmd_param,
			ft_strlen_c(temp_str, '=')) == 0)
		return (1);
	return (0);
}

int	unset_var(t_data *minishell, t_list **temp)
{
	if (ft_is_there((*temp)->str, '=') == 0)
		return (0);
	if (*temp == minishell->env)
		minishell->env = (*temp)->next;
	(*temp)->prev->next = (*temp)->next;
	(*temp)->next->prev = (*temp)->prev;
	free((*temp)->str);
	free(*temp);
	return (0);
}

int	ft_is_there(const char *str, char c)
{
	int	n;

	n = 0;
	while (str[n])
		n++;
	while ((str[n] != c) && (n > 0))
		n--;
	if (str[n] == c)
		return (1);
	else
		return (0);
}

int	unset_inv_opt(char *cmd_param)
{
	ft_putstr_fd("unset: invalid option: ", 2);
	ft_putendl_fd(cmd_param, 2);
	return (2);
}
