/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:07:53 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/11 19:31:50 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(t_data *minishell)
{
	// t_list	*export;

	if (minishell->cmd->cmd_param[1] == NULL)
		minishell->exit_code = 2;
	if (ft_strchr(minishell->cmd->cmd_param[1], '='))
	{
		if (ft_isdigit(minishell->cmd->cmd_param[1][0]))
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(minishell->cmd->cmd_param[1], 2);
			ft_putendl_fd(": not a valid identifier", 2);
			minishell->exit_code = 1;
			// free all
		}
		// else
		// {
		// 	export = new_lst(minishell->cmd->cmd_param[1]);
		// 	if (export == NULL)
		// 		minishell->exit_code = 1;
		// 	if (export != NULL)
		// 		add_to_lst(minishell->env, export);
		//	free all
		// }
	}
	// free all
	return (minishell->exit_code);
}

// t_list	*new_lst(char *str)
// {
// 	t_list	*lst;

// 	lst = malloc(sizeof(t_list));
// 	if (!lst)
// 		return (NULL);
// 	lst->str = str;
// 	lst->next = NULL;
// 	return (lst);
// }

// t_list	*last_lst(t_list *lst)
// {
// 	t_list	*temp;

// 	temp = lst;
// 	temp = temp->next;
// 	while (temp != lst)
// 		temp = temp->next;
// 	return (temp);
// }

// void	add_to_lst(t_list **lst, t_list *new)
// {
// 	t_list	*last;

// 	last = last_lst(*lst);
// 	if (!last)
// 		*lst = new;
// 	else
// 		last->next = new;
// }
