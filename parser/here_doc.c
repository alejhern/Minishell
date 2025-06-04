/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:11:31 by pafranco          #+#    #+#             */
/*   Updated: 2025/06/04 15:18:41 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc(char *eof)
{
	char		*in;
	char		*ret;
	int			util;

	in = 0;
	util = 0;
	ret = ft_safe_strdup(":)");
	while (!util)
	{
		in = readline(">");
		if (ft_strncmp(in, eof, ft_strlen(eof)) == 0)
			util = 1;
		else
			ft_strjoin_free(ret, in, 3);
		free(in);
	}
}
