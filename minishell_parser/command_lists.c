/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lists.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:28:03 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/13 19:31:01 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*command_lstlast(t_command *lst)
{
	t_command			*temp;

	if (lst == 0)
		return (0);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	command_lstadd_back(t_command **lst, t_command *new)
{
	t_command		*temp;

	if (lst)
	{
		if (*lst)
		{
			temp = command_lstlast(*lst);
			temp->next = new;
		}
		else
			*lst = new;
	}
}

t_redirect	*redirect_lstlast(t_redirect *lst)
{
	t_redirect			*temp;

	if (lst == 0)
		return (0);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	redirect_lstadd_back(t_redirect **lst, t_redirect *new)
{
	t_redirect		*temp;

	if (lst)
	{
		if (*lst)
		{
			temp = redirect_lstlast(*lst);
			temp->next = new;
		}
		else
			*lst = new;
	}
}
