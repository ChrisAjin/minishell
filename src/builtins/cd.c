/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 21:55:35 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/11 17:25:06 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// mene vers le chemin tab[1]
// si tab[1] == '~' || tab[1] == '\0' mene vers home
// implementer $HOME et $OLDPWD
// gerer le cas cd $HOME/Documents
// tester les cas - et . dans le bash
// - revient au precedent path (OLDPWD) et . ne fait rien
// quand on donne un chemin relatif, bash fouille dans la var d'env $CDPATH
// msg d'erreur si:
// le chemin n'existe pas
// permission denied
// cd $var qui n'existe pas

// tester cd dans un fichier supprime

int	cd(t_data *minishell)
{
	char	**env;
	char	*old_pwd;
	char	*cur_dir;

	env = list_to_arr(minishell->env);
	old_pwd = get_pwd();
	if (minishell->cmd->cmd_param[1] == NULL
		|| ft_strncmp(minishell->cmd->cmd_param[1], "~", 2) == 0)
	{
		if (ch_dir_home(env, old_pwd) < 0)
		{
			// free all
			return (1);
		}
	}
	else
	{
		if (chdir(minishell->cmd->cmd_param[1]) < 0)
		{
			perror("cd");
			if (old_pwd)
				free(old_pwd);
			// free all
			return (1);
		}
	}
	cur_dir = get_pwd();
	if (add_pwd(cur_dir, env) || add_old_pwd(old_pwd, env) < 0)
	{
		// free_all
		return (1);
	}
	// free all
	return (0);
}

int	ch_dir_home(char **env, char *old_pwd)
{
	char	*path;

	path = get_home(env);
	if (chdir(path) < 0)
	{
		perror("cd");
		if (old_pwd)
			free(old_pwd);
		return (1);
	}
	return (0);
}

char	*get_home(char **env)
{
	int		i;
	char	*home;

	i = 0;
	home = NULL;
	while (env && env[i])
	{
		if (ft_strncmp("HOME=", env[i], 5) == 0)
			home = ft_strdup(env[i] + 5);
		// proteger strdup
		i++;
	}
	if (home == NULL)
		ft_putendl_fd("HOME not set.", 2);
	return (home);
}

int	add_pwd(char *cur_dir, char **env)
{
	int	i;

	i = 0;
	if (cur_dir == NULL)
		return ;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("PWD=", cur_dir);
			if (env[i] == '\0')
			{
				ft_putstr_fd(ERR_MALLOC, 2);
				return (1);
			}
			return (0);
		}
		i++;
	}
	ft_putendl_fd("Could not set PWD", 2);
	free(cur_dir);
	return (0);
}

int	add_old_pwd(char *old_pwd, char **env)
{
	int	i;

	i = 0;
	if (old_pwd == NULL)
		return ;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", old_pwd);
			if (env[i] == '\0')
			{
				ft_putstr_fd(ERR_MALLOC, 2);
				return (1);
			}
			return (0);
		}
		i++;
	}
	ft_putendl_fd("Could not set OLDPWD", 2);
	free(old_pwd);
	return (0);
}
