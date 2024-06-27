/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:20 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/27 15:17:57 by inbennou         ###   ########.fr       */
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

// char	*strjoinfree(char *s1, char *s2)
// {
// 	int		i;
// 	int		j;
// 	char	*str;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!str)
// 		return (NULL);
// 	i = -1;
// 	j = -1;
// 	while (s1[++j])
// 		str[++i] = s1[j];
// 	j = -1;
// 	while (s2[++j])
// 		str[++i] = s2[j];
// 	str[i + 1] = '\0';
//     ft_free(s1);
// 	return (str);
// }

// bool    read_in_stdin(t_data *minishell, char *word)
// {
//     char    *line;
//     char    *temp;
//     char    *res;
//     int i = 0;

//     line = NULL;
//     temp = NULL;
//     res = NULL;
//     while (1)
//     {
//         ft_putstr_fd("> ", 2);
//         line = get_next_line(0, 0);
//         if (line == NULL)
//         {
//             print_error("\nwarning: here-document delimited by end-of-file ");
//             print_error("(wanted '");
//             print_error(word);
//             print_error("')\n");
//             break ;
//         }
//         temp = ft_strtrim(line, "\n");
//         if (ft_strncmp(temp, word, ft_strlen(word) + 1) == 0)
//             break ;
//         if (!replace_dollar(&line, minishell))
//         {
// 			ft_free(temp);
// 			ft_free(line);
// 			ft_free(res);
//             free_all(minishell, ERR_MALLOC, EXT_MALLOC);
//             return false;
//         }
//         if (i == 0)
//             res = ft_strdup(line);
//         else
//         {
//             temp = ft_strjoin(res, line);
//             res = ft_strdup(temp);
//         }
//         ft_free(line);
//         ft_free(temp);
//         if (!res)
//         {
//             ft_free(temp);
// 			ft_free(line);
// 			ft_free(res);
//             free_all(minishell, ERR_MALLOC, EXT_MALLOC);
//             return false;
//         }
//         i++;
//     }
//     ft_free(line);
//     ft_free(temp);
//     get_next_line(0, 1);
//     // ft_free(word);
//     word = res;
//     // ft_free(res);
// 	printf("word :\n%s\n", word);
//     return true;
// }

// static bool	read_in_stdin(t_data *data, char *word)
// {
//     char	*buf;
//     char	*temp;
//     char	*final_result = NULL;
//     int i = 0;

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
//         if (!ft_strncmp(word, buf, INT_MAX))
//         {
//             break ;
//         }
//         if (!replace_dollar(&buf, data))
//         {
// 			free(final_result);
//             free_all(data, ERR_MALLOC, EXT_MALLOC);
//             return false;
//         }
//         if (i == 0)
//             temp = ft_strdup(buf);
//         else
//             temp = ft_strjoin(final_result, buf);
//         free(final_result);
//         if (!temp)
//         {
//             free(buf);
//             return false;
//         }
//         final_result = ft_strjoin(temp, "\n");
//         free(temp);
//         if (!final_result)
//         {
//             free(buf);
//             return false;
//         }
//         free(buf);
//         i++;
//     }
//     free(buf);
//     free(word);
//     word = final_result;
// 	// printf("word :\n%s\n", word);
//     return true;
// }

int here_doc(t_data *data, char *word)
{
    if (!read_in_stdin(data, word))
        return -1;
    return 0;
}
