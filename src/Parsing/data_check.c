/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:19:30 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/28 14:30:13 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_reder(int var)
{
	if (var == HEREDOC || var == TRUNC || var == INPUT || var == APPEND)
		return (1);
	return (0);
}

int	check_reder_tkn(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (1)
	{
		if (is_reder(tmp->type) && !tmp->next)
		{
			ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
			return (1);
		}
		if (is_reder(tmp->type) && tmp->next->type != ARG
			&& (is_reder(tmp->next->type) || tmp->next->type == PIPE))
		{
			ft_putstr_fd("syntax error near unexpected token '", 2);
			ft_putstr_fd(tmp->next->str, 2);
			ft_putstr_fd("'\n", 2);
			return (1);
		}
		tmp = tmp->next;
		if (tmp == token)
			break ;
	}
	return (0);
}

int	check_pipe_tkn(t_token *token)
{
	t_token	*ptr;

	ptr = token;
	while (1)
	{
		if (ptr->type == PIPE)
		{
			if (!ptr->next || !ptr->prev || strcmp(ptr->prev->str,
					"new_root") == 0)
			{
				ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
				return (1);
			}
			else if (ptr->next->type == PIPE)
			{
				ft_putstr_fd("syntax error near unexpected token '||'\n", 2);
				return (1);
			}
		}
		ptr = ptr->next;
		if (ptr == token)
			break ;
	}
	return (0);
}

int	check_herdoc_tkn(t_token *token)
{
	int		i;
	t_token	*ptr;

	i = 0;
	ptr = token;
	while (1)
	{
		if (ptr->type == HEREDOC)
			i++;
		ptr = ptr->next;
		if (ptr == token)
			break ;
	}
	if (i > 16)
	{
		ft_putstr_fd("maximum here-document count exceeded\n", 2);
		return (1);
	}
	return (0);
}

int	check_pipe_red_herdoc(t_data *data)
{
	if (!data->token)
		return (0);
	if (check_herdoc_tkn(data->token))
		return (1);
	if (check_reder_tkn(data->token))
		return (1);
	if (data->token && data->token->prev->type == PIPE)
	{
		write(2, "Error: Unclosed pipe\n", 21);
		data->exit_code = 2;
		return (1);
	}
	if (check_pipe_tkn(data->token))
		return (1);
	return (0);
}
