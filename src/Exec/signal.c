/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:03:01 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/14 19:05:31 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_signal_ctrl_c(int sig, t_data *ptr)
{
	static t_data	*context;

	if (sig == -200)
		context = ptr;
	if (waitpid(-1, NULL, WNOHANG) == 0)
	{
		printf("\n");
		return ;
	}
	if (sig == SIGINT)
	{
		g_ext_status = 1;
		if (!context->sigflg)
        {
            //rl_replace_line("", 0);   // Efface la ligne courante dans readline
			//rl_on_new_line();         // Informe readline qu'une nouvelle ligne commence
			//rl_redisplay();
            ft_putstr_fd("\n", 1);
        }
			
		
	}
}

void	handle_signal_in_out(t_data *data)
{
	dup2(data->f_stdin, 0);
	dup2(data->f_stdout, 1);
	data->sig = 0;
	handle_signal_ctrl_c(-200, data);
	signal(SIGQUIT, (void (*)(int))handle_signal_ctrl_c);
	signal(SIGINT, (void (*)(int))handle_signal_ctrl_c);
}