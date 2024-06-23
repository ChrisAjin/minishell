/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:20 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/22 20:55:19 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool read_in_stdin(t_data *data, char **str, char *word)
{
    char *buf;
    char *new_str;
    *str = NULL;

    while (1)
    {
        buf = readline("> ");
        if (!buf)
        {
            print_error("warning: here-document delimited by end-of-file ");
            print_error("(wanted '");
            print_error(word);
            print_error("')\n");
            break ;
        }
        if (!ft_strncmp(word, buf, INT_MAX))
        {
            free(buf);
            break ;
        }
        if (!replace_dollar(&buf, data))
        {
            free(buf);
            free_all(data, ERR_MALLOC, EXT_MALLOC);
        }

        char *line_with_newline = ft_strjoin(buf, "\n");
        if (!line_with_newline)
        {
            free(buf);
            free(*str);
            return false;
        }

        new_str = ft_strjoin(*str, line_with_newline);
        free(line_with_newline);
        if (!new_str)
        {
            free(buf);
            free(*str);
            return false;
        }

        free(*str);
        *str = new_str;

        free(buf);
    }
    return true;
}

int here_doc(t_data *data, char *word, char **str)
{
    *str = NULL;

    if (!read_in_stdin(data, str, word))
    {
        free(*str);
        return -1;
    }
    return 0;
}
