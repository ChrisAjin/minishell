/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:44:38 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/04 19:10:50 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(char *name)
{
	int	fd_in;

	fd_in = open(name, O_RDWR, 0777);
	if (fd_in < 0)
		perror(name);
	return (fd_in);
}

int	open_outfile_append(char *name)
{
	int	fd_out;

	fd_out = open(name, O_RDWR | O_APPEND | O_CREAT, 0777);
	if (fd_out < 0)
		perror(name);
	return (fd_out);
}

int	open_outfile_trunc(char *name)
{
	int	fd_out;

	fd_out = open(name, O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (fd_out < 0)
		perror(name);
	return (fd_out);
}
