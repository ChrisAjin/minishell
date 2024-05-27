/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:16:00 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/26 16:26:38 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitest.h"

// !! prompt doit revenir a la ligne mm s'il y a l'option -n
// gerer les quotes
// implementer le cas "echo $var"
// implementer le cas option non reconnue ?
void	echo(char **tab)
{
	int	n;

	n = 0;
	if (tab[1] == NULL)
	{
		printf("\n");
		return ;
	}
	if (ft_strncmp(tab[1], "-n", 3) == 0)
		n = 1;
	if (tab[1 + n] != NULL)
		print_args(tab, 1 + n);
	if (n != 1)
		printf("\n");
}

void	print_args(char **tab, int index)
{
	int	y;

	y = index;
	while (tab[y + 1])
	{
		printf("%s ", tab[y]);
		y++;
	}
	printf("%s", tab[y]);
}
