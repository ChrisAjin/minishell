/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:20 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/28 17:55:37 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool		result_hd(t_data *data, char *buf, char *final_result);
char    *fill_temp(char *final_result, char *buf);

void	error_hd(char *word)
{
	print_error("warning: here-document delimited by end-of-file ");
	print_error("(wanted '");
	print_error(word);
	print_error("')\n");
}

static bool	read_in_stdin(t_data *data, char *word)
{
	char	*buf;
	char	*temp;
	char	*final_result;

	temp = NULL;
	final_result = NULL;
	while (1)
	{
		buf = readline("> ");
		if (!buf)
			return (error_hd(word), result_hd(data, buf, final_result));
		if (!ft_strncmp(word, buf, ft_strlen(word) + 1))
			break ;
		temp = fill_temp(final_result, buf);
		if (!temp)
			return (free(buf), false);
		final_result = ft_strjoin(temp, "\n");
		ft_free(temp);
		if (!final_result)
			return (free(buf), false);
		ft_free(buf);
	}
	return (result_hd(data, buf, final_result));
}

char    *fill_temp(char *final_result, char *buf)
{
    char    *tmp;

    if (!final_result)
        tmp = ft_strdup(buf);
    else
        tmp = ft_strjoin(final_result, buf);
    ft_free(final_result);
    return (tmp);
}

bool	result_hd(t_data *data, char *buf, char *final_result)
{
	ft_free(buf);
	if (final_result)
		data->token->here_doc = ft_strdup(final_result);
	free(final_result);
	if (!data->token->here_doc)
		return (false);
	return (true);
}

int	here_doc(t_data *data, char *word)
{
	if (!read_in_stdin(data, word))
		return (-1);
	return (0);
}
