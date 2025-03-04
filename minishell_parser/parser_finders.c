/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_finders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:08:07 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/04 14:52:44 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_delimiter(char *prompt)
{
	long long			i;
	long long			aux;

	i = ft_strchr(prompt, '<') - prompt;
	aux = ft_strchr(prompt, '>') - prompt;
	if (i < 0 || (aux < i && aux > 0))
		i = aux;
	aux = ft_strchr(prompt, ' ') - prompt;
	if (i < 0 || (aux < i && aux > 0))
		i = aux;
	aux = ft_strchr(prompt, '	') - prompt;
	if (i < 0 || (aux < i && aux > 0))
		i = aux;
	aux = ft_strchr(prompt, 0) - prompt;
	if (i < 0 || (aux < i && aux > 0))
		i = aux;
	return (i * (i > 0));
}

int	find_pipe(char *prompt)
{
	long long			i;
	long long			cond;
	long long			quote1;
	long long			quote2;

	i = ft_strchr(prompt, '|') - prompt + 1;
	cond = find_conditional(prompt, 0);
	if (i < 0)
		i = ft_strchr(prompt, 0) - prompt;
	if (cond > 0 && i > cond)
		i = cond;
	quote1 = find_quotes(prompt);
	if (quote1 > 0 && quote1 < i)
	{
		quote2 = find_quotes(&prompt[quote1]);
		i = quote1 + quote2 + find_pipe(&prompt[quote1 + quote2]);
	}
	return (i);
}

int	find_quotes(char *prompt)
{
	long long		i;
	long long		s_quote;
	long long		d_quote;

	if (*prompt == 39 || *prompt == 34)
		i = ft_strchr(prompt + 1, *prompt) - prompt;
	else
	{
		s_quote = ft_strchr(prompt + 1, '\'') - prompt;
		d_quote = ft_strchr(prompt + 1, '\"') - prompt;
		if (s_quote >= 0 && (d_quote < 0 || s_quote < d_quote))
			i = s_quote;
		else if (d_quote >= 0)
			i = d_quote;
		else
			i = -1;
	}
	return (i);
}

int	find_sub(char *prompt)
{
	int			i;
	char		*sub;

	i = 0;
	sub = prompt;
	while (sub)
	{
		i++;
		sub = ft_strchr(sub, '(');
	}
	sub = prompt;
	while (sub)
	{
		i--;
		sub = ft_strchr(sub, ')');
	}
	return (i);
}

int	avoid_quotes(char *prompt, int og, int *type)
{
	int				i;
	int				j;

	i = find_quotes(prompt);
	if (i > 0 && i < og)
	{
		j = find_quotes(&prompt[i]);
		og = i + j + find_conditional(&prompt[i + j], type);
	}
	return (og);
}

int	find_conditional(char *prompt, int *type)
{
	int					and;
	int					or;
	int					t;
	long long			sub;
	long long			ret;

	and = double_strchr(prompt, '&');
	or = double_strchr(prompt, '|');
	sub = ft_strchr(prompt, '(') - prompt;
	t = 0;
	if (and > 0 && (and < or || or < 0) && (and < sub || sub < 0))
		t = 1;
	if (or > 0 && (or < and || and < 0) && (or < sub || sub < 0))
		t = 2;
	if (sub > 0 && (sub < and || and < 0) && (sub < or || or < 0))
		t = 3;
	if (t != 0)
		ret = (and * (t == 1)) + (or * (t == 2)) + (sub * (t == 3));
	else
		ret = ft_strchr(prompt, 0) - prompt;
	ret = avoid_quotes(prompt, ret, &t);
	if (type)
		*type = t;
	return (ret);
}
