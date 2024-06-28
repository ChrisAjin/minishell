/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:50:22 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/27 15:51:43 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_old_pwd(char *old_pwd, t_data *minishell)
{
	t_list	*temp;

	if (!old_pwd)
		return (1);
	temp = minishell->env;
	while (minishell->env->next != temp)
	{
		if (ft_strncmp("OLDPWD=", minishell->env->str, 7) == 0)
		{
			free(minishell->env->str);
			minishell->env->str = ft_strjoin("OLDPWD=", old_pwd);
			if (minishell->env->str == NULL)
			{
				ft_putstr_fd(ERR_MALLOC, 2);
				return (1);
			}
			return (0);
		}
		minishell->env = minishell->env->next;
	}
	return (1);
}

int	add_pwd(char *cur_dir, t_data *minishell)
{
	t_list	*temp;

	if (!cur_dir)
		return (1);
	temp = minishell->env;
	while (minishell->env->next != temp)
	{
		if (ft_strncmp("PWD=", minishell->env->str, 4) == 0)
		{
			free(minishell->env->str);
			minishell->env->str = ft_strjoin("PWD=", cur_dir);
			if (minishell->env->str == NULL)
			{
				ft_putstr_fd(ERR_MALLOC, 2);
				return (1);
			}
			return (0);
		}
		minishell->env = minishell->env->next;
	}
	return (1);
}

int	size_tab(char **cmd_param)
{
	int	i;

	i = 0;
	while (cmd_param[i])
		i++;
	return (i);
}

int	check_args(char	**cmd_param)
{
	if (size_tab(cmd_param) > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	return (0);
}
