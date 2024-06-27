/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:20 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/26 15:11:10 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static bool	read_in_stdin(t_data *data, char *word)
// {
//     char	*buf;
//     char	*temp;
//     char    *lim;
//     int i = 0;

//     lim = ft_strdup(word);
//     while (1)
//     {
//         buf = readline("> ");
//         if (!buf)
//         {
//             print_error("warning: here-document delimited by end-of-file ");
//             print_error("(wanted '");
//             print_error(word);
//             print_error("')\n");
//             break ;
//         }
//         if (!ft_strncmp(lim, buf, INT_MAX))
//         {
//             dprintf(2, "%s\n", word);
//             break ;
//         }
//         if (!replace_dollar(&buf, data))
//         {
// 			ft_free(lim);
//             free_all(data, ERR_MALLOC, EXT_MALLOC);
//             return false;
//         }
//         if (i == 0)
//             temp = ft_strdup(buf);
//         else
//             temp = ft_strjoin(word, buf);
//         ft_free(word);
//         if (!temp)
//         {
//             ft_free(buf);
//             ft_free(lim);
//             return false;
//         }
//         word = ft_strjoin(temp, "\n");
//         ft_free(temp);
//         if (!word)
//         {
//             ft_free(buf);
//             ft_free(lim);
//             return false;
//         }
//         ft_free(buf);
//         if (i < INT_MAX)
//             i++;
//     }
//     ft_free(buf);
//     ft_free(temp);
//     // ft_free(word);
//     ft_free(lim);
// 	// printf("word :\n%s\n", word);
//     return true;
// }


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
			free(final_result);
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
    free(word);
    word = ft_strdup(final_result);
    free(final_result);
	// printf("word :\n%s\n", word);
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
