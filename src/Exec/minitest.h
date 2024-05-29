/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitest.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:31:13 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/29 13:44:38 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITEST_H
# define MINITEST_H

# include "libft_ines/libft.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>

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
	bool			sq;
}					t_data;

// builtins
int					exec_builtin(char *line, char **envp);
void				exit_shell(int write_ex);
void				echo(char **tab);
void				env_cmd(char **tab, char **env);
int					cd(char **tab, char **envp);
void				pwd(void);
char				*get_pwd(void);
char				*get_home(char **envp);
int					ch_dir_home(char **envp);
void				add_pwd(char *cur_dir, char **envp);
void				add_old_pwd(char *old_pwd, char **envp);

// builtins_utils
void				print_args(char **tab, int index);
void				printf_tab(char **tab);

// errors
int	command_not_found(t_data *minishell, char **paths);
int	exec_fail(t_data *minishell, char **paths);
void	permission_denied(t_data *minishell);
void	no_such_file(t_data *minishell);
void	empty_cmd(char *cmd);

#endif