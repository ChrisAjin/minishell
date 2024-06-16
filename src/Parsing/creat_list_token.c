/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:04:27 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/14 15:49:50 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	length_cmd(char *command, int *quotes)
{
	int	i;

	i = 0;
	*quotes = 0;
	while (command[i] && !is_space(command[i]) && !is_special(command + i))
	{
		if (command[i] == '"' || command[i] == '\'')
		{
			(*quotes)++;
			if (command[i++] == '"')
				while (command[i] && command[i] != '"')
					++i;
			else
				while (command[i] && command[i] != '\'')
					++i;
			if (command[i])
				++i;
		}
		if (command[i] && command[i] != '"' && command[i] != '\'' && \
			!is_space(command[i]) && !is_special(command + i))
			++i;
	}
	return (i);
}

static void	copy_token(char *command, int length, char *str, int i)
{
	int	j;

	j = 0;
	while (command[i + j] && i < length)
	{
		if (command[i + j] == '\'' && ++j)
		{
			while (command[i + j] != '\'' && ++i)
				str[i - 1] = command[(i - 1) + j];
			j++;
		}
		else if (command[i + j] == '"' && ++j)
		{
			while (command[i + j] != '"' && ++i)
				str[i - 1] = command[(i - 1) + j];
			j++;
		}
		else
		{
			str[i] = command[i + j];
			i++;
		}
	}
	str[i] = 0;
}

static bool	add_cmd(t_token **begin, char **command)
{
	char	*str;
	int		length;
	int		quotes;
	int		i;

	i = 0;
	length = length_cmd(*command, &quotes);
	if (((length) - (2 * quotes)) < 0)
		return (true);
	str = malloc(sizeof(char) * ((length + 1) - (2 * quotes)));
	if (!str)
		return (false);
	copy_token(*command, length - (2 * quotes), str, i);
	if (!add_to_list_token(begin, str, 0))
		return (false);
	if ((*begin)->prev == (*begin) || (*begin)->prev->prev->type == PIPE)
		(*begin)->prev->type = CMD;
	else
		(*begin)->prev->type = ARG;
	(*command) += length;
	return (true);
}

static bool	add_special(t_token **begin, char **command)
{
	int	spe;

	spe = is_special(*command);
	if (!spe)
		return (false);
	if (spe == INPUT && !add_to_list_token(begin, ft_strdup("<"), INPUT))
		return (false);
	else if (spe == HEREDOC && !add_to_list_token(begin, ft_strdup("<<"), HEREDOC))
		return (false);
	else if (spe == TRUNC && !add_to_list_token(begin, ft_strdup(">"), TRUNC))
		return (false);
	else if (spe == APPEND && !add_to_list_token(begin, ft_strdup(">>"), APPEND))
		return (false);
	else if (spe == PIPE && !add_to_list_token(begin, ft_strdup("|"), PIPE))
		return (false);
	if (spe == INPUT || spe == TRUNC || spe == PIPE)
		(*command)++;
	else if (spe == HEREDOC || spe == APPEND)
		(*command) += 2;
	return (true);
}

bool	create_list_token(t_token **begin, char *command)
{
	(*begin) = NULL;
	while (*command)
	{
		while (is_space(*command))
			command++;
		if (*command && !is_special(command) && !add_cmd(begin, &command))
		{
			if (*begin)
				free_token(begin);
			return (false);
		}
		else if (*command && is_special(command) && \
					!add_special(begin, &command))
		{
			if (*begin)
				free_token(begin);
			return (false);
		}
	}
	return (true);
}
