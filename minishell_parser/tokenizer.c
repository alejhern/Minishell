/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:02:05 by pafranco          #+#    #+#             */
/*   Updated: 2025/04/02 18:32:36 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_cond(char *prompt, int *i, int *error, t_list **token_list)
{
	t_token	*new_token;
	t_list	*new_node;
	int		and;
	int		j;

	int or ;
	or = 0;
	and = 0;
	j = 0;
	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
	{
		ft_lstclear(token_list, free_token);
		*error = 1;
		return ;
	}
	while (prompt[*i + j] == '|' || prompt[*i + j] == '&')
	{
		if (prompt[*i + j] == '|')
			or ++;
		else
			and++;
		j++;
	}
	new_token->type = token_cond_util(or, and, error);
	new_node = ft_lstnew(new_token);
	if (!new_node)
	{
		free(new_token);
		ft_lstclear(token_list, free_token);
		*error = 1;
		return ;
	}
	ft_lstadd_back(token_list, new_node);
	*i += j;
}

t_token_type	token_sub_type(char c)
{
	if (c == '(')
		return (TOKEN_LPAREN);
	else if (c == ')')
		return (TOKEN_RPAREN);
	else if (c == '<')
		return (TOKEN_LESS);
	else if (c == '>')
		return (TOKEN_GREAT);
	else
		return (-1);
}

void	token_sub_red(char *prompt, int *i, int *error, t_list **token_list)
{
	t_token	*new_token;
	t_list	*new_node;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
	{
		ft_lstclear(token_list, free_token);
		*error = 1;
		return ;
	}
	new_token->type = token_sub_type(prompt[*i]);
	if (new_token->type == (t_token_type)-1)
		return (*error = 1, free(new_token), ft_lstclear(token_list,
				free_token));
	new_node = ft_lstnew(new_token);
	if (!new_node)
	{
		free(new_token);
		ft_lstclear(token_list, free_token);
		*error = 1;
		return ;
	}
	ft_lstadd_back(token_list, new_node);
	*i += 1;
}

void	token_quote(char *prompt, int *i, int *error, t_list **token_list)
{
	t_token	*new_token;
	t_list	*new_node;
	int		j;

	new_token = ft_calloc(1, sizeof(t_token));
	j = 1;
	if (!new_token)
		return (ft_lstclear(token_list, free_token));
	while (prompt[*i + j] != prompt[*i] && prompt[*i + j] != '\0')
		j++;
	if (prompt[*i + j] == '\0')
		return (*error = 1, free(new_token), ft_lstclear(token_list,
				free_token));
	j++;
	new_token->token = ft_substr(prompt, *i, j);
	if (prompt[*i] == '\'')
		new_token->type = TOKEN_QUOTE_SINGLE;
	else if (prompt[*i] == '"')
		new_token->type = TOKEN_QUOTE_DOUBLE;
	if (!new_token->token)
		return (*error = 1, free(new_token), ft_lstclear(token_list,
				free_token));
	new_node = ft_lstnew(new_token);
	if (!new_node)
		return (*error = 1, free(new_token->token), free(new_token),
			ft_lstclear(token_list, free_token));
	ft_lstadd_back(token_list, new_node);
	*i += j;
}

void	token_word(char *prompt, int *i, t_list **token_list)
{
	t_token	*new_token;
	t_list	*new_node;
	int		j;

	new_token = ft_calloc(1, sizeof(t_token));
	j = 0;
	if (!new_token)
		return (ft_lstclear(token_list, free_token));
	while (prompt[*i + j] != ' ' && prompt[*i + j] != '\t' && prompt[*i
		+ j] != '\0' && !is_del(prompt[*i + j]))
		j++;
	new_token->token = ft_substr(prompt, *i, j);
	new_token->type = TOKEN_WORD;
	if (!new_token->token)
		return (free(new_token), ft_lstclear(token_list, free_token));
	new_node = ft_lstnew(new_token);
	if (!new_node)
		return (free(new_token->token), free(new_token), ft_lstclear(token_list,
				free_token));
	ft_lstadd_back(token_list, new_node);
	*i += j;
}

t_list	*tokenize(char *prompt, int *error)
{
	int		i;
	t_list	*token_list;

	i = 0;
	token_list = NULL;
	while (prompt[i] && *error == 0)
	{
		while (prompt[i] == ' ' || prompt[i] == '\t' || prompt[i] == '\n')
			i++;
		if (!prompt[i])
			break ;
		if (prompt[i] == '(' || prompt[i] == ')' || prompt[i] == '>'
			|| prompt[i] == '<')
			token_sub_red(prompt, &i, error, &token_list);
		else if (prompt[i] == '&' || prompt[i] == '|')
			token_cond(prompt, &i, error, &token_list);
		else if (prompt[i] == '\'' || prompt[i] == '"')
			token_quote(prompt, &i, error, &token_list);
		else
			token_word(prompt, &i, &token_list);
	}
	if (*error)
		return (ft_lstclear(&token_list, free_token), NULL);
	return (token_list);
}
