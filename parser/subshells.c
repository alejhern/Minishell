/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshells.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:43:23 by pafranco          #+#    #+#             */
/*   Updated: 2025/05/26 17:57:00 by pafranco         ###   ########.fr       */
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
	if ((*token)->next->type == 0 || (*token)->next->type == 4
		|| (*token)->next->type == 6 || (*token)->next->type == 7)
		check_tokens(0, token, &error, env);
	else
		error = 1;
	if ((*token)->next != 0 && ((*token)->next->type == OPEN_SUB
			|| (*token)->next->type == WORD))
		error = 1;
	return (error);
}
