/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:11:08 by pafranco          #+#    #+#             */
/*   Updated: 2025/05/28 19:50:25 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*token_lstnew(char *token, int type)
{
	t_token			*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		exit(0);
	new->token = token;
	new->type = type;
	return (new);
}

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
