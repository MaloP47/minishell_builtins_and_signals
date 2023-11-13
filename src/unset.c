/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:53:30 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/09 15:27:59 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*return_link_by_str(t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, str, ft_strlen(str)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env	*ft_lstnew_env(void *content)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

int	pop_node(t_env **head, t_env *to_remove)
{
	t_env	*current;

	if (!head || !*head || !to_remove)
		return (0);
	current = *head;
	if (*head == to_remove)
	{
		*head = to_remove->next;
		return (ft_lstdelone_env(to_remove, &free), 0);
	}
	while (current->next && current->next != to_remove)
		current = current->next;
	if (current->next != to_remove)
		return (0);
	current->next = to_remove->next;
	return (ft_lstdelone_env(to_remove, &free), 1);
}

int	unset_end(char ***env, t_env *head)
{
	free_tab(*env);
	*env = lst_to_chartab(head);
	ft_lstclear_env(&head, &free);
	return (0);
}

int	unset(char **cmd, char ***env)
{
	int		i;
	t_env	*env_lst;
	t_env	*head;

	i = 0;
	if (!cmd[1])
		return (0);
	env_lst = env_to_lst(*env);
	head = env_lst;
	while (cmd[++i])
	{
		env_lst = head;
		while (env_lst)
		{
			if (!ft_strncmp(env_lst->content, cmd[i], ft_strlen(cmd[i]))
				&& (env_lst->content[ft_strlen(cmd[i])] == '='
					|| env_lst->content[ft_strlen(cmd[i])] == 0))
			{
				pop_node(&head, return_link_by_str(env_lst, cmd[i]));
				break ;
			}
			env_lst = env_lst->next;
		}
	}
	return (unset_end(env, head));
}
