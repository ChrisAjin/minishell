/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:19:18 by inbennou          #+#    #+#             */
/*   Updated: 2024/07/04 14:37:30 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_shell(t_data *minishell)
{
	int	size;

	size = size_tab(minishell->cmd->cmd_param);
	if (size > 3)
	{
		too_many_args(minishell);
		if (minishell->pid != 0)
			return ;
	}
	else if (size == 1)
		minishell->exit_code = 0;
	else if (size == 2)
		size_2(minishell);
	else if (size == 3)
	{
		if (only_digit(minishell->cmd->cmd_param[1]))
		{
			too_many_args(minishell);
			if (minishell->pid != 0)
				return ;
		}
		else
			minishell->exit_code = 2;
	}
	clear_and_exit(minishell);
}

void	too_many_args(t_data *minishell)
{
	ft_putendl_fd("minishell: exit: too many argments", 2);
	minishell->exit_code = 1;
}

void	size_2(t_data *minishell)
{
	if (only_digit(minishell->cmd->cmd_param[1]))
		minishell->exit_code = ft_atoi(minishell->cmd->cmd_param[1]);
	else
		minishell->exit_code = 2;
}

void	clear_and_exit(t_data *minishell)
{
	if (minishell->pid != 0)
		if (write(1, "exit\n", 5) < 0)
			perror("write error");
	rl_clear_history();
	free_all(minishell, NULL, -1);
	exit(minishell->exit_code);
}

int	only_digit(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (ft_strlen(str) > 11)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1)
		{
			ft_putendl_fd("minishell: exit: numeric argument required", 2);
			return (0);
		}
		i++;
	}
	return (1);
}
