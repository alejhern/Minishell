/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:54:03 by pafranco          #+#    #+#             */
/*   Updated: 2025/05/12 19:07:22 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//this is a placeholder funtion, it will get removed later, therefore it's fine that i go over the 5 function limit
char	*get_expanse(char *var)
{
	if (var != 0)
		return (ft_strdup("patata"));
	else
		return (ft_strdup("😡😡😡😡😡😡😡😡😡😡😡"));
}

void	token_word2_util(int *j, int *k)
{
	*j += 1;
	*k += 1;
}

void	token_expanse(char *p, int *i, int *j, t_token **token)
{
	t_token	*next;
	char	*var;
	int		k;

	k = 1;
	next = ft_calloc(1, sizeof(t_token));
	if (!next)
		exit(0);
	while (p[*i + *j + k] != ' ' && p[*i + *j + k] != '	' && p[*i + *j + k]
		&& p[*i + *j + k] != '$' && p[*i + *j + k] != '\''
		&& p[*i + *j + k] != '\"')
		k++;
	if (p[*i + *j + 1] == '$')
		k = 2;
	token_lstadd_back(token, next);
	var = ft_substr(p, *i + *j, k);
	if (!var)
		exit(0);
	next->next = 0;
	next->token = get_expanse(var);
	if (!next->token)
		exit(0);
	*j += k;
}

void	token_word2(char *prompt, int *i, t_token **token, int quotes)
{
	t_token	*next;
	int		j;
	int		k;

	j = 0;
	k = 0;
	next = ft_calloc(1, sizeof(t_token));
	token_lstadd_back(token, next);
	if (!token)
		free_token(*token);
	if (quotes != 0)
		*i += 1;
	while (prompt[*i + j] != '\'' && prompt[*i + j] != '\"' && prompt[*i + j])
	{
		if (prompt[*i + j] == '$' && quotes != 1)
			token_expanse(prompt, i, &j, token);
		else
			token_word2_util(&j, &k);
	}
	next->token = ft_substr(prompt, *i, k);
	if (!next->token)
		free_token(*token);
	if (quotes != 0)
		j++;
	*i += j;
}

char	*join_tokens(t_token *token)
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

char	*expand(char *prompt)
{
	int		i;
	char	*new;
	t_token	*token;

	i = 0;
	token = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'')
			token_word2(prompt, &i, &token, 1);
		else if (prompt[i] == '\"')
			token_word2(prompt, &i, &token, 2);
		else if (prompt[i])
			token_word2(prompt, &i, &token, 0);
	}
	new = join_tokens(token);
	return (new);
}
