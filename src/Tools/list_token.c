/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:20:08 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/28 14:20:09 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	token_new_elem(t_token **new, char *str, int type)
{
	if (!str)
		return (0);
	(*new) = malloc(sizeof(t_token));
	if (*new == NULL)
	{
		free(str);
		return (0);
	}
	(*new)->str = str;
	(*new)->here_doc = NULL;
	(*new)->type = type;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	return (1);
}

int	add_root(t_token **list, char *str, int type)
{
	t_token	*new;
	t_token	*last;

	if (!token_new_elem(&new, str, type))
		return (0);
	if (*list == NULL)
	{
		*list = new;
		(*list)->prev = *list;
		(*list)->next = *list;
	}
	else
	{
		last = (*list)->prev;
		new->next = *list;
		new->prev = last;
		last->next = new;
		(*list)->prev = new;
		*list = new;
	}
	return (1);
}

static void	add_first(t_token **list, t_token *new)
{
	(*list) = new;
	(*list)->prev = *list;
	(*list)->next = *list;
}

int	append_token(t_token **list, char *str, int type)
{
	t_token	*new;

	if (!token_new_elem(&new, str, type))
		return (0);
	if (!(*list))
		add_first(list, new);
	else
	{
		new->prev = (*list)->prev;
		new->next = (*list);
		(*list)->prev->next = new;
		(*list)->prev = new;
	}
	return (1);
}

void	free_token(t_token **list)
{
	t_token	*tmp;
	t_token	*current;

	if (!(*list))
		return ;
	current = *list;
	while (current->next != *list)
	{
		tmp = current;
		current = current->next;
		free(tmp->str);
		free(tmp->here_doc);
		free(tmp);
	}
	free(current->str);
	free(current->here_doc);
	free(current);
	*list = NULL;
}
