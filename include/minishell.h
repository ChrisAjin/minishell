/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:45:40 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/06 14:52:35 by cassassa         ###   ########.fr       */
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

// cmd_fd.C
bool				get_outfile(t_token *token, t_cmd *cmd, t_data *data);
bool				get_infile(t_data *data, t_token *token, t_cmd *cmd);

// cmd_param.c
char				**get_param(t_data *data, t_token *token);

// creat_cmd.c
bool				create_list_cmd(t_data *data);

// list_cmd.c
int					add_list_cmd(t_cmd **list, int infile, int outfile,
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
int					skip_prev(t_data *minishell, int child_nbr);
int					exec(t_data *minishell);
int					one_cmd(t_data *minishell);
int					find_and_exec(t_data *minishell, int child_nbr);
int					exec_path(t_data *minishell, int child_nbr);
int					exec_first_child(t_data *minishell, int child_nbr);
int					exec_last_child(t_data *minishell, int child_nbr);

// childs.c
int					only_child(t_data *minishell);
int					first_child(t_data *minishell, int child_nbr);
int					middle_child(t_data *minishell, int child_nbr);
int					last_child(t_data *minishell, int child_nbr);

// errors.c
int					command_not_found(t_data *minishell, char **paths);
int					exec_fail(t_data *minishell, char **paths);
void				permission_denied(t_data *minishell);
void				no_such_file(t_data *minishell);
void				dup2_error(t_data *minishell, int infile, int outfile);

// utils.c
char				**split_path(char **envp);
void				wait_and_error(t_data *minishell, int pid_lastchild);
int					exec_middle_childs(t_data *minishell, int child_nbr);
int					renew_pipe(t_data *minishell);
int					close_all(t_data *minishell, int infile, int outfile);
int					close_fds(void);

// builtins
int					exec_builtin(char *line, char **envp);
void				exit_shell(int write_ex);
void				echo(char **tab);
void				env_cmd(char **tab, char **env);
int					cd(char **tab, char **envp);
void				pwd(void);
char				*get_pwd(void);
char				*get_home(char **envp);
int					ch_dir_home(char **envp, char *old_pwd);
void				add_pwd(char *cur_dir, char **envp);
void				add_old_pwd(char *old_pwd, char **envp);

// builtins_utils
void				print_args(char **tab, int index);
void				printf_tab(char **tab);

#endif

// Code résolu
