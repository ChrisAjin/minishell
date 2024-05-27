/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:01:42 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/27 14:47:39 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// fonction qui compte le nbr de commande
// fonction pour fork (dans une boucle?)
// lancer child qui correspond juste apres
// si redir modifier infile et outfile (dans first et last child ?)

// open infile et outfile dans childs ou parent?

// here_doc ?

int	exec(t_data *minishell)
{
	int	ac;
	int	pid;

	// ac = cmd_count(minishell);
	// if here_doc
		// exec_here_doc
			// ouvrir un fichier temp ou ecrire dans le pipe
	// fonction qui check s'il y a des redir et qui open les files
		// si redir sur outfile choisir entre trunc et append et check les droits
	pid = ft_fork();
	if (ac == 1)
		// only child
	while (ac > 0)
	{
		
	}
	// close all
}

int	ft_fork()
{
	int	pid;

	pid = fork();
	if (pid < 0)
		// close and error
	return (pid);
}
