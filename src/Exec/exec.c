/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:01:42 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/29 18:35:03 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// open dans les childs pcq chacun peut avoir ses redir
// avant la fonction exec il faut init inf et outf sur stdin et stdout ou sur -1
// gerer le cas ou on a juste un pipe a la fin ?
// skip cmd ?
// comment parcourir les cmds pour les assigner au bon child ?

// compter here_doc comme une cmd s'il n'a pas de commande (ex: << LIM) ?
int	cmd_count(t_data *minishell)
{
	int	i;

	i = 0;
	while (minishell->token)
	{
		if (minishell->token->type == CMD)
			i++;
		// if (minishell->token->type == HEREDOC)
		// {
		// 	if (minishell->token->prev->type != CMD
		// 		&& minishell->token->next->type != CMD)
		// 		i++;
		// }
		minishell->token->next;
	}
	return (i);
}

int	exec(t_data *minishell)
{
	int	ac;

	ac = cmd_count(minishell);
	if (ac == 0) // ou commande vide
		return (0);
	if (ac == 1)
		return (one_cmd(minishell));
	else if (ac > 1)
	{
		// while (ac > 1)
			// exec middle children
	}
	// exec last child
	// close all
	// return wait and error(pid only child ou last child);
}

int	one_cmd(t_data *minishell)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		perror("fork error");
	if (pid == 0)
		// only child
	// init exit code
	return (0);
}
