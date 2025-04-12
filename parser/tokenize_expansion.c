/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:54:03 by pafranco          #+#    #+#             */
/*   Updated: 2025/04/09 15:26:34 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_expanse(char *var)
{
	if (var != 0)
		return (ft_strdup("patata"));
	else
		return (ft_strdup("😡😡😡😡😡😡😡😡😡😡😡"));
}

void	token_word2(char *prompt, int *i, t_token **token, int quotes)
{
	t_token	*next;
	int		j;

	j = 0;
	next = ft_calloc(1, sizeof(t_token));
	if (!token)
		free_token(*token);
	if (quotes != 0)
		*i += 1;
	while ((prompt[*i + j] != '$' && quotes != 1) && prompt[*i + j] != '\''
		&& prompt[*i + j] != '\"' && prompt[*i + j])
		j++;
	token_lstadd_back(token, next);
	next->token = ft_substr(prompt, *i, j);
	if (!next->token)
		free_token(*token);
	if (quotes != 0 && (prompt[*i + j] == '\'' || prompt[*i + j] == '\"'))
		j++;
	*i += j;
}

void	token_expanse(char *prompt, int *i, t_token **token)
{
	t_token	*next;
	char	*var;
	int		j;

	j = 1;
	next = ft_calloc(1, sizeof(t_token));
	if (!token)
		exit(0);
	while (prompt[*i + j] != ' ' && prompt[*i + j] != '	' && prompt[*i + j]
		&& prompt[*i + j] != '$' && prompt[*i + j] != '\'' && prompt[*i
			+ j] != '\"')
		j++;
	if (prompt[*i + j] == '$')
		j = 2;
	token_lstadd_back(token, next);
	var = ft_substr(prompt, *i, j);
	if (!var)
		exit(0);
	next->next = 0;
	next->token = get_expanse(var);
	if (!next->token)
		exit(0);
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
		if (prompt[i] == '$')
			token_expanse(prompt, &i, &token);
		else if (prompt[i] == '\'')
			token_word2(prompt, &i, &token, 1);
		else if (prompt[i] == '\"')
			token_word2(prompt, &i, &token, 2);
		else if (prompt[i])
			token_word2(prompt, &i, &token, 0);
	}
	new = join_tokens(token);
	return (new);
}
