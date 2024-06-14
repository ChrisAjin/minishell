/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 21:55:35 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/14 17:47:29 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// implementer $HOME et $OLDPWD
// gerer le cas cd $HOME/Documents
// quand on donne un chemin relatif, bash fouille dans la var d'env $CDPATH
// msg d'erreur si:
// le chemin n'existe pas
// permission denied
// cd $var qui n'existe pas

// tester cd dans un fichier supprime :((((((((((

// pour la norme retirer char **env et adapter a une liste chainee
int	cd(t_data *minishell)
{
	char	*old_pwd;
	char	*cur_dir;

	if (size_tab(minishell->cmd->cmd_param) > 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	old_pwd = get_pwd();
	if (!old_pwd)
	{
		ft_putendl_fd("cd: error retrieving current directory", 2);
		return (1);
	}
	if (minishell->cmd->cmd_param[1] == NULL
		|| ft_strncmp(minishell->cmd->cmd_param[1], "~", 2) == 0)
	{
		if (ch_dir_home(minishell->env, old_pwd) < 0)
			return (1);
	}
	else
	{
		if (chdir(minishell->cmd->cmd_param[1]) < 0)
		{
			perror(minishell->cmd->cmd_param[1]);
			if (old_pwd)
				free(old_pwd);
			return (1);
		}
	}
	cur_dir = get_pwd();
	if (add_pwd(cur_dir, minishell) > 0 || add_old_pwd(old_pwd, minishell) > 0)
		return (1);
	return (0);
}

int	add_old_pwd(char *old_pwd, t_data *minishell)
{
	t_list	*temp;

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
	ft_putendl_fd("Could not set OLDPWD.", 2);
	return (1);
}

int	add_pwd(char *cur_dir, t_data *minishell)
{
	t_list	*temp;

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
	ft_putendl_fd("Could not set PWD.", 2);
	return (1);
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

int	size_tab(char **cmd_param)
{
	int	i;

	i = 0;
	while (cmd_param[i])
		i++;
	return (i);
}
