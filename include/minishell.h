/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:45:40 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/22 18:42:14 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/src/libft.h"
//# include "../libft-ines/libft.h"
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
# include <signal.h>
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
# define PATH_MAX        4096

//int	g_ext_status;

typedef struct s_cmd
{
	bool			skip_cmd;
	char			**cmd_param;
	struct s_cmd	*next;
	struct s_cmd	*prev;
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
	int			sig;
	int			sigflg;
	int			f_stdin;
	int			f_stdout;
	int				exit_code;
	int				pipes;
	int				infile;
	int				outfile;
	int				pip[2];
	int				temp_fd;
	bool			sq;

}					t_data;
// main.c
int					make_env(t_data *data, char **env);
// Tools_list.c
int					free_list(t_list **list);
int					append(t_list **list, char *elem);
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
bool	print_error(char *str);
// list_token.c
int					append_token(t_token **list, char *str, int type);
void				free_token(t_token **list);

// add_list.c
void append_list(t_list **list, char *str);
void add_root_list(t_list **list, char *str);

// creat_list_token.c
bool				create_list_token(t_token **begin, char *command);
int add_root(t_token **list, char *str, int type);

// cmd_param.c
char				**get_param(t_data *data, t_token *token);

// creat_cmd.c
bool				create_list_cmd(t_data *data);

// list_cmd.c
int	append_cmd(t_cmd **list, char **cmd_param);
void	free_cmd(t_cmd **list);
size_t	len_cmd(t_cmd *list);

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

//fd_check.c
bool	get_outfile(t_token *token, t_cmd *cmd, t_data *data);
bool	get_infile(t_data *data, t_token *token, t_cmd *cmd);
//DEBUG.c
void	print_token(t_token *token);
void	print_cmd(t_cmd *cmd);
void print_tokens(t_token *head);
void print_list(t_list *head);

//signal.c
//void	handle_signal_in_out(t_data *data);

// exec.c
int					exec(t_data *minishell);
void					find_and_exec(t_data *minishell, char **env);
void					exec_path(t_data *minishell, char **env);
int					pipe_count(t_data *minishell);

//here_doc.c
int		here_doc(t_data *data, char *word);
// void		is_here_doc(t_data *minishell, char **env, int read, int write);

// childs.c
void					only_child(t_data *minishell, char **env);
void					first_child(t_data *minishell, char **env);
void					middle_child(t_data *minishell, char **env);
void					last_child(t_data *minishell, char **env);

// errors.c
void					command_not_found(t_data *minishell, char **paths, char **env);
void				permission_denied(t_data *minishell, char**env);
void				no_such_file(t_data *minishell, char **env);

// errors2.c
int					child_fail(t_data *minishell, char **env);
void					exec_fail(t_data *minishell, char **paths, char **env, char *cur_path);
void				dup2_error(t_data *minishell, char **env);

// exec_child.c
int					exec_one_cmd(t_data *minishell, char **env);
int					one_cmd(t_data *minishell, char **env);
int					exec_first_child(t_data *minishell, char **env);
int					exec_middle_childs(t_data *minishell, char **env);
int					exec_last_child(t_data *minishell, char **env);

// exec_utils.c
char				**split_path(char **envp);
void				wait_and_error(t_data *minishell, int pid_lastchild);
int					renew_pipe(t_data *minishell);
int					close_all(t_data *minishell);
void					skip(t_data **minishell);

// exec utils2
void					free_tab(char **tab);
void					close_fds(void);
void					init_fds(t_data *minishell);

// open
int					open_inf_outf(t_data *minishell);
int					infile_count(t_data *minishell);
int					outfile_count(t_data *minishell);
void					open_infile(t_data *minishell, int inf_count);
void					open_outfile(t_data *minishell, int outf_count);

// builtins_utils
void					exec_builtin(t_data *minishell, char **env);
int					is_builtin(char *cmd);
char				*get_pwd(void);
void					free_and_exit(t_data *minishell, char **env, int ret);
int					size_tab(char **cmd_param);

// cd
int					cd(t_data *minishell);
int					ch_dir_home(t_list *env, char *old_pwd);
int				add_pwd(char *cur_dir, t_data *minishell);
int				add_old_pwd(char *old_pwd, t_data *minishell);
char				*get_home(t_list *env);

// echo
int				echo(t_data *minishell);
int				n_option(char *str);
int				print_args(t_data *minishell, int index);

// env
int				env_cmd(t_data *minishell);
int				print_lst(t_list *lst);

// exit
void				exit_shell(t_data *minishell);
int				only_digit(char *str);

// parent_builtin
int				is_parent_builtin(char *cmd);
int				parent_builtin(t_data *minishell, char **env);
int				which_builtin(t_data *minishell);

// pwd
int				pwd(t_data *minishell);

// export
int				export(t_data *minishell);
int				export_print_lst(t_list *lst);
int				is_var(char *str, t_list *env);
int				change_var(char *str, t_list *env);
int				not_valid(t_data *minishell);
int				has_space(char	*str);

// unset
int				unset(t_data *minishell);

//data_check.c
int				check_pipe_red_herdoc(t_data *data);

#endif
