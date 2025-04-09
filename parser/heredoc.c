/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:04:40 by pafranco          #+#    #+#             */
/*   Updated: 2025/04/02 20:46:10 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc(t_token *token, t_redirect *red, int type)
{
	if (red->is_double == 0 || type == 7)
	{
		red->path = ft_strdup(token->token);
		return ;
	}
}
