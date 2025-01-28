/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:55:44 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/28 12:18:32 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include "../libft/libft.h"

typedef struct s_data
{
	char	**envp;
	int		envp_len;
	int		exit_code;
}	t_data;

typedef struct s_cmd
{
	char	**args;
	int		fd_in;
	int		fd_out;
	int		pid;
	int		argc;
}	t_cmd;

//	VISUAL

void	get_title(void);
char	*get_prompt(void);

// PARSING

int		parse_cmd(t_cmd *cmd, char **line, int cmd_len, int args_len);
int		find_lens(char **line, int *i, int *cmd_len, int *args_len);
char	**ft_line_spliter(char const *s);
int		syntax_parsing(char **line);
void	parse_builtin(char **line, t_data *data);
void	parse_line(char **line, t_data *data);
int		get_redirect_fd(t_cmd *cmd, char **line, int i);
int		get_heredoc_fd(char *limiter, char *name);
char	*init_cmd_path(t_cmd *cmd, t_data *data);

//EXEC

void	ft_exec(t_cmd *cmd, t_data *data);

//	BUILTINS

int		try_exec_builtins(t_cmd *cmd);
int		exec_builtins(t_cmd *cmd, t_data *data);
int		ft_echo(t_cmd *cmd);
int		ft_cd(char *path);
int		ft_pwd(void);
int		ft_env(t_data *data);
int		ft_export(t_data *data, char *arg);
int		ft_unset(t_data *data, char *arg);
void	ft_exit(int exit_code, t_cmd *cmd, t_data *data);

//	ENV
char	*parse_var_name(char *arg);
int		get_env_size(char **data);
int		get_env_index(char *env_var, t_data *data);
char	**realloc_envp(char **old_envp, size_t new_size);

#endif
