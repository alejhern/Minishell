/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:08:46 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/26 19:52:15 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_word(t_list *token_node)
{
    t_token *next_token;

    if (!token_node || !token_node->next || !token_node->content || !token_node->next->content)
        return (1);
    next_token = (t_token *)token_node->next->content;
    if (next_token->type == TOKEN_LPAREN)
        return (1);
    return (0);
}

int check_pipe(t_list *token_node)
{
    t_token *next_token;

    if (!token_node || !token_node->next || !token_node->content || !token_node->next->content)
        return (1);
    next_token = (t_token *)token_node->next->content;
    if (next_token->type == TOKEN_WORD ||
        next_token->type == TOKEN_LESS ||
        next_token->type == TOKEN_GREAT ||
        next_token->type == TOKEN_LPAREN)
        return (0);
    return (1);
}

int check_conditional(t_list *token_node)
{
    t_token *next_token;

    if (!token_node || !token_node->next || !token_node->content || !token_node->next->content)
        return (1);
    next_token = (t_token *)token_node->next->content;
    if (next_token->type == TOKEN_RPAREN ||
        next_token->type == TOKEN_OR ||
        next_token->type == TOKEN_AND ||
        next_token->type == TOKEN_PIPE)
        return (1);
    return (0);
}

int check_redirection(t_list **token_node)
{
    t_token *token;
    t_token *next_token;

    if (!token_node || !*token_node || !(*token_node)->next || 
        !(*token_node)->content || !(*token_node)->next->content)
        return (1);

    token = (t_token *)(*token_node)->content;
    next_token = (t_token *)(*token_node)->next->content;

    if (token->type == next_token->type)
        *token_node = (*token_node)->next;

    if (!(*token_node)->next || !(*token_node)->next->content)
        return (1);

    next_token = (t_token *)(*token_node)->next->content;
    if (next_token->type == TOKEN_WORD)
        return (0);
    return (1);
}

void check_tokens(t_list *token_list, t_list **token_node, int *error)
{
    t_list *current;
    t_token *token;

    if (token_list)
        current = token_list;
    else if (token_node && *token_node)
        current = (*token_node)->next;
    else
    {
        if (error) *error = 1;
        return;
    }

    while (current && current->next && error && *error == 0)
    {
        token = (t_token *)current->content;
        if (!token)
        {
            *error = 1;
            break;
        }

        if (token->type == TOKEN_RPAREN)
            break;

        if (token->type == TOKEN_WORD)
            *error = check_word(current);
        else if (token->type == TOKEN_PIPE)
            *error = check_pipe(current);
        else if (token->type == TOKEN_OR || token->type == TOKEN_AND)
            *error = check_conditional(current);
        else if (token->type == TOKEN_LPAREN || token->type == TOKEN_RPAREN)
            *error = check_subshell(&current);
        else if (token->type == TOKEN_GREAT || token->type == TOKEN_LESS)
            *error = check_redirection(&current);

        current = current->next;
    }
    if (token_node)
    {
        *token_node = current;
        if (!current && error)
            *error = 1;
    }
}