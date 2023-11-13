/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:22:18 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/13 13:25:09 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h> 
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h> 
# include <sys/ioctl.h>
# include <errno.h>

# include "messages.h"
# include "libft.h"

# define MAX_PWD 2048
# define LL_MAXOU 9223372036854775807ULL

extern int	g_status;

typedef enum e_signals
{
	DEFAULT_SIG = 1,
	HEREDOC_SIG,
	CHILD_SIG,
	PARENT_SIG
}		t_signals;

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}	t_env;

/* *** cd.c *** */

int			cd_too_many(char **cmd);
int			cd_home(char **cmd, char **env);
int			cd_minus(char **cmd, char **env);
int			cd_point_point(void);
int			cd(char **cmd, char **env);

/* *** echo.c *** */

void		parse_echo_option(char **echo, int *i, int *n);
void		echo(char **echo);

/* *** env.c *** */

void		env_builtin(char **env);

/* *** exit.c *** */

long long	ft_atoull_exit(const char *str);
int			exit_builtin(char **cmd);

/* *** export.c *** */

int			parse_export(char *new_export_var);
int			add_to_env(char ***env, char *cmd);
int			update_env(char ***env, char *cmd);
int			export(char **cmd, char ***env);

/* *** export_noargs.c *** */

void		sort_index(char **tab, int *index, int size);
void		print_export(char **tab, int *index, int size);
void		export_noargs(char **env);

/* *** pwd.c *** */

int			pwd(void);

/* *** sigaction_utils.c *** */

void		sigint_handler_default(int signum);
void		sig_handler_parent(int signum);
void		sig_handler_heredoc(int signum);

/* *** signals.c *** */

int			default_config(void);
int			heredoc_config(void);
int			child_config(void);
int			parent_config(void);
int			config_signals(int config);

/* *** unset.c *** */

t_env		*return_link_by_str(t_env *env, char *str);
t_env		*ft_lstnew_env(void *content);
int			pop_node(t_env **head, t_env *to_remove);
int			unset_end(char ***env, t_env *head);
int			unset(char **cmd, char ***env);

/* *** utils.c *** */

t_env		*env_to_lst(char **env);
char		*get_env(char *var_name, char **env);
char		**copy_tab(char **src);
char		**lst_to_chartab(t_env *env);
char		*trim_path(char *path);

/* *** utils_lst_env.c *** */

int			ft_lstsize_env(t_env *lst);
void		ft_lstdelone_env(t_env *lst, void (*del)(void*));
void		ft_lstclear_env(t_env **lst, void (*del)(void *));
t_env		*ft_lstlast_env(t_env *lst);
void		ft_lstadd_back_env(t_env **lst, t_env *newl);

#endif
