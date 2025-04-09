/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshells.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:43:23 by pafranco          #+#    #+#             */
/*   Updated: 2025/04/07 18:17:30 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	command->subshell = token_parser(0, &error, token);
	return (error);
}

int	check_subshell(t_token **token)
{
	int					error;

	error = 0;
	if ((*token)->next->type == 0 || (*token)->next->type == 4
		|| (*token)->next->type == 6 || (*token)->next->type == 7)
		check_tokens(0, token, &error);
	else
		error = 1;
	if ((*token)->next != 0 && ((*token)->next->type == OPEN_SUB
			|| (*token)->next->type == WORD))
		error = 1;
	return (error);
}
