/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:19:18 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/28 15:40:25 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_shell(t_data *minishell)
{
	if (minishell->pid != 0)
		if (write(1, "exit\n", 5) < 0)
			perror("write error");
	if (only_digit(minishell->cmd->cmd_param[1]))
		minishell->exit_code = ft_atoi(minishell->cmd->cmd_param[1]);
	else if (minishell->cmd->cmd_param[1] != NULL)
		minishell->exit_code = 2;
	else
		minishell->exit_code = 0;
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