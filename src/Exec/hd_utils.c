/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:52:31 by cassassa          #+#    #+#             */
/*   Updated: 2024/07/01 18:18:23 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	signal_here_doc(void)
{
	signal(SIGINT, &sig_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	print_error_hd(char *word)
{
	print_error("warning: here-document delimited by end-of-file ");
	print_error("(wanted '");
	print_error(word);
	print_error("')\n");
}
