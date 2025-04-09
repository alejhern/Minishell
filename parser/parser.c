/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:46:25 by pafranco          #+#    #+#             */
/*   Updated: 2025/04/09 12:14:35 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_word(t_list *list_og, t_token *token)
{
	t_shell					*cond;
	t_command				*command;

	cond = ft_lstlast(list_og)->content;
	if (!cond || !cond->command)
	{
		cond->command = p_lstnew(p_calloc(1, sizeof(t_command)));
		command = cond->command->content;
	}
	else
		command = ft_lstlast(cond->command)->content;
	ft_append_array((void ***) &command->argv, p_strdup(token->token));
	if (command->argv == 0)
		exit(0);
	return (0);
}

int	new_conditional(t_list *list_og, t_token *token)
{
	t_list					*list;

	list = ft_lstlast(list_og);
	if (!list)
		return (1);
	if (token->type == ORC)
		((t_shell *) list->content)->type = OR;
	else if (token->type == ANDC)
		((t_shell *) list->content)->type = AND;
	else
		return (1);
	ft_lstadd_back(&list_og, p_lstnew(p_calloc(1, sizeof(t_shell))));
	return (0);
}

int	new_pipe(t_list *cond_og)
{
	t_shell					*con;
	t_list					*list;
	t_command				*command;
	t_command				*command2;

	con = ft_lstlast(cond_og)->content;
	command = p_calloc(1, sizeof(t_command));
	list = ft_lstnew(command);
	if (!list || !command)
		exit(0);
	command2 = (ft_lstlast(con->command)->content);
	if (command2->argv == 0 && command2->subshell == 0)
		return (1);
	ft_lstadd_back(&(con->command), list);
	return (0);
}

int	add_redirect(t_list *list_og, t_token **token)
{
	t_shell					*cond;
	t_command				*command;
	t_list					*red;
	int						type;

	type = (*token)->type;
	cond = ft_lstlast(list_og)->content;
	if (!cond->command)
		ft_lstadd_back(&list_og, p_lstnew(p_calloc(1, sizeof(t_command))));
	command = ft_lstlast(cond->command)->content;
	red = p_lstnew(p_calloc(1, sizeof(t_redirect)));
	if ((*token)->next->type == WORD)
		((t_redirect *) red->content)->is_double = 0;
	else if ((*token)->type == (*token)->next->type)
	{
		((t_redirect *) red->content)->is_double = 1;
		*token = (*token)->next;
	}
	*token = (*token)->next;
	heredoc(*token, ((t_redirect *) red->content), type);
	if (type == IN_RED)
		ft_lstadd_back(&command->redirect_in, red);
	else if (type == OUT_RED)
		ft_lstadd_back(&command->redirect_out, red);
	return (0);
}

t_list	*token_parser(t_token *token, int *error, t_token **token_sub)
{
	t_token				*aux;
	t_list				*list;

	if (token == 0 && token_sub != 0)
		aux = (*token_sub)->next;
	else
		aux = token;
	list = p_calloc(1, sizeof(t_list));
	list->content = p_calloc(1, sizeof(t_shell));
	while (aux && *error == 0 && aux->type != CLOSE_SUB)
	{
		if (aux->type == WORD)
			*error = add_word(list, aux);
		else if (aux->type == PIPE)
			*error = new_pipe(list);
		else if (aux->type == ORC || aux->type == ANDC)
			*error = new_conditional(list, aux);
		else if (aux->type == OPEN_SUB || aux->type == CLOSE_SUB)
			*error = new_subshell(list, &aux);
		else if (aux->type == IN_RED || aux->type == OUT_RED)
			*error = add_redirect(list, &aux);
		aux = aux->next;
	}
	parser_check(token_sub, aux);
	return (list);
}
