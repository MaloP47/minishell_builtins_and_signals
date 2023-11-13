/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:50:45 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/09 15:17:17 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	static char	buf[MAX_PWD] = {0};

	if (!getcwd(buf, MAX_PWD))
		return (ft_putendl_fd(ERR_PWD, 2), 1);
	else
		ft_putendl_fd(buf, 1);
	return (0);
}
