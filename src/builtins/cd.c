/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 21:55:35 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/04 19:10:10 by inbennou         ###   ########.fr       */
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

int	cd(char **tab, char **envp)
{
	char	*old_pwd;
	char	*cur_dir;

	old_pwd = get_pwd();
	if (tab[1] == NULL || ft_strncmp(tab[1], "~", 2) == 0)
		ch_dir_home(envp, old_pwd);
	else
	{
		if (chdir(tab[1]) < 0)
		{
			perror("cd");
			if (old_pwd)
				free(old_pwd);
			exit(1);
		}
	}
	cur_dir = get_pwd();
	add_pwd(cur_dir, envp);
	add_old_pwd(old_pwd, envp);
	exit(0);
}

int	ch_dir_home(char **envp, char *old_pwd)
{
	char	*path;
	// char	**envp; // celui de la struct

	path = get_home(envp);
	if (chdir(path) < 0)
	{
		perror("cd");
		if (old_pwd)
			free(old_pwd);
		exit(1);
	}
	return (0);
}

char	*get_home(char **envp)
{
	int	i;
	char	*home;

	i = 0;
	home = NULL;
	while (envp[i])
	{
		if (ft_strncmp("HOME=", envp[i], 5) == 0)
			home = ft_strdup(envp[i] + 5);
			// proteger strdup
		i++;
	}
	// if (env[i] == '\0')
		// ft_putendl_fd("Could find HOME", 2);
	return (home);
}

void	add_pwd(char *cur_dir, char **env)
{
	// char	**env; // celui de la struct
	int	i;

	i = 0;
	if (cur_dir == NULL)
		return ;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			env[i] = ft_strjoin("PWD=", cur_dir);
			// proteger strjoin
			return ;
		}
		i++;
	}
	// if (env[i] == '\0')
		// ft_putendl_fd("Could not add PWD", 2);
	free(cur_dir);
}

void	add_old_pwd(char *old_pwd, char **env)
{
	// char	**env; // celui de la struct
	int	i;

	i = 0;
	if (old_pwd == NULL)
		return ;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			env[i] = ft_strjoin("OLDPWD=", old_pwd);
			// proteger strjoin
			return ;
		}
		i++;
	}
	// if (env[i] == '\0')
		// ft_putendl_fd("Could not add OLDPWD", 2);
	free(old_pwd);
}
