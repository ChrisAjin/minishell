/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 21:55:35 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/27 15:54:48 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd(t_data *minishell)
{
	char	*old_pwd;

	if (check_args(minishell->cmd->cmd_param))
		return (1);
	old_pwd = get_pwd();
	if (minishell->cmd->cmd_param[1] == NULL
		|| ft_strncmp(minishell->cmd->cmd_param[1], "~", 2) == 0)
	{
		if (ch_dir_home(minishell->env, old_pwd) < 0)
		{
			free(old_pwd);
			return (1);
		}
	}
	else
	{
		if (chdir(minishell->cmd->cmd_param[1]))
		{
			perror(minishell->cmd->cmd_param[1]);
			free(old_pwd);
			return (1);
		}
	}
	return (update_pwd_old(minishell, old_pwd));
}

int	update_pwd_old(t_data *minishell, char *old_pwd)
{
	char	*cur_dir;

	cur_dir = get_pwd();
	add_pwd(cur_dir, minishell);
	add_old_pwd(old_pwd, minishell);
	free(old_pwd);
	free(cur_dir);
	return (0);
}

int	ch_dir_home(t_list *env, char *old_pwd)
{
	char	*path;

	path = get_home(env);
	if (chdir(path) < 0)
	{
		perror("cd");
		if (old_pwd)
			free(old_pwd);
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

char	*get_home(t_list *env)
{
	char	*home;
	t_list	*temp;

	home = NULL;
	temp = env;
	while (temp->next != env)
	{
		if (ft_strncmp("HOME=", temp->str, 5) == 0)
		{
			home = ft_strdup(temp->str + 5);
			if (!home)
				ft_putstr_fd(ERR_MALLOC, 2);
		}
		temp = temp->next;
	}
	if (home == NULL)
		ft_putendl_fd("HOME not set.", 2);
	return (home);
}
