/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:52:18 by pafranco          #+#    #+#             */
/*   Updated: 2025/04/12 14:07:59 by amhernandez      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_cond_util(int or, int and, int *error, t_token *next)
{
	if (or == 1 && and == 0)
		return (1);
	else if (or == 2 && and == 0)
		return (2);
	else if (or == 0 && and == 2)
		return (3);
	else if (or == 0 && and == 1)
	{
		next->token = ft_strdup("&");
		return (0);
	}
	*error = 1;
	return (0);
}

void	parser_check(t_token **t_sub, t_token *t)
{
	if (t_sub != 0 && t != 0)
		*t_sub = t;
}

int	remove_quotes(t_token *token)
{
	char	*str;

	str = ft_substr(token->token, 1, ft_strlen(token->token) - 2);
	free(token->token);
	token->token = str;
	return (0);
}

void	heredoc(t_token *token, t_redirect *red, int type)
{
	if (red->is_double == 0 || type == OUT_RED)
	{
		red->path = ft_strdup(token->token);
		token->type = PASS;
		return ;
	}
}

int	is_del(char c)
{
	return (c == '<' || c == '>' || c == '&' || c == '|' || c == '('
		|| c == ')');
}
