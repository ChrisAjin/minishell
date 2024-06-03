/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:18:23 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/31 12:32:09 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitest.h"

void	pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd || pwd[0] == '\0')
		perror("getcwd");
	else
		printf("%s\n", pwd);
	free(pwd);
}
// pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
// exit 1