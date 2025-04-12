/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:08:46 by pafranco          #+#    #+#             */
/*   Updated: 2025/04/09 20:09:11 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_word(t_token *token)
{
	char	*str;
	char	*var;

	if (token->next && token->next->type == OPEN_SUB)
		return (1);
	var = ft_strchr(token->token, '$');
	if (var == 0)
		return (0);
	str = expand(token->token);
	free(token->token);
	token->token = str;
	return (0);
}

int	check_pipe(t_token *token)
{
	if (token->next && (token->next->type == 0 || token->next->type == IN_RED
			|| token->next->type == OUT_RED || token->next->type == OPEN_SUB))
		return (0);
	return (1);
}

int	check_conditional(t_token *token)
{
	if ((token->next && (token->next->type == 5 || token->next->type == ORC
				|| token->next->type == ANDC || token->next->type == PIPE))
		|| !token->next)
		return (1);
	return (0);
}

int	check_redirection(t_token **token)
{
	if ((*token)->next && (*token)->type == (*token)->next->type)
		*token = (*token)->next;
	if ((*token)->next && (*token)->next->type == WORD)
		return (0);
	return (1);
}

void	check_tokens(t_token *token, t_token **token_sub, int *error)
{
	t_token	*aux;

	if (token != 0)
		aux = token;
	else
		aux = (*token_sub)->next;
	while (aux && *error == 0 && aux->type != CLOSE_SUB)
	{
		if (aux->type == WORD)
			*error = check_word(aux);
		else if (aux->type == PIPE)
			*error = check_pipe(aux);
		else if (aux->type == ORC || aux->type == ANDC)
			*error = check_conditional(aux);
		else if (aux->type == OPEN_SUB || aux->type == CLOSE_SUB)
			*error = check_subshell(&aux);
		else if (aux->type == OUT_RED || aux->type == IN_RED)
			*error = check_redirection(&aux);
		aux = aux->next;
	}
	if (token_sub != 0 && *error == 0)
	{
		*token_sub = aux;
		*error = (aux == 0);
	}
}
