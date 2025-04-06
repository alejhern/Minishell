/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshells.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:43:23 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/26 18:55:26 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
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
*/
int new_subshell(t_list *list_og, t_list **token_node)
{
    t_shell     *cond;
    t_command   *command;
    int         error;
    t_list      *last_node;

    if (!list_og || !token_node || !*token_node)
        return (1);

    last_node = ft_lstlast(list_og);
    if (!last_node || !last_node->content)
        return (1);

    cond = (t_shell *)last_node->content;
    error = 0;

    // Initialize command structure if needed
    if (!cond->command)
    {
        cond->command = ft_lstnew(ft_calloc(1, sizeof(t_command)));
        if (!cond->command || !cond->command->content)
            return (1);
    }

    command = (t_command *)ft_lstlast(cond->command)->content;
    if (!command)
        return (1);

    // Parse the subshell tokens
    command->subshell = token_parser(*token_node, &error);
    if (error)
        return (error);

    // Advance past the closing parenthesis
    while (*token_node && ((t_token *)(*token_node)->content)->type != TOKEN_RPAREN)
        *token_node = (*token_node)->next;

    if (!*token_node)
        return (1);

    return (0);
}

int check_subshell(t_list **token_node)
{
    t_token *next;
    int     error;

    if (!token_node || !*token_node || !(*token_node)->content)
        return (1);
    if (!(*token_node)->next || !(*token_node)->next->content)
        return (1);
    next = (t_token *)(*token_node)->next->content;
    error = 0;
    // Check valid tokens after opening parenthesis
    if (next->type == TOKEN_WORD ||        // 0
        next->type == TOKEN_LPAREN ||      // 4
        next->type == TOKEN_LESS ||        // 6
        next->type == TOKEN_GREAT)        // 7
    {
        check_tokens(NULL, token_node, &error);
    }
    else
    {
        error = 1;
    }

    // Additional validation
    if (!error && (*token_node)->next && (*token_node)->next->content)
    {
        next = (t_token *)(*token_node)->next->content;
        if (next->type == TOKEN_LPAREN ||  // OPEN_SUB
            next->type == TOKEN_WORD)      // WORD
        {
            error = 1;
        }
    }

    return (error);
}