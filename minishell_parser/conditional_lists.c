/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditional_lists.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:26:19 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/13 19:29:48 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_conditional	*cond_lstlast(t_conditional *lst)
{
	t_conditional		*temp;

	if (lst == 0)
		return (0);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	cond_lstadd_back(t_conditional **lst, t_conditional *new)
{
	t_conditional		*temp;

	if (lst)
	{
		if (*lst)
		{
			temp = cond_lstlast(*lst);
			temp->next = new;
		}
		else
			*lst = new;
	}
}
