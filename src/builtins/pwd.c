/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:18:23 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/27 14:44:55 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd(t_data *minishell)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd || pwd[0] == '\0')
	{
		perror("Could not get current working directory");
		free_all(minishell, NULL, -1);
		return (1);
	}
	else
		printf("%s\n", pwd);
	free(pwd);
	return (0);
}
