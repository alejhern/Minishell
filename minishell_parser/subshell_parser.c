/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:43:23 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/19 19:58:53 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*subshell_parser(t_token **token, int *error)
{
	t_token				*aux;
	t_list				*list;

	aux = (*token)->next;
	list = p_calloc(1, sizeof(t_list));
	list->content = p_calloc(1, sizeof(t_shell));
	while (aux && *error == 0 && aux->type != 5)
	{
		if (aux->type == 0)
			*error = add_word(list, aux);
		else if (aux->type == 1)
			*error = new_pipe(list);
		else if (aux->type == 2 || aux->type == 3)
			*error = new_conditional(list, aux);
		else if (aux->type == 4 || aux->type == 5)
			*error = new_subshell(list, &aux);
		else if (aux->type == 7 || aux->type == 6)
			*error = add_redirect(list, &aux);
		aux = aux->next;
	}
	*token = aux;
	return (list);
}

int	new_subshell(t_list *list_og, t_token **token)
{
	t_shell					*cond;
	t_command				*command;
	int						error;

	cond = ft_lstlast(list_og)->content;
	error = 0;
	if (!cond || !cond->command)
	{
		cond->command = p_lstnew(p_calloc(1, sizeof(t_command)));
		command = cond->command->content;
	}
	else
		command = ft_lstlast(cond->command)->content;
	command->is_subshell = 1;
	command->subshell = subshell_parser(token, &error);
	return (error);
}
