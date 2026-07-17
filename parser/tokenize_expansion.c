/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:54:03 by pafranco          #+#    #+#             */
/*   Updated: 2025/06/27 19:17:06 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*token_expand_var(char *p, int *i, char **env)
{
	char	*var;
	char	*exp;
	int		k;

	k = 0;
	while (ft_isalnum(p[*i + i[1] + 1 + k]) || p[*i + i[1] + 1 + k] == '_')
		k++;
	if (k == 0)
	{
		exp = ft_strdup("$");
		i[1]++;
	}
	else
	{
		var = ft_substr(p, *i + i[1] + 1, k);
		exp = ft_getenv(var, env);
		free(var);
		if (exp)
			exp = ft_strdup(exp);
		else
			exp = ft_strdup("");
		i[1] += k + 1;
	}
	return (exp);
}

static void	token_expanse(char *p, int *i, t_token **token, char **env)
{
	char	*exp;
	t_token	*next;

	if (p[*i + i[1] + 1] == '?')
	{
		exp = ft_itoa(g_signal);
		if (!exp)
			exit(0);
		i[1] += 2;
		next = token_lstnew(exp, 0);
		if (!next)
			exit(0);
		token_lstadd_back(token, next);
		return ;
	}
	exp = token_expand_var(p, i, env);
	if (exp)
	{
		next = token_lstnew(exp, 0);
		if (!next)
			exit(0);
		token_lstadd_back(token, next);
	}
}

static void	token_word2(char *p, int *i, t_token **token, char **env)
{
	int		k;
	t_token	*next;

	next = token_lstnew(0, 0);
	i[1] = 0;
	k = 0;
	*i += (i[2] > 0);
	token_lstadd_back(token, next);
	while ((i[3] == 1 || ((p[*i + i[1]] != '\'' || i[2] == 2) && (p[*i
					+ i[1]] != '"' || i[2] == 1))) && p[*i + i[1]])
	{
		if (p[*i + i[1]] == '$' && i[2] != 1)
		{
			next->token = ft_substr(p, *i + k, i[1] - k);
			token_expanse(p, i, token, env);
			next = token_lstnew(0, 0);
			token_lstadd_back(token, next);
			k = i[1];
		}
		else
			i[1]++;
	}
	next->token = ft_substr(p, *i + k, i[1] - k);
	i[1] += (i[2] != 0);
	*i += i[1];
}

static char	*join_tokens(t_token *token)
{
	t_token	*aux;
	char	*new;
	char	*temp;

	new = 0;
	while (token)
	{
		aux = token->next;
		temp = ft_strjoin(new, token->token);
		if (!temp)
			exit(0);
		if (new)
			free(new);
		free(token->token);
		free(token);
		token = aux;
		new = temp;
	}
	return (new);
}

char	*expand(char *prompt, char **env, int doc)
{
	int i[4];
	char *new;
	t_token *token;

	i[0] = 0;
	i[1] = 0;
	i[3] = doc;
	token = 0;
	while (prompt[i[0]])
	{
		i[2] = (prompt[i[0]] == '\'') + ((prompt[i[0]] == '\"') * 2) - doc * 3;
		if (prompt[i[0]] == '\'' && doc == 0)
			token_word2(prompt, i, &token, env);
		else if (prompt[i[0]] == '\"' && doc == 0)
			token_word2(prompt, i, &token, env);
		else if (prompt[i[0]])
			token_word2(prompt, i, &token, env);
	}
	new = join_tokens(token);
	return (new);
}
