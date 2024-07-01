/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:55:07 by inbennou          #+#    #+#             */
/*   Updated: 2024/07/01 15:55:29 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_export_valid(char *str)
{
	if (ft_isalpha(str[0]) || str[0] == '_')
		return (1);
	return (0);
}

int	not_valid(t_data *minishell)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(minishell->cmd->cmd_param[1], 2);
	ft_putendl_fd(": not a valid identifier", 2);
	return (1);
}
