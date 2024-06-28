/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:16:04 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/28 15:18:13 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	size_2_tab(t_data *minishell)
{
	if (only_digit(minishell->cmd->cmd_param[1]) == 2)
		clear_and_exit(minishell, 2,
			"minishell: exit: numeric argument required");
	minishell->exit_code = ft_atoi(minishell->cmd->cmd_param[1]);
	clear_and_exit(minishell, minishell->exit_code, NULL);
}

void	exit_shell_c(t_data *minishell)
{
	if (size_tab(minishell->cmd->cmd_param) == 1)
		clear_and_exit(minishell, 0, NULL);
	else
	{
		if (size_tab(minishell->cmd->cmd_param) == 2)
			size_2_tab(minishell);
		else if (size_tab(minishell->cmd->cmd_param) == 3)
		{
			if (only_digit(minishell->cmd->cmd_param[1])
				&& only_digit(minishell->cmd->cmd_param[2]) == 2)
				clear_and_exit(minishell, 1,
								"minishell: exit: too many argument"); //
			else
				clear_and_exit(minishell, 1,
					"minishell: exit: numeric argument required");
		}
		else if (size_tab(minishell->cmd->cmd_param) > 3)
			clear_and_exit(minishell, 127,
							"minishell: exit: too many argument"); //
	}
	clear_and_exit(minishell, 0, NULL);
}

int	exit_shell_p(t_data *minishell)
{
	if (size_tab(minishell->cmd->cmd_param) == 1)
		clear_and_exit(minishell, 0, NULL);
	else
	{
		if (size_tab(minishell->cmd->cmd_param) == 2)
			size_2_tab(minishell);
		else if (size_tab(minishell->cmd->cmd_param) == 3)
		{
			if (only_digit(minishell->cmd->cmd_param[1])
				&& only_digit(minishell->cmd->cmd_param[2]) == 2)
				return(clear_no_exit(minishell, "minishell: exit: too many argument"));
			else
				clear_and_exit(minishell, 1,
					"minishell: exit: numeric argument required");
		}
		else if (size_tab(minishell->cmd->cmd_param) > 3)
			return (clear_no_exit(minishell, "minishell: exit: too many argument"));
	}
	clear_and_exit(minishell, 0, NULL);
	return (0);
}

int	clear_no_exit(t_data *minishell, char *msg)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	if (minishell->pipes == 0)
		if (write(1, "exit\n", 5) < 0)
			perror("write error");
	rl_clear_history();
	free_all(minishell, NULL, -1);
	return (0);
}

int	clear_and_exit(t_data *minishell, int exit_c, char *msg)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	if (minishell->pipes == 0)
		if (write(1, "exit\n", 5) < 0)
			perror("write error");
	rl_clear_history();
	free_all(minishell, NULL, -1);
	exit(exit_c);
	return (0);
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
