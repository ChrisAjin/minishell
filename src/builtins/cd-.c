/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd-.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:18:58 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/20 18:28:57 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_args(char	**cmd_param);
char	*get_old_pwd(t_data *minishell);
int	size_tab(char **cmd_param);

int	cd(t_data *minishell)
{
	char	*old_pwd;
	char	*cur_dir;

	if (check_args(minishell->cmd->cmd_param))
		return (1);
	old_pwd = get_pwd();
	if (!old_pwd)
	{
		if (get_old_pwd(minishell) == NULL)
		{
			ft_putendl_fd("minishell: cd: error retrieving current directory", 2);
			return (1);
		}
	}
	if (minishell->cmd->cmd_param[1] == NULL 
		|| ft_strncmp(minishell->cmd->cmd_param[1], "~", 2) == 0)
	{
		if (ch_dir_home(minishell->env, old_pwd) < 0)
		{
			ft_free(old_pwd);
			return (1);
		}
	}
	else
	{
		printf("ici");
		if (chdir(minishell->cmd->cmd_param[1]) < 0)
		{
			
			perror(minishell->cmd->cmd_param[1]);
			ft_free(old_pwd);
			return (1);
		}
	}
	cur_dir = get_pwd();
	add_pwd(cur_dir, minishell);
	add_old_pwd(old_pwd, minishell);
	// dprintf(2, "%s\n", old_pwd);
	// ft_free(old_pwd);
	return (0);
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

char	*get_old_pwd(t_data *minishell)
{
	t_list	*temp;
	char	*pwd;

	temp = minishell->env;
	while (minishell->env->next != temp)
	{
		if (ft_strncmp("PWD=", minishell->env->str, 4) == 0)
		{
			pwd = ft_strdup(minishell->env->str + 4);
			if (!pwd)
			{
				ft_putstr_fd(ERR_MALLOC, 2);
				return (NULL);
			}
		}
		minishell->env = minishell->env->next;
	}
	return (pwd);
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
		ft_putendl_fd("HOME not set.", 2); // retirer ?
	return (home);
}

int	size_tab(char **cmd_param)
{
	int	i;

	i = 0;
	while (cmd_param[i])
		i++;
	return (i);
}

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
		}
		minishell->env = minishell->env->next;
	}
	return (0);
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
		}
		minishell->env = minishell->env->next;
	}
	return (0);
}
