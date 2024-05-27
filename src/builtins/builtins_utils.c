/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:31:03 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/27 17:37:21 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitest.h"

// !!! tous les builtins doivent exit pour kill les childs !!!
// lstadd back et lst delone pour export et unset
// adapter env pour une liste chainee pas **tab

// prends en param la struct pour pouvoir tout free
int	exec_builtin(char *line, char **envp)
{
	char	**tab;

	tab = NULL;
	if (!line || line[0] == '\0')
		return (0);
	tab = ft_split(line, ' ');
	if (ft_strncmp(tab[0], "echo", 5) == 0)
		echo(tab);
	if (ft_strncmp(tab[0], "cd", 3) == 0)
		cd(tab, envp);
	if (ft_strncmp(tab[0], "pwd", 4) == 0)
		pwd();
	// if (ft_strncmp(tab[0], "export", 7) == 0)
	// 	export(tab);
	// if (ft_strncmp(tab[0], "unset", 6) == 0)
	// 	unset(tab);
	if (ft_strncmp(tab[0], "env", 4) == 0)
		env_cmd(tab, envp);
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
		perror("Could not get current directory");
	return (path);
}
