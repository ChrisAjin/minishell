/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:20:12 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/28 14:20:13 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**list_to_arr(t_list *env)
{
	t_list	*lst;
	char	**dest;
	int		i;

	dest = NULL;
	i = 0;
	lst = env;
	dest = (char **)malloc(sizeof(char *) * (len_list(lst) + 1));
	if (!dest)
		return (NULL);
	dest[i] = (lst->str);
	lst = lst->next;
	i++;
	while (lst != env)
	{
		dest[i] = (lst->str);
		lst = lst->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}


bool	is_space(char c)
{
	if (c && (c == ' ' || c == '\n' || c == '\r' || c == '\f' || c == '\t' \
	|| c == '\v'))
		return (true);
	return (false);
}

int	is_special(char *str)
{
	if (str && *str && ft_strlen(str) >= 2)
	{
		if (!ft_strncmpp(str, "<<", 2))
			return (HEREDOC);
		if (!ft_strncmpp(str, ">>", 2))
			return (APPEND);
	}
	if (*str && ft_strlen(str) >= 1)
	{
		if (!ft_strncmpp(str, "<", 1))
			return (INPUT);
		if (!ft_strncmpp(str, ">", 1))
			return (TRUNC);
		if (!ft_strncmpp(str, "|", 1))
			return (PIPE);
	}
	return (0);
}

bool	check_pipe(t_data *data)
{
	if (data->token->type == PIPE)
	{
		write(2, "syntax error near unexpected token '|'\n", 39);
		free_token(&data->token);
		free_cmd(&data->cmd);
		return (false);
	}
	return (true);
}

bool	make_env2(t_data *data)
{
	char	path[PATH_MAX];
	char	*tmp;

	// tmp = ft_strdup("OLDPWD");
	// if (!tmp || !append(&(data->env), tmp) || getcwd(path, PATH_MAX) == NULL)
	// 	free_all(data, ERR_MALLOC, EXT_MALLOC);
	if (getcwd(path, PATH_MAX) == NULL)
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	tmp = ft_strjoin("PWD=", path);
	if (!tmp || !append(&(data->env), tmp))
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	return (1);
}

void	absolute_path(char **path, char *cmd, t_data *data)
{
	*path = ft_strdup(cmd);
	if (!(*path))
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	if (access((*path), F_OK))
	{
		write(2, (*path), ft_strlen((*path)));
		write(2, " : command not found\n", 21);
		free(*path);
		*path = NULL;
	}
}
