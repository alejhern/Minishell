/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:53:42 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/26 20:30:13 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_cond_util(int or, int and, int *error)
{
	if (or == 2)
		return (TOKEN_OR);
	else if (and == 2)
		return (TOKEN_AND);
	else if (or == 1)
		return (TOKEN_PIPE);
	else
	{
		*error = 1;
		return (-1);
	}
}

void parser_check(t_token **t_sub, t_token *t)
{
    if (!t_sub || !t)
        return; 
    if (*t_sub)
    {
        // Free existing token content if needed
        free((*t_sub)->token);
        free(*t_sub);
    }   
    *t_sub = t;
}