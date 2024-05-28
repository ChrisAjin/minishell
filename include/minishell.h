/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:45:40 by cassassa          #+#    #+#             */
/*   Updated: 2024/05/28 18:50:41 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/src/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define INPUT 1   //"<"
# define HEREDOC 2 //"<<"
# define TRUNC 3   //">"
# define APPEND 4  //">>"
# define PIPE 5    //"|"
# define CMD 6     //"|"
# define ARG 7     //"|"

# define EXT_MALLOC 1
# define ERR_MALLOC "error malloc\n"

extern pid_t		g_signal_pid;

typedef struct s_cmd
{
	bool			skip_cmd;
	int				infile;
	int				outfile;
	char			**cmd_param;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_list
{
	char			*str;
	struct s_list	*prev;
	struct s_list	*next;
}					t_list;

typedef struct s_data
{
	t_list	*env;
	t_token	*token;
	t_cmd	*cmd;
	int		exit_code;
	int		pip[2];
	bool	sq;
}				t_data;
// main.c
int make_env(t_data *data, char **env);
// Tools_list.c
int free_list(t_list **list);
int	add_to_list(t_list **list, char *elem);
//utils.c
bool is_space(char c);
int	is_special(char *str);
bool check_pipe(t_data *data);
bool make_env2(t_data *data);

//print_error.c
bool	print_error_token(t_token *token, t_data *data);

//free
void	free_all(t_data *data, char *err, int ext);
void	free_array(char **arr);
void	free_cmd(t_cmd **list);
//list_token.c
int add_to_list_token(t_token **list, char *str, int type);
void free_token(t_token **list);

//creat_list_token.c
bool	create_list_token(t_token **begin, char *command);

//cmd_fd.C
bool	get_outfile(t_token *token, t_cmd *cmd, t_data *data);
bool	get_infile(t_data *data, t_token *token, t_cmd *cmd);

//cmd_param.c
char **get_param(t_data *data, t_token *token);

//creat_cmd.c
bool create_list_cmd(t_data *data);

//list_cmd.c
int	add_list_cmd(t_cmd **list, int infile, int outfile, char **cmd_param);

//DEBUG.c
void	print_token(t_token *token);
#endif
