/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:54:03 by pafranco          #+#    #+#             */
/*   Updated: 2025/06/20 23:07:54 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	token_expanse_util(char p)
{
	if (p != ' ' && p != '	' && p && p != '$' && p != '\n' && p != '\''
		&& p != '\"')
		return (1);
	return (0);
}

static void	token_expanse(char *p, int *i, t_token **token, char **env)
{
	char	*var;
	int		k;
	char	*exp;

	k = 1;
	while (token_expanse_util(p[*i + i[1] + k]))
		k++;
	if (p[*i + i[1] + 1] == '$')
		k = 2;
	if (p[*i + i[1] + k] == '\'' || p[*i + i[1] + k] == '\"'
		|| p[*i + i[1] + k] == '\n')
		k--;
	var = ft_substr(p, *i + i[1] + 1, k);
	if (!var)
		exit(0);
	exp = ft_getenv(var, env);
	free(var);
	if (exp == 0)
		exp = ft_strdup("");
	else
		exp = ft_strdup(exp);
	if (exp == 0)
		exit(0);
	token_lstadd_back(token, token_lstnew(exp, 0));
	i[1] += k;
}

static void	token_word2(char *p, int *i, t_token **token, char **env)
{
	int			k;
	t_token		*next;

	next = token_lstnew(0, 0);
	i[1] = 0;
	k = 0;
	*i += (i[2] > 0);
	token_lstadd_back(token, next);
	while ((i[3] == 1 || ((p[*i + i[1]] != '\'' && i[2] != 2)
				|| (p[*i + i[1]] != '\"' && i[2] != 1))) && p[*i + i[1]])
	{
		if (p[*i + i[1]] == '$' && i[2] != 1)
		{
			next->token = ft_substr(p, *i + k, i[1] - k);
			token_expanse(p, i, token, env);
			next = token_lstnew(0, 0);
			token_lstadd_back(token, next);
			k = i[1] + 1;
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
	int		i[4];
	char	*new;
	t_token	*token;

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
