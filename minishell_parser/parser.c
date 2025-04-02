/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:46:25 by pafranco          #+#    #+#             */
/*   Updated: 2025/04/02 20:47:39 by pafranco         ###   ########.fr       */
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
	if (token->type == 2)
		((t_shell *) list->content)->type = 2;
	else if (token->type == 3)
		((t_shell *) list->content)->type = 1;
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

	con = ft_lstlast(cond_og)->content;
	command = p_calloc(1, sizeof(t_command));
	list = ft_lstnew(command);
	if (!list || !command)
		exit(0);
	if (((t_command *)ft_lstlast(con->command)->content)->argv == 0)
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
	if ((*token)->next->type == 0)
		((t_redirect *) red->content)->is_double = 0;
	else if ((*token)->type == (*token)->next->type)
	{
		((t_redirect *) red->content)->is_double = 1;
		*token = (*token)->next;
	}
	*token = (*token)->next;
	heredoc(*token, ((t_redirect *) red->content), type);
	if (type == 6)
		ft_lstadd_back(&command->redirect_in, red);
	else if (type == 7)
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
	parser_check(token_sub, aux);
	return (list);
}
