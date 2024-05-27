/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitest.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:31:13 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/25 22:40:05 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITEST_H
#define MINITEST_H

#include "libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

// builtins
int	exec_builtin(char *line, char **envp);
void	exit_shell(int write_ex);
void	echo(char **tab);
int	cd(char **tab, char **envp);
void	pwd(void);
char	*get_pwd();
char	*get_home(char **envp);
int	ch_dir_home(char **envp);
void	add_pwd(char *cur_dir, char **envp);
void	add_old_pwd(char *old_pwd, char **envp);

// utils
void	print_args(char **tab, int index);

#endif