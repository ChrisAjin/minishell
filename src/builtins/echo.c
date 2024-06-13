/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:16:00 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/13 19:55:36 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// ca marche plus :(
// gerer echo $?
int	echo(t_data *minishell)
{
	int	n;
	int	i;

	n = 0;
	i = 1;
	if (!minishell->cmd->cmd_param[1] || minishell->cmd->cmd_param[1] == NULL)
	{
		printf("\n");
		// free_all(minishell, NULL, -1);
		return (0);
	}
	if (ft_strncmp(minishell->cmd->cmd_param[1], "$?", 3) == 0)
	{
		printf("%d\n", minishell->exit_code);
		return (0);
	}
	if (n_option(minishell->cmd->cmd_param[1]))
	{
		n = 1;
		i = 2;
	}
	while (n_option(minishell->cmd->cmd_param[i]))
		i++;
	if (minishell->cmd->cmd_param[i] != NULL)
	{
		dprintf(2, "oui\n");
		if (print_args(minishell, i) < 0)
			minishell->exit_code = 1;
	}
	if (n != 1)
		printf("\n");
	// free_all(minishell, NULL, -1);
	return (0);
}

int	n_option(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0' || ft_strlen(str) < 2)
		return (0);
	if (str[i] == '-')
	{
		i++;
		while (str && str[i] == 'n')
			i++;
	}
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}

int	print_args(t_data *minishell, int index)
{
	int	y;

	y = index;
	while (minishell->cmd->cmd_param[y + 1])
	{
		if (printf("%s ", minishell->cmd->cmd_param[y]) < 0)
		{
			perror("printf");
			// free_all(minishell, NULL, -1);
			return (1);
		}
		y++;
	}
	if (printf("%s", minishell->cmd->cmd_param[y]) < 0)
	{
		perror("printf");
		// free_all(minishell, NULL, -1);
		return (1);
	}
	return (0);
}
