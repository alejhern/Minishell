/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:02:05 by pafranco          #+#    #+#             */
/*   Updated: 2025/06/20 19:40:06 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_cond(char *prompt, int *i, int *error, t_token **token)
{
	int		and;
	int		j;
	int		or;
	t_token	*next;

	or = 0;
	and = 0;
	j = 0;
	while (prompt[*i + j] == '|' || prompt[*i + j] == '&')
	{
		if (prompt[*i + j] == '|')
			or ++;
		else if (prompt[*i + j] == '&')
			and++;
		j++;
	}
	next = ft_calloc(1, sizeof(t_token));
	if (!token)
		free_token(*token);
	next->type = token_cond_util(or, and, error, next);
	token_lstadd_back(token, next);
	next->next = 0;
	*i += j;
}

void	token_sub_red(char *prompt, int *i, int *error, t_token **token)
{
	t_token	*next;

	next = ft_calloc(1, sizeof(t_token));
	if (!token)
		free_token(*token);
	if (prompt[*i] == '(')
		next->type = OPEN_SUB;
	else if (prompt[*i] == ')')
		next->type = CLOSE_SUB;
	else if (prompt[*i] == '<')
		next->type = IN_RED;
	else if (prompt[*i] == '>')
		next->type = OUT_RED;
	else
		*error = 1;
	token_lstadd_back(token, next);
	next->next = 0;
	*i += 1;
}

void	token_word(char *p, int *i, t_token **token, int *error)
{
	t_token	*next;
	int		j;
	int		k;

	j = 0;
	k = 0;
	next = ft_safe_calloc(1, sizeof(t_token));
	while (p[*i + j] != ' ' && p[*i + j] != '	' && p[*i + j]
		&& !is_del(p[*i + j]) && p[j + *i] != 0 && *error == 0)
	{
		while ((p[j + *i] == '\'' || p[j + *i] == '\"')
			&& (p[k + j + *i] != p[j + *i] || k == 0) && *error == 0)
		{
			*error = (p[k + j + *i] == 0);
			k++;
		}
		j++;
		j += k;
		k = 0;
	}
	token_lstadd_back(token, next);
	next->token = ft_substr(p, *i, j);
	if (!next->token)
		free_token(*token);
	*i += j;
}

t_token	*tokenize(char *prompt, int *error)
{
	int		i;
	t_token	*token;

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
		else if (prompt[i])
			token_word(prompt, &i, &token, error);
	}
	return (token);
}
