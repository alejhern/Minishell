/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:02:05 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/26 19:42:44 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_cond(char *prompt, int *i, int *error, t_token **token)
{
	t_token				*next;
	int					or;
	int					and;
	int					j;

	or = 0;
	and = 0;
	j = 0;
	while (prompt[*i + j] == '|' || prompt[*i + j] == '&')
	{
		if (prompt[*i + j] == '|')
			or++;
		else if (prompt[*i + j] == '&')
			and++;
		j++;
	}
	next = ft_calloc(1, sizeof(t_token));
	if (!token)
		free_token(*token, 1);
	next->type = token_cond_util(or, and, error, next);
	token_lstadd_back(token, next);
	next->next = 0;
	*i += j;
}

void	token_sub_red(char *prompt, int *i, int *error, t_token **token)
{
	t_token				*next;

	next = ft_calloc(1, sizeof(t_token));
	if (!token)
		free_token(*token, 1);
	if (prompt[*i] == '(')
		next->type = 4;
	else if (prompt[*i] == ')')
		next->type = 5;
	else if (prompt[*i] == '<')
		next->type = 6;
	else if (prompt[*i] == '>')
		next->type = 7;
	else
		*error = 1;
	token_lstadd_back(token, next);
	next->next = 0;
	*i += 1;
}

void	token_quote(char *prompt, int *i, int *error, t_token **token)
{
	t_token				*next;
	int					j;

	j = 1;
	next = ft_calloc(1, sizeof(t_token));
	if (!token)
		free_token(*token, 1);
	while (prompt[j + *i] != prompt[*i] && prompt[j + *i] != 0)
		j++;
	if (prompt[j + *i] == 0)
		*error = 1;
	else
		j++;
	token_lstadd_back(token, next);
	next->next = 0;
	next->token = ft_substr(prompt, *i, j);
	if (!next->token)
		free_token(*token, 1);
	*i += j;
}

void	token_word(char *prompt, int *i, t_token **token)
{
	t_token				*next;
	int					j;

	j = 0;
	next = ft_calloc(1, sizeof(t_token));
	if (!token)
		free_token(*token, 1);
	while (prompt[*i + j] != ' ' && prompt[*i + j] != '	' && prompt[*i + j]
		&& !is_del(prompt[*i + j]))
		j++;
	token_lstadd_back(token, next);
	next->token = ft_substr(prompt, *i, j);
	next->next = 0;
	if (!next->token)
		free_token(*token, 1);
	*i += j;
}

t_token	*tokenize(char *prompt, int *error)
{
	int				i;
	t_token			*token;

	i = 0;
	token = 0;
	while (prompt[i] && *error == 0)
	{
		while (prompt[i] == ' ' || prompt[i] == '	' || prompt[i] == '\n')
			i++;
		if (prompt[i] == '&' || prompt[i] == '|')
			token_cond(prompt, &i, error, &token);
		else if (prompt[i] == '(' || prompt[i] == ')' || prompt[i] == '>'
			|| prompt[i] == '<')
			token_sub_red(prompt, &i, error, &token);
		else if (prompt[i] == '\'' || prompt[i] == '"')
			token_quote(prompt, &i, error, &token);
		else if (prompt[i])
			token_word(prompt, &i, &token);
	}
	return (token);
}
