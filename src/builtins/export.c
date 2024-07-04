/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:07:53 by inbennou          #+#    #+#             */
/*   Updated: 2024/07/04 15:21:57 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	export(t_data *minishell)
{
	int	i;

	i = 0;
	if (minishell->cmd->cmd_param[1] == NULL)
		return (export_print_lst(minishell->env));
	if (minishell->cmd->cmd_param[1][0] == '-')
		return (export_inv_opt(minishell->cmd->cmd_param[1]));
	else
	{
		while (minishell->cmd->cmd_param[++i])
		{
			if (!is_export_valid(minishell->cmd->cmd_param[i])
				|| ft_strchr(minishell->cmd->cmd_param[i], '=') == 0
				|| has_space(minishell->cmd->cmd_param[i]))
				not_valid(minishell, i);
			else
			{
				if (is_var(minishell->cmd->cmd_param[i], minishell->env))
					change_var(minishell->cmd->cmd_param[i], minishell->env);
				else
					append_list(&minishell->env, minishell->cmd->cmd_param[i]);
			}
		}
	}
	return (0);
}

int	change_var(char *str, t_list *env)
{
	t_list	*temp;

	temp = env->next;
	while (temp != env)
	{
		if (ft_strncmp(temp->str, str, ft_strlen_c(str, '=')) == 0)
		{
			free(temp->str);
			temp->str = ft_strdup(str);
			env = temp;
			return (0);
		}
		temp = temp->next;
	}
	env = temp;
	return (1);
}

int	is_var(char *str, t_list *env)
{
	t_list	*temp;

	temp = env->next;
	while (temp != env)
	{
		if (ft_strncmp(temp->str, str, ft_strlen_c(str, '=')) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	export_print_lst(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (1);
	temp = lst;
	if (printf("declare -x %s\n", temp->str) < 0)
	{
		perror("printf");
		return (1);
	}
	temp = temp->next;
	while (temp != lst)
	{
		if (printf("declare -x %s\n", temp->str) < 0)
		{
			perror("printf");
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}
