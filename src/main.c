/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:44:44 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/20 19:55:09 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	make_env(t_data *data, char **env)
{
	t_list	*list;
	int		i;
	char	*tmp;

	i = -1;
	list = NULL;
	//cas ou il y a une list vide d'env
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
	data->pipes = 0;
	data->infile = -1;
	data->outfile = -1;
	data-> pip[0]= -1;
	data->pip[1] = -1;
	data->temp_fd = -1;
	/*init signal a add*/
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

// bool parsline (t_data *data, char *line)
// {
// 	if (open_quote(data, line))
// 	{
// 		free(line);
// 		return (false);
// 	}
// 	if(!replace_dollar(&line, data) || !create_list_token(&data->token, line) )
// 	{
// 		free(line);
// 		free_all(data,ERR_MALLOC, EXT_MALLOC);
// 	}
// 	free(line);
// 	//print_token(data->token);
// 	if (data->token && data->token->prev->type == PIPE)
// 	{
// 		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n",2);
// 		data->exit_code = 2;
// 		free_token(&data->token);
// 		return (false);
// 	}
// 	if(data->token->next && data->token->next->type == PIPE)
// 	{
// 		ft_putstr_fd("minishell: syntax error near unexpected token '||'\n",2);
// 		data->exit_code = 2;
// 		free_token(&data->token);
// 		return (false);
// 	}
// 	if (check_pipe_red_herdoc(data))
// 		return (false);
// 	if (!data->token || !create_list_cmd(data))
// 	{
// 		free_token(&data->token);
// 		free_cmd(&data->cmd);
// 		return(false);
// 	}
// 	//print_cmd(data->cmd);
// 	return (check_pipe(data));
// }

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
	add_root(&data->token, ft_strdup("new_root"), 0);
	free(line);
	//append_list(&data->env, ft_strdup("NEW_ENV"));
	// print_list(data->env);
	if (data->token && data->token->prev->type == PIPE)
	{
		write(2, "Error: Unclosed pipe\n", 21);
		data->exit_code = 2;
		free_token(&data->token);
		return (false);
	}
	if (check_pipe_red_herdoc(data))
	{
		return (false);
	}
 	 	
	if (!data->token || !create_list_cmd(data))
	{
		free_token(&data->token);
		free_cmd(&data->cmd);
		return (false);
	}
	// print_cmd(data->cmd);
	return (check_pipe(data));
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*line;

	/*init data*/
	if (!isatty(0))
		return (printf("tty required!!\n"), 1);
	init_data(&data, argc, argv);
	if (!make_env(&data, env))
		free_all(&data, ERR_MALLOC, EXT_MALLOC);
	add_root_list(&data.env, ft_strdup("1NEW_ENV"));

	while (1)
	{
		//handle_signal_in_out(&data);
		line = readline("minishell> ");
		if (!line)
			free_all(&data, "exit\n", data.exit_code);
		if (empty_line(line))
			continue ;
		add_history(line);

		if (!parseline(&data, line))
			continue ;
		exec(&data);
		free_cmd(&data.cmd);
		free_token(&data.token);
	}
	rl_clear_history();
	free_all(&data, NULL, -1);
	return (0);
}
