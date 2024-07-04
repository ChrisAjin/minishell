/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:52:31 by cassassa          #+#    #+#             */
/*   Updated: 2024/07/04 16:14:36 by cassassa         ###   ########.fr       */
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

static void	interactive_handler(int sig)
{
	g_signal_pid = 130;
	(void)sig;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	init_sig(void)
{
	struct sigaction	act;

	signal(SIGQUIT, SIG_IGN);
	ft_bzero(&act, sizeof(act));
	act.sa_handler = interactive_handler;
	sigaction(SIGINT, &act, NULL);
}

void	react_sig(t_data *data)
{
	data->exit_code = 130;
	g_signal_pid = 0;
}
