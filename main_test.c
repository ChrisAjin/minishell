/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:35:57 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/26 16:18:37 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitest.h"

// echo avc l'option -n /
// cd /
// pwd /
// export
// unset
// env
// exit /

// idees redirections :
// init infile à 0 et outfile à 1
// outf_trunc et outf_append ?
// si il y a une redir on modif par fd inf et/ou fd outf

// proteger les writes avec perror (par ex: pwd > /dev/full)
// seuls cas  qui font quitter le shell : la commande "exit" et ctrl D (consdere comme EOF)
// Makefile: ajouter le flag -lreadline a la fin pcq c'est une lib

// comment gerer les free struct en fonction de qui exec la commande

// exit_code doit etre une valeur de notre struct
// creer un ac dans struct ou au debut de la fonction exec pour gerer les childs
	// avoir une fonction qui compte le nbr de commandes
int	main(int ac, char **av, char **envp)
{
	char	*line;
	(void)av;
	// (void)envp; // mettre dans la struct
	// init_struct

	if (ac != 1)
		exit(1);
	while (1)
	{
		line = readline("Minitest > ");
		// rl_history
		// if ctrl D
		// 	break ;
		// parsing
			// init struct->ac
		// exec
		exec_builtin(line, envp);
			// pipe (plusieurs cmds)
				// pipex
			// no pipe
				// only child
		free(line);
	}
	exit_shell(0);
}
