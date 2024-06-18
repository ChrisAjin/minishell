/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:07:53 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/18 14:09:11 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*ft_lstnew(char *content);
int	export_print_lst(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);

int	export(t_data *minishell)
{
	t_list	*new_elem;

	if (minishell->cmd->cmd_param[1] == NULL)
		return (export_print_lst(minishell->env));
	if (minishell->cmd->cmd_param[1][0] == '-')
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(minishell->cmd->cmd_param[1], 2);
		ft_putendl_fd(": invalid option", 2);
		return (2);
	}
	else
	{
		if (ft_isdigit(minishell->cmd->cmd_param[1][0]))
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(minishell->cmd->cmd_param[1], 2);
			ft_putend_fd(": not a valid identifier", 2);
			return (1);
		}
		if (ft_strchr(minishell->cmd->cmd_param[1], '=') == 0)
			return (0);
		// add to list
		// new_elem = ft_lstnew(minishell->cmd->cmd_param[1]);
		// ft_lstadd_back((*minishell).env, new_elem);
	}
}

int	export_print_lst(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (1);
	temp = lst;
	if (printf("declare -x %s\n", temp->str) < 0)
	{
		perror("printf");
		return (1);
	}
	temp = temp->next;
	while (temp != lst)
	{
		if (printf("declare -x %s\n", temp->str) < 0)
		{
			perror("printf");
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

t_list	*ft_lstnew(char *content)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->str = content;
	lst->next = NULL;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = ft_lstlast(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}
