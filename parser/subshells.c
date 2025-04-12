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
	t_shell					*shell;
	t_command				*command;
	int						error;

	shell = ft_lstlast(list_og)->content;
	error = 0;
	if (!shell || !shell->commands)
	{
		shell->commands = ft_save_lstnew(ft_save_calloc(1, sizeof(t_command)));
		command = shell->commands->content;
	}
	else
		command = ft_lstlast(shell->commands)->content;
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
