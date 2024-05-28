/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:32:17 by cassassa          #+#    #+#             */
/*   Updated: 2024/05/28 15:35:59 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_space(char c)
{
	if (c && (c == ' ' || c == '\n' || c == '\r' || c == '\f' || c == '\t' \
	|| c == '\v'))
		return (true);
	return (false);
}
bool check_pipe(t_data *data)
{
	if (data->token->type == PIPE)
	{
		write(2, "syntax error near unexpected toekn '|'\n", 39);
		free_token(&data->token);
		free_cmd(&data->cmd);
		return (false);
	}
	return (true);
}

bool make_env2(t_data *data)
{
	char	path[PATH_MAX];
	char 	tmp;

	tmp = ft_stardup("OLDPWD");
	if (!tmp || !append(&(data->env), tmp) || getcwd(path,PATH_MAX) == NULL)
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	tmp = ft_strjoin("PWD", path);
	if (!tmp || !append(&(data->env), tmp))
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	return (1);
}