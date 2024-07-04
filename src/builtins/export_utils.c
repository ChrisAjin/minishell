/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:55:07 by inbennou          #+#    #+#             */
/*   Updated: 2024/07/04 15:20:01 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_export_valid(char *str)
{
	if (ft_isalpha(str[0]) || str[0] == '_')
		return (1);
	return (0);
}

int	not_valid(t_data *minishell, int i)
{
	if (i < 2)
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(minishell->cmd->cmd_param[i], 2);
		ft_putendl_fd(": not a valid identifier", 2);
	}
	return (1);
}

int	export_inv_opt(char *cmd_param)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(cmd_param, 2);
	ft_putendl_fd(": invalid option", 2);
	return (2);
}
