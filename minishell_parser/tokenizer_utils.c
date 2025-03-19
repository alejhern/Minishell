/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:53:42 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/19 19:54:25 by pafranco         ###   ########.fr       */
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
