/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:20 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/23 21:05:41 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	read_in_stdin(t_data *data, char *word)
{
    char	*buf;
    char	*temp;
    char	*final_result = ft_strdup("");

    if (!final_result)
        return false;

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
            break ;
        }
        if (!replace_dollar(&buf, data))
        {
            free_all(data, ERR_MALLOC, EXT_MALLOC);
            return false;
        }
        temp = ft_strjoin(final_result, buf);
        free(final_result);
        if (!temp)
        {
            free(buf);
            return false;
        }
        final_result = ft_strjoin(temp, "\n");
        free(temp);
        if (!final_result)
        {
            free(buf);
            return false;
        }
        free(buf);
    }
    free(buf);
    word = final_result;
	printf("word :\n%s\n", word);
    return true;
}

int here_doc(t_data *data, char *word)
{
    if (!read_in_stdin(data, word))
    {
        return -1;
    }
    return 0;
}
