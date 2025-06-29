/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:52:18 by pafranco          #+#    #+#             */
/*   Updated: 2025/06/28 22:39:18 by pafranco         ###   ########.fr       */
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

int	is_del(char c)
{
	return (c == '<' || c == '>' || c == '&' || c == '|' || c == '('
		|| c == ')');
}

void	syntax_error(t_token *token, char ***env, int *error)
{
	check_tokens(token, NULL, error, *env);
	if (*error == 0)
		return ;
	free_token(token);
	ft_printf("SYNTAX ERROR\n");
	persist_exit_status(2, env);
}
