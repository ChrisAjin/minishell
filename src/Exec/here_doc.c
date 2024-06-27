/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:20 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/27 19:01:49 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	read_in_stdin(t_data *data, char *word)
{
    char	*buf;
    char	*temp;
    char	*final_result = NULL;

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
    // word = ft_calloc(sizeof(char), ft_strlen(final_result));
    // if (!word) {
    //     ft_free(word);
    //     ft_free(final_result);
    //     return false;
    // }
    // ft_strlcpy(word, final_result, ft_strlen(final_result));
    data->token->here_doc = ft_strdup(final_result);
    free(final_result);
    // free(word);
	// printf("word :\n%s\n", data->token->here_doc);
    return true;
}

int here_doc(t_data *data, char *word)
{
    if (!read_in_stdin(data, word))
        return (-1);
    return (0);
}
