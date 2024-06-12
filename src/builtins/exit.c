/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:16:04 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/12 13:04:58 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_data *minishell)
{
	if (minishell->pipes == 0)
		if (write(1, "exit\n", 5) < 0)
			perror("write error");
	free_all(minishell, NULL, -1);
	// rl_clear_history
	if (only_digit(minishell->cmd->cmd_param[1]))
		minishell->exit_code = ft_atoi(minishell->cmd->cmd_param[1]);
	else if (minishell->cmd->cmd_param[1] != NULL)
		minishell->exit_code = 2;
	else
		minishell->exit_code = 0;
	exit(minishell->exit_code);
}

int	only_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (isdigit(str[i]) != 1)
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			return (0);
		}
		i++;
	}
	if (ft_strlen(str) != 1)
		return (1);
	return (0);
}
