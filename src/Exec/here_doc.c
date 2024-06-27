/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:20 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/27 16:39:06 by cassassa         ###   ########.fr       */
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


char	*ft_strnjoin(char  *s1, char  *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++j])
		str[++i] = s1[j];
	j = -1;
	while (s2[++j])
		str[++i] = s2[j];
	str[i + 1] = '\0';
	//free((char *)s1);
	return (str);
}
// static bool	read_in_stdin(t_data *data, char *word)
// {
//     char	*buf;

//     // printf("HERE:%s\n", data->token->here_doc);
//     // data->token->here_doc = NULL;

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
//         // if (!replace_dollar(&buf, data))
//         // {
// 		// 	//free(data->token->here_doc);
//         //     free_all(data, ERR_MALLOC, EXT_MALLOC);
//         //     return false;
//         // }

//         if(data->token->here_doc == NULL)
//         {
//             data->token->here_doc = ft_strdup(buf);
//             // if (!data->token->here_doc)
//         }
//         // else
//         // {
//         //     data->token->here_doc = ft_strjoin(data->token->here_doc, buf);
//         //     free(buf);
//         // }
//     }
//     free(buf);
//     free(data->token->here_doc);
//     return true;
// }
static bool	read_in_stdin(t_data *data, char *word)
{
    char	*buf;

    // printf("HERE:%s\n", data->token->here_doc);
    // data->token->here_doc = NULL;

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
        // if (!replace_dollar(&buf, data))
        // {
		// 	//free(data->token->here_doc);
        //     free_all(data, ERR_MALLOC, EXT_MALLOC);
        //     return false;
        // }
        add_root_list(&data->token->here_doc, buf);
        free(buf);
    }
    free(buf);
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
