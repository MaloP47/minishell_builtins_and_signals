/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:28:13 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/13 13:36:21 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

int main(int ac, char **av, char **env)
{
	(void)av;
	char	*line;
	char	**cdd;
	char	**echoo;
	char	**unsett;
	char	**exportt;
	char	**exitt;
	t_env	*env_perso;
	static char	**env_cpy;

	g_status = 0;
	cdd = 0;
	echoo = 0;
	env_cpy = copy_tab(env);
	env_perso = env_to_lst(env);
	line = 0;
	if (ac != 1)
		return (1);
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (0);
	while (1)
	{
		config_signals(1);
		line = readline("minishrek-V0.1$ ");
		if (!line)
			exit(0);
		if (line && *line)
			add_history(line);
		if (!ft_strcmp(line, "pwd"))
			pwd();
		else if (!ft_strncmp(line, "export", 6))
		{
			exportt = ft_split(line, 32);
			export(exportt, &env_cpy);
			if (exportt)
				free_tab(exportt);
		}
		else if (!ft_strncmp(line, "cd", 2))
		{
			cdd = ft_split(line, 32);
			cd(cdd, env_cpy);
			free_tab(cdd);
		}
		else if (!ft_strcmp(line, "env"))
			env_builtin(env_cpy);
		else if (!ft_strncmp(line, "echo", 4) && line[0] == 32)
		{
			echoo = ft_split(line, 32);
			echo(echoo);
			free_tab(echoo);
		}
		else if (!ft_strncmp(line, "unset", 5))
		{
			unsett = ft_split(line, 32);
			unset(unsett, &env_cpy);
			free_tab(unsett);
		}
		else if (!ft_strcmp(line, "\n"))
			ft_putendl_fd("\n", 1);
		/*else if (!ft_strcmp(line, "exit"))
			break ;*/
		else if (!ft_strncmp(line, "exit", 4))
		{
			exitt = ft_split(line, 32);
			exit_builtin(exitt);
		}
		else if (ft_strlen(line))
			printf("minishrek: %s: command not found\n", line);
		free(line);
		printf("----------------------------------------------------------------------------\n");
	}
	rl_clear_history();
	ft_lstclear_env(&env_perso, &free);
	free(line);
	if (env_cpy)
		free_tab(env_cpy);
}
