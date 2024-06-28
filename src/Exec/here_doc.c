/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:20 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/28 16:02:53 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	read_in_stdin(t_data *data, char *word)
{
    char	*buf;
    char	*temp = NULL;
    char	*final_result = NULL;

    while (1)
    {
        signal(SIGINT, &sig_handler_heredoc);
		signal(SIGQUIT, SIG_IGN);
        buf = readline("> ");
        if (!buf)
        {
            print_error("warning: here-document delimited by end-of-file ");
            print_error("(wanted '");
            print_error(word);
            print_error("')\n");
            break ;
        }
        if (g_signal_pid == 1)
        {
            data->exit_code = 130;
            g_signal_pid = 0;
            break;
        }

        if (!ft_strncmp(word, buf, ft_strlen(word) + 1))
            break ;
        if (!replace_dollar(&buf, data))
        {
			free(final_result);
            free_all(data, ERR_MALLOC, EXT_MALLOC);
            return false;
        }
        if (!final_result)
            temp = ft_strdup(buf);
        else
            temp = ft_strjoin(final_result, buf);
        ft_free(final_result);
        if (!temp)
        {
            free(buf);
            return false;
        }
        final_result = ft_strjoin(temp, "\n");
        ft_free(temp);
        if (!final_result)
        {
            free(buf);
            return false;
        }
        ft_free(buf);
    }
    ft_free(buf);
    if (final_result)
        data->token->here_doc = ft_strdup(final_result);
    free(final_result);
    if (!data->token->here_doc)
        return false;
	// printf("word :\n%s\n", data->token->here_doc);
    return true;
}

int here_doc(t_data *data, char *word)
{
    if (!read_in_stdin(data, word))
        return (-1);
    return (0);
}
