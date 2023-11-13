/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:22:21 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/13 13:21:00 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	default_config(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler_default;
	if (sigaction(SIGINT, &sa, 0))
		return (ft_printf_fd(2, ERR_SIGACTION), 1);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, 0))
		return (ft_printf_fd(2, ERR_SIGACTION), 1);
	return (0);
}

int	heredoc_config(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sig_handler_heredoc;
	if (sigaction(SIGINT, &sa, 0))
		return (ft_printf_fd(2, ERR_SIGACTION), 1);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, 0))
		return (ft_printf_fd(2, ERR_SIGACTION), 1);
	return (0);
}

int	child_config(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &sa, 0))
		return (ft_printf_fd(2, ERR_SIGACTION), 1);
	if (sigaction(SIGQUIT, &sa, 0))
		return (ft_printf_fd(2, ERR_SIGACTION), 1);
	return (0);
}

int	parent_config(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sig_handler_parent;
	if (sigaction(SIGINT, &sa, 0))
		return (ft_printf_fd(2, ERR_SIGACTION), 1);
	sa.sa_handler = sig_handler_parent;
	if (sigaction(SIGQUIT, &sa, 0))
		return (ft_printf_fd(2, ERR_SIGACTION), 1);
	return (0);
}

int	config_signals(int config)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	if (config == DEFAULT_SIG)
		default_config();
	else if (config == HEREDOC_SIG)
		heredoc_config();
	else if (config == CHILD_SIG)
		child_config();
	else if (config == PARENT_SIG)
		parent_config();
	return (0);
}

/*int	config_signals(int config)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	if (config == DEFAULT_SIG)
	{
		sa.sa_handler = sigint_handler_default;
		if (sigaction(SIGINT, &sa, 0))
			return (ft_printf_fd(2, ERR_SIGACTION), 1);
		sa.sa_handler = SIG_IGN;
		if (sigaction(SIGQUIT, &sa, 0))
			return (ft_printf_fd(2, ERR_SIGACTION), 1);
	}
	else if (config == HEREDOC_SIG)
	{
		sa.sa_handler = sigint_handler_heredoc;
		if (sigaction(SIGINT, &sa, 0))
			return (ft_printf_fd(2, ERR_SIGACTION), 1);
		sa.sa_handler = SIG_IGN;
		if (sigaction(SIGQUIT, &sa, 0))
			return (ft_printf_fd(2, ERR_SIGACTION), 1);
	}
	else if (config == CHILD_SIG)
	{
		sa.sa_handler = SIG_DFL;
		if (sigaction(SIGINT, &sa, 0))
			return (ft_printf_fd(2, ERR_SIGACTION), 1);
		if (sigaction(SIGQUIT, &sa, 0))
			return (ft_printf_fd(2, ERR_SIGACTION), 1);
	}
	else if (config == PARENT_SIG)
	{
		sa.sa_handler = sig_handler_parent;
		if (sigaction(SIGINT, &sa, 0))
			return (ft_printf_fd(2, ERR_SIGACTION), 1);
		sa.sa_handler = sig_handler_parent;
		if (sigaction(SIGQUIT, &sa, 0))
			return (ft_printf_fd(2, ERR_SIGACTION), 1);
	}
	return (0);
}*/
