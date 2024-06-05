/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:10:57 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/05 01:00:03 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int replace_dollar(char **line, t_data *data)
{
    bool doubleq;
    int i;
    char *str;

    i = 0;
    doubleq = false;
    data->simpleq = false;
    str = ft_strdup("");
    while ((*line)[i])
    {
        quoting_choice(&doubleq, &data->simpleq, NULL, (*line)[i]);
        if ((*line)[i] && (*line)[i + 1] && (*line)[i] == '$' && \
			((*line)[i + 1] != '\'' && (*line)[i + 1] != '"') && \
			(ft_isalpha((*line)[i + 1]) || (*line)[i + 1] == '?' || \
			(*line)[i + 1] == '_') && !data->simpleq && \
			!add_dollar((*line), &i, &str, data))
			return (0);
        if ((*line)[i] && !add_char(&(*line)[i], &str, data, &i))
            return (0);
    }
    free(*line);
    *line = str;
    return (1);
}