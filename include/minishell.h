/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:45:40 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/11 17:44:53 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/src/libft.h"
// # include "../libft-ines/libft.h"
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
# include <errno.h>
// # include <stdarg.h>
// # include <stddef.h>
// # include <string.h>

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
	char			**cmd_param;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_list
{
	char			*str;
	struct s_list	*prev;
	struct s_list	*next;
}					t_list;

typedef struct s_data
{
	t_list			*env;
	t_token			*token;
	t_cmd			*cmd;
	int				exit_code;
	int				pipes;
	int				infile;
	int				outfile;
	int				pip[2];
	int				temp_fd;
	bool			simpleq;
	bool			doubleq;
}					t_data;
// main.c
int					make_env(t_data *data, char **env);
// Tools_list.c
int					free_list(t_list **list);
int					add_to_list(t_list **list, char *elem);
size_t	len_list(t_list *list);

// utils.c
bool				is_space(char c);
int					is_special(char *str);
bool				check_pipe(t_data *data);
bool				make_env2(t_data *data);
char	**list_to_arr(t_list *env);

// print_error.c
bool				print_error_token(t_token *token, t_data *data);

// free
void				free_all(t_data *data, char *err, int ext);
void				free_array(char **arr);
void				free_cmd(t_cmd **list);
bool	print_error(char *str);
// list_token.c
int					add_to_list_token(t_token **list, char *str, int type);
void				free_token(t_token **list);

// creat_list_token.c
bool				create_list_token(t_token **begin, char *command);

// cmd_param.c
char				**get_param(t_data *data, t_token *token);

// creat_cmd.c
bool				create_list_cmd(t_data *data);

// list_cmd.c
int					add_list_cmd(t_cmd **list,
						char **cmd_param);

//quotes.c
int open_quote(t_data *data, char *line);
void quoting_choice(bool *doubleq, bool *simpleq, int *index, char c);

/* dollar_env */
int		exist_in_env(char *line, int *i, t_data *data);
char	*get_elem_env(t_list *env, char *key);
char	*get_dollar_word(char *line, int size);

/* dollar_replace */
int		add_dollar(char *line, int *index, char **str, t_data *data);
int		add_char(char *c, char **str, t_data *data, int *index);
int		replace_dollar(char **line, t_data *data);

//DEBUG.c
void	print_token(t_token *token);

// exec.c
int					exec(t_data *minishell);
int					one_cmd(t_data *minishell, char **env);
int					find_and_exec(t_data *minishell, char **env);
int					exec_path(t_data *minishell, char **env);
int					exec_first_child(t_data *minishell, char **env);
int					exec_last_child(t_data *minishell, char **env);

// childs.c
int					only_child(t_data *minishell, char **env);
int					first_child(t_data *minishell, char **env);
int					middle_child(t_data *minishell, char **env);
int					last_child(t_data *minishell, char **env);

// errors.c
void					command_not_found(t_data *minishell, char **paths, char **env);
void					exec_fail(t_data *minishell, char **paths, char **env);
void				permission_denied(t_data *minishell, char**env);
void				no_such_file(t_data *minishell, char **env);
void				dup2_error(t_data *minishell, char **env);

// utils.c
char				**split_path(char **envp);
void				wait_and_error(t_data *minishell, int pid_lastchild);
int					exec_middle_childs(t_data *minishell, char **env);
int					renew_pipe(t_data *minishell);
int					close_all(t_data *minishell);
int					close_fds(void);

// open
int					infile_count(t_data *minishell);
int					outfile_count(t_data *minishell);
void					open_infile(t_data *minishell, int inf_count);
void					open_outfile(t_data *minishell, int outf_count);

// builtins
int					exec_builtin(t_data *minishell, char **env);
void				exit_shell(t_data *minishell);
void				echo(t_data *minishell);
void				env_cmd(t_data *minishell);
int					cd(t_data *minishell);
void				pwd(t_data *minishell);
char				*get_pwd(void);
char				*get_home(char **envp);
int					ch_dir_home(char **envp, char *old_pwd);
int				add_pwd(char *cur_dir, char **envp);
int				add_old_pwd(char *old_pwd, char **envp);

// builtins_utils
void				print_args(char **tab, int index);
// void				printf_tab(char **tab);

#endif

// Code résolu