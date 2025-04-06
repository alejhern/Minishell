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

t_list *subshell_parser(t_list **token_node, int *error)
{
    t_list  *list;
    t_token *token;
    t_list  *current;

    if (!token_node || !*token_node)
        return (NULL);    
    current = (*token_node)->next;
    list = ft_lstnew(ft_calloc(1, sizeof(t_shell)));
    if (!list || !list->content)
    {
        *error = 1;
        return (NULL);
    }
    while (current && *error == 0)
    {
        token = current->content;
        if (!token)
        {
            *error = 1;
            break;
        }
        if (token->type == TOKEN_RPAREN)
            break;
        if (token->type == TOKEN_WORD)
            *error = add_word(list, token);
        else if (token->type == TOKEN_PIPE)
            *error = new_pipe(list);
        else if (token->type == TOKEN_AND || token->type == TOKEN_OR)
            *error = new_conditional(list, token);
        else if (token->type == TOKEN_LPAREN)
            *error = new_subshell(list, &current);
        else if (token->type == TOKEN_LESS || token->type == TOKEN_GREAT)
            *error = add_redirect(list, &current);
        if (*error == 0)
            current = current->next;
    }
    *token_node = current;
    return (list);
}

int new_subshell(t_list *list_og, t_list **token_node)
{
    t_shell     *cond;
    t_command   *command;
    int         error;

    if (!list_og || !token_node || !*token_node)
        return (1);

    t_list *last_node = ft_lstlast(list_og);
    if (!last_node || !last_node->content)
        return (1);

    cond = (t_shell *)last_node->content;
    error = 0;

    if (!cond->command)
    {
        cond->command = ft_lstnew(ft_calloc(1, sizeof(t_command)));
        if (!cond->command || !cond->command->content)
            return (1);
    }
    command = (t_command *)ft_lstlast(cond->command)->content;
    if (!command)
        return (1);
    command->subshell = subshell_parser(token_node, &error);
    return (error);
}

int check_subshell(t_list **token_node) 
{
    t_list  *current;
    t_token *token;
    int     error = 0;

    if (!token_node || !*token_node || !(*token_node)->content)
        return (1);

    token = (*token_node)->content;
    if (token->type != TOKEN_LPAREN)
        return (1);  // No es una subshell si no empieza con '('

    current = (*token_node)->next;
    while (current && error == 0)
    {
        token = (t_token *)current->content;
        if (!token)
            return (1);
        if (token->type == TOKEN_RPAREN)
            break;
        if (token->type == TOKEN_WORD)
            error = check_word(current);
        else if (token->type == TOKEN_PIPE)
            error = check_pipe(current);
        else if (token->type == TOKEN_AND || token->type == TOKEN_OR)
            error = check_conditional(current);
        else if (token->type == TOKEN_LPAREN)
            error = check_subshell(&current);
        else if (token->type == TOKEN_LESS || token->type == TOKEN_GREAT)
            error = check_redirection(&current);
        current = current->next;
    }
    if (!current || ((t_token *)current->content)->type != TOKEN_RPAREN)
        return (1); // No se cerró la subshell
    *token_node = current; // Avanzamos el puntero al ')'
    return (error);
}
