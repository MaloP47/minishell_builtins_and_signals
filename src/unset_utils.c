/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:25:04 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/09 15:25:08 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize_env(t_env *lst)
{
	size_t	total;

	total = 0;
	while (lst)
	{
		lst = lst->next;
		total++;
	}
	return (total);
}

void	ft_lstdelone_env(t_env *lst, void (*del)(void*))
{
	if (!del || !lst)
		return ;
	if (lst)
	{
		(*del)(lst->content);
		free(lst);
	}
}

void	ft_lstclear_env(t_env **lst, void (*del)(void *))
{
	t_env	*tmp;

	if (!*lst || !lst || !del)
		return ;
	while (lst && *lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone_env(*lst, del);
		*lst = tmp;
	}
	*lst = 0;
}

t_env	*ft_lstlast_env(t_env *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(t_env **lst, t_env *newl)
{
	t_env	*last;

	if (!*lst)
	{
		*lst = newl;
		return ;
	}
	last = ft_lstlast_env(*lst);
	last->next = newl;
}
