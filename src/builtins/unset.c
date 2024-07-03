/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:45:34 by inbennou          #+#    #+#             */
/*   Updated: 2024/07/03 22:23:13 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	unset(t_data *minishell)
// {
// 	t_list	*temp;
// 	int i= 0;

// 	temp = minishell->env;

// 	if (minishell->cmd->cmd_param[1][0] == '-')
// 	{
// 		ft_putstr_fd("unset: invalid option: ", 2);
// 		ft_putendl_fd(minishell->cmd->cmd_param[1], 2);
// 		return (2);
// 	}
// 	if (ft_is_there(minishell->cmd->cmd_param[1], '='))
// 		return (0);
// 	while(minishell->cmd->cmd_param[1][i])
// 	{
// 		if (!ft_strcmp(temp->str,minishell->cmd->cmd_param[1]))
// 		{
// 			temp = temp->next;
// 		}
// 		else
// 			return (unset_var(minishell, temp));
// 	}
// 	return (0);
// }

// int	unset_var(t_data *minishell, t_list *temp)
// {
// 	if (ft_is_there(temp->str, '=') == 0)
// 		return (0);
// 	if (temp == minishell->env)
// 		minishell->env = temp->next;
// 	if (temp->prev)
// 		temp->prev->next = temp->next;
// 	if (temp->next)
// 		temp->next->prev = temp->prev;
// 	free(temp->str);
// 	free(temp);
// 	return (0);
// }

// int	ft_is_there(const char *str, char c)
// {
// 	int	n;

// 	n = 0;
// 	while (str[n])
// 		n++;
// 	while ((str[n] != c) && (n > 0))
// 		n--;
// 	if (str[n] == c)
// 		return (1);
// 	else
// 		return (0);
// }

static bool	syntax(char *str)
{
	int	i;

	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (false);
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static int	exist(char *str, t_list *env)
{
	int		i;
	int		j;
	t_list	*tmp;

	if (!env)
		return (-1);
	i = 0;
	while (str[i])
		i++;
	j = 0;
	tmp = env;
	if (!ft_strncmp(tmp->str, str, i))
		return (j);
	tmp = tmp->next;
	j++;
	while (tmp != env)
	{
		if (!ft_strncmp(tmp->str, str, i))
			return (j);
		tmp = tmp->next;
		j++;
	}
	return (-1);
}

static void	check_env(t_list *tmp, t_list **env)
{
	if (tmp == (*env))
		(*env) = tmp->next;
	if (tmp->next == tmp)
		(*env) = NULL;
}

static bool	ft_unset(char *str, t_list **env)
{
	int		pos;
	int		i;
	t_list	*tmp;

	if (!str || !(*str))
		return (false);
	if (!syntax(str))
	{
		print_error("unset: invalid identifier\n");
		return (true);
	}
	pos = exist(str, (*env));
	if (pos == -1)
		return (false);
	tmp = (*env);
	i = 0;
	while (i++ < pos)
		tmp = tmp->next;
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	free(tmp->str);
	check_env(tmp, env);
	free(tmp);
	tmp = NULL;
	return (false);
}

int	unset(char **str, t_list **env)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 0;
	while (str[i])
	{
		if (ft_unset(str[i], env))
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
