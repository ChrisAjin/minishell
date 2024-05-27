/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:44:44 by cassassa          #+#    #+#             */
/*   Updated: 2024/05/27 14:25:04 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

pid_t	g_signal_pid;

int	make_env(t_data *data, char **env)
{
	t_list	*list;
	int		i;
	char	*tmp;

	i = -1;
	list = NULL;
	//cas ou il y a une list vide d'env
	while (env[++i])
	{
		tmp = ft_strdup(env[i]);
		if (!tmp)
			return (free_list(&list));
		if (!add_to_list(&list, tmp))
			return (free_list(&list));
	}
	data->env = list;
	return (1);
}
void	init_data(t_data *data, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	data->env = NULL;
	data->token = NULL;
	data->cmd = NULL;
	data->exit_code = 0;
	data->pip[0] = -1;
	data->pip[1] = -1;
	/*init signal a add*/
	g_signal_pid = 0;
	//signals();
}
bool	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (i == (int)ft_strlen(line))
	{
		free(line);
		return (true);
	}
	return (false);
}

bool parsline (t_data *data, char *line){
	
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*line;

	/*init data*/
	init_data(&data, argc, argv);
	if (!make_env(&data, env))
		free_all(&data, ERR_MALLOC, 1);
	while (1)
	{
		line = readline("minishell> ");
		/*if (!line)
			free_all(&data, "exit\n", data.exit_code);*/
		if (empty_line(line))
			continue ;
		add_history(line);
		if (!parsline(&data, line))
			continue ;
		/* exec part*/
		//free_cmd(&data.cmd);
		//free_token(&data.token);
		g_signal_pid = 0;
	}
	// clear hisotory
	free_all(&data, NULL, -1);
	return (0);
}
