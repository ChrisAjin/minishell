/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:18:23 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/10 18:31:10 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_data *minishell)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd || pwd[0] == '\0')
	{
		perror("Could not get current working directory");
		// free all
		exit(1);
	}
	else
		printf("%s\n", pwd);
	free(pwd);
	// free all
	exit(0);
}
