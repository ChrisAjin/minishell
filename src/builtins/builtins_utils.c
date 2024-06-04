/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:31:03 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/04 19:09:59 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// !!! tous les builtins doivent exit pour kill les childs !!!
// adapter env pour une liste chainee pas **tab

// export: regles a respecter dans les noms, voir cas s'il existe deja (ecrase l'ancien?)

// unset : echo oui | unset PATH | ls n'a pas unset PATH...

// prends en param la struct pour pouvoir tout free
int	exec_builtin(t_data *minishell, char *cmd)
{
	char	**tab;

	tab = NULL;
	if (!cmd || cmd[0] == '\0')
		return (0);
	tab = ft_split(cmd, ' ');
	if (ft_strncmp(tab[0], "echo", 5) == 0)
		echo(tab);
	if (ft_strncmp(tab[0], "cd", 3) == 0)
		cd(tab, minishell->env);
	if (ft_strncmp(tab[0], "pwd", 4) == 0)
		pwd();
	// if (ft_strncmp(tab[0], "export", 7) == 0)
	// 	export(tab);
	// if (ft_strncmp(tab[0], "unset", 6) == 0)
	// 	unset(tab);
	if (ft_strncmp(tab[0], "env", 4) == 0)
		env_cmd(tab, minishell->env);
	if (ft_strncmp(tab[0], "exit", 5) == 0)
		exit_shell(1);
	return (0);
}

char	*get_pwd()
{
	char	*path;

	path = NULL;
	path = getcwd(NULL, 0);
	if (!path || path[0] == '\0')
		return (NULL);
	return (path);
}
