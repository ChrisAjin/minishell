/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:16:04 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/27 16:05:41 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	err_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (1);
}

int	exit_shell(t_data *minishell)
{
	if (size_tab(minishell->cmd->cmd_param) == 1)
		minishell->exit_code = 0;
	else
	{
		if (size_tab(minishell->cmd->cmd_param) > 3)
			return (err_msg("minishell: exit: too many argument"));
		else if (size_tab(minishell->cmd->cmd_param) == 2)
		{
			minishell->exit_code = ft_atoi(minishell->cmd->cmd_param[1]);
			if (only_digit(minishell->cmd->cmd_param[1]) == 2)
				return (err_msg("minishell: exit: numeric argument required"));
		}
		else if (size_tab(minishell->cmd->cmd_param) == 3)
		{
			if (only_digit(minishell->cmd->cmd_param[1])
				&& only_digit(minishell->cmd->cmd_param[2]) == 2)
				return (err_msg("minishell: exit: too many argument"));
			else
			{
				ft_putendl_fd("minishell: exit: numeric argument required", 2);
				minishell->exit_code = 2;
			}
		}
	}
	return (clear_and_exit(minishell));
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
			return (2);
		i++;
	}
	return (1);
}

int	clear_and_exit(t_data *minishell)
{
	if (minishell->pipes == 0)
		if (write(1, "exit\n", 5) < 0)
			perror("write error");
	rl_clear_history();
	free_all(minishell, NULL, -1);
	exit(minishell->exit_code);
	return (0);
}
