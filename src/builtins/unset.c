/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:45:34 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/27 15:21:33 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unset(t_data *minishell)
{
	t_list	*temp;
	int		is_var;

	temp = minishell->env->next;
	is_var = 0;
	if (minishell->cmd->cmd_param[1][0] == '-')
	{
		ft_putstr_fd("unset: invalid option: ", 2);
		ft_putendl_fd(minishell->cmd->cmd_param[1], 2);
		return (2);
	}
	if (ft_is_there(minishell->cmd->cmd_param[1], '='))
		return (0);
	while (temp != minishell->env)
	{
		if (ft_is_there(temp->str, '='))
			is_var = ft_strncmp(temp->str, minishell->cmd->cmd_param[1],
					ft_strlen_c(temp->str, '='));
		if (is_var == 0)
			return (unset_var(minishell, temp));
		temp = temp->next;
	}
	return (0);
}

int	unset_var(t_data *minishell, t_list *temp)
{
	if (ft_is_there(temp->str, '=') == 0)
		return (0);
	if (temp == minishell->env)
		minishell->env = temp->next;
	if (temp->prev)
		temp->prev->next = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	free(temp->str);
	free(temp);
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
