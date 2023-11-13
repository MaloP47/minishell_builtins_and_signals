/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:12:36 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/09 15:27:52 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_to_lst(char **env)
{
	t_env	*head;
	t_env	*new;
	char	*env_copy;
	int		i;

	i = -1;
	head = 0;
	while (env[++i])
	{
		env_copy = ft_strdup(env[i]);
		if (!env_copy)
		{
			ft_lstclear_env(&head, &free);
			return (NULL);
		}
		new = ft_lstnew_env(env_copy);
		if (!new)
		{
			free(env_copy);
			ft_lstclear_env(&head, &free);
			return (NULL);
		}
		ft_lstadd_back_env(&head, new);
	}
	return (head);
}

char	*get_env(char *var_name, char **env)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(var_name);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], var_name, len) && env[i][len] == '=')
			return (env[i] + len + 1);
	}
	return (0);
}

char	**copy_tab(char **src)
{
	int		i;
	int		size;
	char	**copy;

	if (!src)
		return (0);
	size = 0;
	while (src[size])
		size++;
	copy = ft_calloc(sizeof(char *), size + 1);
	if (!copy)
		return (0);
	i = 0;
	while (i < size)
	{
		copy[i] = ft_strdup(src[i]);
		if (!copy[i])
			return (free_tab(copy), NULL);
		i++;
	}
	copy[i] = 0;
	return (copy);
}

char	**lst_to_chartab(t_env *env)
{
	int		i;
	int		lst_size;
	char	**tab;
	t_env	*tmp;

	i = 0;
	lst_size = ft_lstsize_env(env);
	tmp = env;
	tab = ft_calloc(lst_size, sizeof(char *));
	if (!tab)
		return (NULL);
	while (i < lst_size - 2)
	{
		tab[i] = ft_strdup(tmp->content);
		if (!tab[i])
			return (free_tab(tab), NULL);
		tmp = tmp->next;
		i++;
	}
	tab[lst_size - 2] = 0;
	return (tab);
}

char	*trim_path(char *path)
{
	int	i;
	int	len;

	len = ft_strlen(path);
	if (len > 0 && path[len - 1] == '/')
		len --;
	i = len - 1;
	while (i >= 0)
	{
		if (path[i] == '/')
		{
			if (i == 0)
				path[i + 1] = 0;
			else
				path[i] = 0;
			break ;
		}
		i--;
	}
	return (path);
}
