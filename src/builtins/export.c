/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:07:53 by inbennou          #+#    #+#             */
/*   Updated: 2024/07/01 17:34:29 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	export(t_data *minishell)
{
	char	*cmd;

	cmd = minishell->cmd->cmd_param[1];
	if (minishell->cmd->cmd_param[1] == NULL)
		return (export_print_lst(minishell->env));
	if (minishell->cmd->cmd_param[1][0] == '-')
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(minishell->cmd->cmd_param[1], 2);
		ft_putendl_fd(": invalid option", 2);
		return (2);
	}
	else
	{
		if (!is_export_valid(minishell->cmd->cmd_param[1])
			|| ft_strchr(minishell->cmd->cmd_param[1], '=') == 0
			|| has_space(minishell->cmd->cmd_param[1]))
			return (not_valid(minishell), 1);
		if (is_var(cmd, minishell->env))
			change_var(cmd, minishell->env);
		else
			add_root_list(&minishell->env, minishell->cmd->cmd_param[1]);
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
