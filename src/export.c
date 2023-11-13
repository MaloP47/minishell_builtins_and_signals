/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:53:04 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/07 13:27:52 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_export(char *new_export_var)
{
	int		i;
	char	**new_var;

	new_var = ft_split(new_export_var, '=');
	i = -1;
	if (!new_var[0] || ft_strlen(new_var[0]) >= 50)
		return (free_tab(new_var), 1);
	if (!ft_strcmp(new_var[0], "$?"))
		return (free_tab(new_var), 0);
	if (ft_isalpha(new_var[0][0]) || new_var[0][0] == '_'
			|| ft_isdigit(new_var[0][0]))
	{
		if (ft_isdigit(new_var[0][0]))
			return (free_tab(new_var), 1);
	}
	while (new_var[0][++i])
	{
		if (!ft_isalpha(new_var[0][i]) && new_var[0][i]
				!= '_' && !ft_isdigit(new_var[0][i]))
			return (free_tab(new_var), 1);
	}
	return (free_tab(new_var), 0);
}

int	add_to_env(char ***env, char *cmd)
{
	int		i;
	int		size;
	char	**env_tmp;

	i = 0;
	size = 0;
	while ((*env)[size])
		size++;
	env_tmp = ft_calloc(sizeof(char *), size + 2);
	if (!env_tmp)
		return (0);
	while (i < size)
	{
		env_tmp[i] = (*env)[i];
		i++;
	}
	env_tmp[size] = ft_strdup(cmd);
	if (!env_tmp[size])
		return (free_tab(env_tmp), 0);
	env_tmp[size + 1] = 0;
	free(*env);
	*env = env_tmp;
	return (1);
}

int	update_env(char ***env, char *cmd)
{
	int		i;
	char	**var;

	var = ft_split(cmd, '=');
	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], var[0], ft_strlen(var[0])))
		{
			if (!ft_strchr(cmd, '='))
				return (free_tab(var), 0);
			free((*env)[i]);
			(*env)[i] = ft_strdup(cmd);
			if (!(*env)[i])
				return (free_tab(var), 0);
			return (free_tab(var), 0);
		}
		i++;
	}
	free_tab(var);
	return (add_to_env(env, cmd));
}

int	export(char **cmd, char ***env)
{
	int		i;

	i = 1;
	if (!cmd[1])
		return (export_noargs(*env), 1);
	while (cmd[i])
	{
		if (parse_export(cmd[i]))
		{
			ft_printf_fd(2, ERR_EXP_PARSE, cmd[i]);
			i++;
			continue ;
		}
		update_env(env, cmd[i]);
		i++;
	}	
	return (0);
}
