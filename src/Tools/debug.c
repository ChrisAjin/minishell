/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:44:29 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/11 23:09:36 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void print_token(t_token *token)
{
    t_token *tmp;

    tmp = token;
    while (tmp->next != token)
    {
        printf("Type : %d, [%s]\n", tmp->type, tmp->str);
        tmp = tmp->next;
    }
    printf("Type : %d, [%s]\n", tmp->type, tmp->str);
}

void	print_tab(char **tab)
{
	int	i;

	if (!(tab))
	{
		printf("NULL");
		return ;
	}
	i = 0;
	printf("[");
	while (tab[i])
	{
		printf("%s", tab[i]);
		if (tab[i + 1])
			printf(", ");
		i++;
	}
	printf("]");
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->next != cmd)
	{
		printf("Skip -> %d, cmd : ",
		tmp->skip_cmd);
		print_tab(tmp->cmd_param);
        
		printf("\n");
		tmp = tmp->next;
	}
	printf("Skip -> %d, cmd : ", tmp->skip_cmd);
	print_tab(tmp->cmd_param);
	printf("\n");
}