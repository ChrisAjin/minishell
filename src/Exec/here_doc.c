/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:20 by inbennou          #+#    #+#             */
/*   Updated: 2024/07/01 19:21:34 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	finish_hd(char *buf, t_data *data, char *final_result)
{
	ft_free(buf);
	if (final_result)
	{
		ft_free(data->token->here_doc);
		data->token->here_doc = ft_strdup(final_result);
	}
	free(final_result);
	if (!data->token->here_doc)
		return (false);
	else
		return (true);
}

static int	signal_error(t_data *data, char *buf, char *final_result,
		char *word)
{
	if (g_signal_pid == 1)
	{
		data->exit_code = 130;
		return (finish_hd(buf, data, final_result));
	}
	print_error_hd(word);
	return (finish_hd(buf, data, final_result));
}

static char	*fill_temp(char *final_result, char *buf)
{
	char	*temp;

	if (!final_result)
		temp = ft_strdup(buf);
	else
		temp = ft_strjoin(final_result, buf);
	ft_free(final_result);
	return (temp);
}

static bool	read_in_stdin(t_data *data, char *word)
{
	char	*buf;
	char	*temp;
	char	*final_result;

	temp = NULL;
	final_result = NULL;
	signal_here_doc();
	while (1)
	{
		buf = readline("> ");
		if (!buf)
			return (signal_error(data, buf, final_result, word));
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
	return (finish_hd(buf, data, final_result));
}

int	here_doc(t_data *data, char *word)
{
	int		stdin;
	bool	heredoc;

	stdin = dup(STDIN_FILENO);
	heredoc = read_in_stdin(data, word);
	signal(SIGINT, &sig_handler);
	if (dup2(stdin, STDIN_FILENO) < 0)
		return (-1);
	close(stdin);
	if (!heredoc)
		return (-1);
	if (g_signal_pid == 1)
	{
		g_signal_pid = 0;
		return (-1);
	}
	data->exit_code = 0;
	return (0);
}
