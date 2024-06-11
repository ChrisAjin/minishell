/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:40:07 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/11 17:45:13 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

bool	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (true);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	if (arr)
		free(arr);
	arr = NULL;
}

void	free_cmd(t_cmd **list)
{
	t_cmd	*tmp;
	t_cmd	*current;

	if (!(*list))
		return ;
	current = *list;
	while (current->next != *list)
	{
		tmp = current;
		current = current->next;
		free_array(tmp->cmd_param);
		free(tmp);
	}
	free_array(current->cmd_param);
	free(current);
	*list = NULL;
}

void	free_all(t_data *data, char *err, int ext)
{
	if (data->cmd)
		free_cmd(&data->cmd);
	if (data->token)
		free_token(&data->token);
	if (data->env)
		free_list(&data->env);
	if (data->pip[0] && data->pip[0] != -1)
		close(data->pip[0]);
	if (data->pip[1] && data->pip[1] != -1)
		close(data->pip[1]);
    (void)err;
	//if (err)
	//	print_error(err);
	//if (!access(".heredoc.tmp", F_OK))
	//	unlink(".heredoc.tmp");
	if (ext != -1)
		exit(ext);
}