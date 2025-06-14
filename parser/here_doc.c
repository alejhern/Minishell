/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:11:31 by pafranco          #+#    #+#             */
/*   Updated: 2025/06/14 18:11:18 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc(char **token, int util, char **env)
{
	char		*in;
	char		*ret;
	char		*eof;

	util = 0;
	eof = *token;
	eof = quote_remover(eof, 0);
	ret = ft_strdup("");;
	while (!util)
	{
		in = readline("> ");
		if (g_signal != 0)
			return (free(ret));
		if (ft_strncmp(in, eof, INT_MAX) == 0)
			util = 1;
		else
			ret = ft_strjoin_free(ret, ft_strjoin_free(in, "\n", 1), 3);
	}
	if (ret != 0 && ft_strchr(ret, '$')
			&& (ft_strchr(*token, '\'') == 0 || ft_strchr(*token, '\"') == 0))
		ret = expand(ret, env, 1);
	free(*token);
	*token = ret;
}
