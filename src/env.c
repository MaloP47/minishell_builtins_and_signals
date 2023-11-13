/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:52:15 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/02 16:36:57 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_equal(char *s)
{
	while (*s)
	{
		if (*s == '=')
			return (1);
		s++;
	}
	return (0);
}

void	env_builtin(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (contains_equal(env[i]))
			printf("%s\n", env[i]);
	}
}
