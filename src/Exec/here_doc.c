/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:20 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/29 14:37:14 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitest.h"

// recuperer tout dans une str avec un join qui free la str au debut
// mettre la str dans la struct token
// putstr fd la str directement dans le pipe si strlen < 65000
// (avec un putstr fd qui ecrit char par char?)

// ajouter un define pour LIM?
// pour only child (pas pareil pour les pipes)
void	exec_here_doc(t_data *minishell)
{
	// if redir
		// open (inf et outf trunc ou append)
		// dup2 outf stdout
	// if il y a une cmd (peut etre avant ou apres <<)
		// if (pipe(pip) < 0)
			// pipe error
		// fill here doc qui ecrit dans le pipe
		// dup2 stdin pip[0]
		// exec cmd
	// else
		// gnl(0) jusqu'a LIM
	// close all
}

void	fill_here_doc(t_data *minishell, char *limiter)
{
	char	*line;
	char	*temp_line;

	temp_line = NULL;
	line = NULL;
	while (1)
	{
		ft_putstr_fd("> ", 2);
		line = get_next_line(0, 0);
		if (line == NULL)
			break ;
		temp_line = ft_strtrim(line, "\n");
		if (ft_strncmp(temp_line, limiter, ft_strlen(limiter) + 1) == 0)
			break ;
		ft_putstr_fd(line, minishell->pip[1]);
		free(line);
		line = NULL;
		free(temp_line);
		temp_line = NULL;
	}
	free(line);
	free(temp_line);
	get_next_line(0, 1);
}
