/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:46:25 by pafranco          #+#    #+#             */
/*   Updated: 2025/06/18 17:49:34 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_word(t_list *shells, t_token *token)
{
	t_shell		*shell;
	t_command	*command;

	shell = ft_lstlast(shells)->content;
	if (!shell || !shell->commands)
	{
		shell->commands = ft_safe_lstnew(ft_safe_calloc(1, sizeof(t_command)));
		command = ft_lstlast(shell->commands)->content;
	}
	else
		command = ft_lstlast(shell->commands)->content;
	ft_append_array((void ***)&command->command, ft_safe_strdup(token->token));
	if (command->command == 0)
		exit(0);
	return (0);
}

int	new_conditional(t_list *shells, t_token *token)
{
	t_list		*list;
	t_shell		*new_shell;

	list = ft_lstlast(shells);
	new_shell = ft_safe_calloc(1, sizeof(t_shell));
	if (!list)
		return (1);
	if (list->content == shells->content)
		((t_shell *)list->content)->type = AND;
	if (token->type == ORC)
		new_shell->type = OR;
	else if (token->type == ANDC)
		new_shell->type = AND;
	else
		return (1);
	ft_lstadd_back(&shells, ft_safe_lstnew((void *) new_shell));
	return (0);
}

int	new_pipe(t_list *cond_og)
{
	t_shell		*shell;
	t_list		*list;
	t_command	*command;
	t_command	*command2;

	shell = ft_lstlast(cond_og)->content;
	command = ft_safe_calloc(1, sizeof(t_command));
	list = ft_lstnew(command);
	if (!list || !command)
		exit(0);
	command2 = (ft_lstlast(shell->commands)->content);
	if (command2->command == 0 && command2->subshell == 0)
		return (1);
	ft_lstadd_back(&(shell->commands), list);
	return (0);
}

int	add_redirect(t_list *shells, t_token **token)
{
	t_shell		*shell;
	t_command	*command;
	t_list		*red;
	int			type;

	type = (*token)->type;
	shell = ft_lstlast(shells)->content;
	if (!shell->commands)
		shell->commands = ft_safe_lstnew(ft_safe_calloc(1, sizeof(t_command)));
	command = ft_lstlast(shell->commands)->content;
	red = ft_safe_lstnew(ft_safe_calloc(1, sizeof(t_redirect)));
	if ((*token)->next->type == WORD)
		((t_redirect *)red->content)->is_double = 0;
	else if ((*token)->type == (*token)->next->type)
	{
		((t_redirect *)red->content)->is_double = 1;
		*token = (*token)->next;
	}
	((t_redirect *)red->content)->path = ft_strdup((*token)->next->token);
	if (type == IN_RED)
		ft_lstadd_back(&command->redirect_in, red);
	else if (type == OUT_RED)
		ft_lstadd_back(&command->redirect_out, red);
	return (0);
}

t_list	*token_parser(t_token *token, int *error, t_token **token_sub)
{
	t_token		*aux_token;
	t_list		*list;

	if (token == 0 && token_sub != 0)
		aux_token = (*token_sub)->next;
	else
		aux_token = token;
	list = ft_safe_calloc(1, sizeof(t_list));
	list->content = ft_safe_calloc(1, sizeof(t_shell));
	while (aux_token && *error == 0 && aux_token->type != CLOSE_SUB)
	{
		if (aux_token->type == OPEN_SUB || aux_token->type == CLOSE_SUB)
			*error = new_subshell(list, &aux_token);
		else if (aux_token->type == WORD)
			*error = add_word(list, aux_token);
		else if (aux_token->type == PIPE)
			*error = new_pipe(list);
		else if (aux_token->type == ORC || aux_token->type == ANDC)
			*error = new_conditional(list, aux_token);
		else if (aux_token->type == IN_RED || aux_token->type == OUT_RED)
			*error = add_redirect(list, &aux_token);
		aux_token = aux_token->next;
	}
	parser_check(token_sub, aux_token);
	return (list);
}
