/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:44:44 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/28 19:10:47 by cassassa         ###   ########.fr       */
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
	if (!(*env))
		return (make_env2(data));
	while (env[++i])
	{
		tmp = ft_strdup(env[i]);
		if (!tmp)
			return (free_list(&list));
		if (!append(&list, tmp))
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
	data->pid = -1;
	data->pipes = 0;
	data->infile = -1;
	data->outfile = -1;
	data->pip[0] = -1;
	data->pip[1] = -1;
	data->temp_fd = -1;
	g_signal_pid = 0;
	//signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
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

bool	parseline(t_data *data, char *line)
{
	if (open_quote(data, line))
	{
		free(line);
		return (false);
	}
	if (!replace_dollar(&line, data) || !create_list_token(&data->token, line))
	{
		free(line);
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	}
	free(line);
	if (check_pipe_red_herdoc(data))
	{
		free_token(&data->token);
		return (false);
	}
	add_root(&data->token, ft_strdup("new_root"), 0);
	if (!data->token || !create_list_cmd(data))
	{
		free_token(&data->token);
		free_cmd(&data->cmd);
		return (false);
	}
	return (check_pipe(data));
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*line;

	if (!isatty(0))
		return (printf("tty required!!\n"), 1);
	init_data(&data, argc, argv);
	if (!make_env(&data, env))
		free_all(&data, ERR_MALLOC, EXT_MALLOC);
	add_root_list(&data.env, "1NEW_ENV");
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			free_all(&data, "exit\n", data.exit_code);
		if (empty_line(line))
			continue ;
		add_history(line);
		if (!parseline(&data, line))
			continue ;
		// while (data.token->type != 0)
		// {
		// 	if (data.token->type == HEREDOC)
		// 		here_doc(&data, data.token->next->str);
		// 	data.token = data.token->next;
		// }
		exec(&data);
		free_cmd(&data.cmd);
		free_token(&data.token);
	}
	rl_clear_history();
	free_all(&data, NULL, -1);
	return (0);
}
