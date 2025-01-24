/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:55:44 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/24 16:18:41 by mmanuell         ###   ########.fr       */
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
}	t_data;

typedef struct s_cmd
{
	char	**args;
	int		fd_in;
	int		fd_out;
}	t_cmd;

char	*get_prompt(void);
void	parse_line(char **line);
int		parse_operator(t_cmd *cmd, char **line, int i);
int		get_heredoc_fd(char *limiter, char *name);
void	ft_echo(char **args);
void	ft_cd(char *path);
void	ft_pwd(void);

//	DATA

t_data	*init_data(char **envp);

//	ENV
void	ft_env(t_data *data);
int		ft_export(t_data *data, char *arg);
int		ft_unset(t_data *data, char *arg);
char	*parse_var_name(char *arg);
int		get_env_size(char **data);
int		get_env_index(char *env_var, t_data *data);
char	**realloc_envp(char **old_envp, size_t new_size);

#endif
