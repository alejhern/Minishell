/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:11:08 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/13 19:31:21 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*token_lstlast(t_token *lst)
{
	t_token		*temp;

	if (lst == 0)
		return (0);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	token_lstadd_back(t_token **lst, t_token *new)
{
	t_token		*temp;

	if (lst)
	{
		if (*lst)
		{
			temp = token_lstlast(*lst);
			temp->next = new;
		}
		else
			*lst = new;
	}
}
