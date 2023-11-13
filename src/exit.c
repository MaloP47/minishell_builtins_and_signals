/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:54:14 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/13 13:35:13 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoull_exit(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	nb;

	i = 0;
	nb = 0;
	sign = 1;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i++] == 45)
			sign *= -1;
	}
	while (ft_isdigit(str[i]))
	{
		nb = (nb * 10) + (str[i] - 48);
		i++;
		if (nb > LL_MAXOU || (nb > (LL_MAXOU + 1) && sign == -1))
			return (ft_printf_fd(2, EXIT_ERR, str), 2);
	}
	return ((long long)nb * sign);
}

int	exit_builtin(char **cmd)
{
	long long	i;
	/* gerer les fd*/
	printf("exit\n");
	if (!cmd[1])
	{
		//tout free
		exit(0);
	}
	i = 0;
	while (cmd[1][i])
	{
		if (!ft_is_sign(cmd[1][i]) && !ft_isdigit(cmd[1][i]))
		{
			ft_printf_fd(2, EXIT_ERR, cmd[1]);
			//tout free
			exit(2);
		}
		i++;
	}
	exit(ft_atoull_exit(cmd[1]));
}
