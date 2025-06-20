/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshells.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:43:23 by pafranco          #+#    #+#             */
/*   Updated: 2025/06/20 23:08:12 by pafranco         ###   ########.fr       */
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
		shell->commands = ft_safe_lstnew(ft_safe_calloc(1, sizeof(t_command)));
		command = shell->commands->content;
	}
	else
		command = ft_lstlast(shell->commands)->content;
	command->subshell = token_parser(0, &error, token);
	return (error);
}

int	check_subshell(t_token **token, char **env)
{
	int					error;

	error = 0;
	if (((*token)->next->type == WORD || (*token)->next->type == OPEN_SUB
			|| (*token)->next->type == IN_RED
			|| (*token)->next->type == OUT_RED)
		&& (*token)->type == OPEN_SUB)
		check_tokens(0, token, &error, env);
	else
		error = 1;
	if ((*token) == 0 || (*token)->type != CLOSE_SUB
		|| ((*token)->next != 0 && ((*token)->next->type == OPEN_SUB
				|| (*token)->next->type == WORD)))
		error = 1;
	return (error);
}
