/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:35:57 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/25 22:36:22 by inbennou         ###   ########.fr       */
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

// prends la struct en param pour tout free
void	exit_shell(int write_ex)
{
	if (write_ex)
		if (write(1, "exit\n", 5) < 0)
			perror("write error");
	// tout free
	// rl_clear_history
	exit(1); // exit avec le bon exit_code
}

void	pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd || pwd[0] == '\0')
		perror("Could not get current working directory");
	else
		printf("%s\n", pwd);
	free(pwd);
}

// exit_code doit etre une valeur de notre struct
// creer un ac dans notre struct
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
			// pipe
				// pipex
			// no pipe
				// only child
		free(line);
	}
	exit_shell(0);
}
