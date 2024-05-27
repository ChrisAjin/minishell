/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:01:42 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/27 20:46:20 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// fonction qui compte le nbr de commande
// open dans les childs pcq chacun peut avoir ses redir

// avant la fonction exec il faut init inf et outf sur stdin et stdout ou sur -1

// gerer le cas ou on a juste un pipe a la fin ? :(

int	exec(t_data *minishell)
{
	int	ac;

	// ac = cmd_count(minishell);
	// fonction qui check s'il y a des redir et qui open les files
		// si redir sur outfile choisir entre trunc et append et check les droits
	// if (ac == 0) ou commande vide
		// init exit_code et return
	if (ac == 1)
		return (one_cmd(minishell));
	else if (ac > 1)
	{
		// while (ac > 1)
			// exec middle children
	}
	// exec last child
	// close all
	// wait and error(pid only child ou last child);
}

int	one_cmd(t_data *minishell)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		// fork error
	if (pid == 0)
		// only child
	// init exit code
	return (0);
}
