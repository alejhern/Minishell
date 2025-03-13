/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:46:25 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/13 22:23:18 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_word(t_conditional *cond_og, t_token *token)
{
	int						i;
	t_conditional			*cond;
	t_command				*command;
	char					**new;

	i = 0;
	cond = cond_lstlast(cond_og);
	if (!cond->command)
		cond->command = p_calloc(1, sizeof(t_command), cond_og);
	command = command_lstlast(cond->command);
	while(command->argv && command->argv[i])
		i++;
	new	= p_calloc(i + 2, sizeof(char), cond);
	i = 0;
	while (command->argv && command->argv[i])
	{
		new[i] = command->argv[i];
		i++;
	}
	new[i] = p_strdup(token->token, cond);
	if (command->argv)
		free(command->argv);
	command->argv = new;
	return (0);
}

int	new_pipe(t_conditional *cond_og)
{
	t_conditional			*cond;
	t_command				*command;

	cond = cond_lstlast(cond_og);
	if (!cond->command)
		return (1);
	command = command_lstlast(cond->command);
	command->next = p_calloc(1, sizeof(t_command), cond_og);
	return(0);
}

int	new_conditional(t_conditional *cond_og, t_token *token)
{
	t_conditional			*cond;

	cond = cond_lstlast(cond_og);
	if (!cond)
		return (1);
	cond->next = p_calloc (1, sizeof(t_conditional), cond_og);
	if (token->type == 2)
		cond->type = 2;
	else if (token->type == 3)
		cond->type = 1;
	else
	{//a
		printf("pau ets tonto");
		return (1);
	}
	return (0);
}

int	add_redirect(t_conditional *cond_og, t_token **token)
{
	t_conditional			*cond;
	t_command				*command;
	t_redirect				*red;

	cond = cond_lstlast(cond_og);
	if (!cond->command)
		cond->command = p_calloc(1, sizeof(t_command), cond_og);
	command = command_lstlast(cond->command);
	red = p_calloc(1, sizeof(t_redirect), cond_og);
	if ((*token)->next->type == 0)
		red->is_double = 0;
	else if ((*token)->type == (*token)->next->type)
	{
		red->is_double = 1;
		*token = (*token)->next;
	}
	else
		return (1);
	*token = (*token)->next;
	red->path = p_strdup((*token)->token, cond_og);
	if ((*token)->type == 6)
		redirect_lstadd_back(&command->redirect_in, red);
	else
		redirect_lstadd_back(&command->redirect_out, red);
	return (0);
}

int	new_subshell(t_conditional *cond_og, t_token **token)
{
	//TODO
	//POOTSER SE COM FER-HO PERO CREC QUE ES UN GUARRADA (un void*per guardar el t_conditional i castear-lo sempre)
	//TODO
	cond_og = 0;
	token = 0;
	if (cond_og == 0 && token == 0)
		return (0);
	return (1);
}

t_conditional	*token_parser(t_token *token, int *error)
{
	t_token				*aux;
	t_conditional		*cond;

	aux = token;
	cond = ft_calloc(1, sizeof(t_conditional));
	while (aux && *error == 0)
	{
		if (aux->type == 0)
			*error = add_word(cond, aux);
		else if (aux->type == 1)
			*error = new_pipe(cond);
		else if (aux->type == 2 || aux->type == 3)
			*error = new_conditional(cond, aux);
		else if (aux->type == 4 || aux->type == 5)
			*error = new_subshell(cond, &aux);
		else if (aux->type == 7 || aux->type == 6)
			*error = add_redirect(cond, &aux);
		aux = aux->next;
	}
	return (cond);
}
