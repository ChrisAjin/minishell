/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:19:30 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/28 14:20:43 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_reder(int var)
{
	if (var == HEREDOC || var == TRUNC || var == INPUT || var == APPEND)
		return (1);
	return (0);
}

int check_reder_tkn(t_token *token) {
    if (!token) return 0;
    t_token *tmp = token;

    do {
        if (is_reder(tmp->type) && !tmp->next) {
            ft_putstr_fd("Minishell: syntax error near unexpected token 'newline'\n", 2);
            return 1;
        }
        if (is_reder(tmp->type) && tmp->next->type != ARG
            && (is_reder(tmp->next->type) || tmp->next->type == PIPE)) {
            ft_putstr_fd("Minishell: syntax error near unexpected token '", 2);
            ft_putstr_fd(tmp->next->str, 2);
            ft_putstr_fd("'\n", 2);
            return 1;
        }
        tmp = tmp->next;
    } while (tmp != token);

    return 0;
}


int check_pipe_tkn(t_token *token) {
    if (!token) return 0;

    t_token *ptr = token;

    do {
        if (ptr->type == PIPE) {
            if (!ptr->next || !ptr->prev) {
                ft_putstr_fd("Minishell: syntax error near unexpected token '|'\n", 2);
                return 1;
            } else if (ptr->next->type == PIPE) {
                ft_putstr_fd("Minishell: syntax error near unexpected token '||'\n", 2);
                return 1;
            }
        }
        ptr = ptr->next;
    } while (ptr != token);

    return 0;
}

int check_herdoc_tkn(t_token *token) {
    if (!token) return 0;

    int i = 0;
    t_token *ptr = token;

    do {
        if (ptr->type == HEREDOC)
            i++;
        ptr = ptr->next;
    } while (ptr != token);

    if (i > 16) {
        ft_putstr_fd("Minishell: maximum here-document count exceeded\n", 2);
        return 1;
    }

    return 0;
}


int	check_pipe_red_herdoc(t_data *data)
{
	if (check_herdoc_tkn(data->token))
		return (1);
	if (check_reder_tkn(data->token))
		return (1);
    if (data->token && data->token->prev->type == PIPE)
	{
		write(2, "Error: Unclosed pipe\n", 21);
		data->exit_code = 2;
		//free_token(&data->token);
		return (1);
	}
	if (check_pipe_tkn(data->token))
		return (1);
	return (0);
}
