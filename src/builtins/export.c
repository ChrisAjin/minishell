/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:07:53 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/19 13:52:20 by inbennou         ###   ########.fr       */
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
		if (ft_isdigit(minishell->cmd->cmd_param[1][0])
			|| ft_strchr(minishell->cmd->cmd_param[1], '=') == 0
			|| has_space(minishell->cmd->cmd_param[1]))
			not_valid(minishell);
		if (is_var(cmd, minishell->env))
			change_var(cmd, minishell->env);
		else
			append_list(&minishell->env, minishell->cmd->cmd_param[1]);
	}
	return (0);
}

int	has_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_space(str[i]) == true)
			return (1);
		i++;
	}
	return (0);
}

int	not_valid(t_data *minishell)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(minishell->cmd->cmd_param[1], 2);
	ft_putendl_fd(": not a valid identifier", 2);
	return (1);
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
