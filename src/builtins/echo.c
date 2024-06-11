/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:16:00 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/10 18:31:55 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// gerer echo $?
void	echo(t_data *minishell)
{
	int	n;
	int	i;

	n = 0;
	i = 2;
	if (minishell->cmd->cmd_param[1] == NULL)
	{
		printf("\n");
		// free all
		exit(0);
	}
	if (n_option(minishell->cmd->cmd_param[1]))
		n = 1;
	while (n_option(minishell->cmd->cmd_param[i]))
		i++;
	if (minishell->cmd->cmd_param[i] != NULL)
		print_args(minishell->cmd->cmd_param, i);
	if (n != 1)
		printf("\n");
	// free all
	exit(0);
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

void	print_args(char **tab, int index)
{
	int	y;

	y = index;
	while (tab[y + 1])
	{
		if (printf("%s ", tab[y]) < 0)
		{
			perror("printf");
			// free all
			exit(1);
		}
		y++;
	}
	if (printf("%s", tab[y]) < 0)
	{
		perror("printf");
		// free all
		exit(1);
	}
}
