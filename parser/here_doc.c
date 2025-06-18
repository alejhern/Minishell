/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:11:31 by pafranco          #+#    #+#             */
/*   Updated: 2025/06/18 17:33:49 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	here_doc_fd(char *eof, char **env, int fd)
{
	char		*in;
	char		*ret;
	int			quotes;
	int			util;

	util = 0;
	quotes = (ft_strchr(eof, '\'') == 0 || ft_strchr(eof, '\"') == 0);
	eof = quote_remover(ft_strdup(eof), 0);
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
	if (ret != 0 && ft_strchr(ret, '$') &&quotes == 1)
		ret = expand(ret, env, 1);
	write(fd, ret, ft_strlen(ret));
	free(ret);
}

int	here_doc(char *eof, char **env)
{
	int			fd[2];

	if (pipe(fd) == -1)
		ft_perror_exit("Error generating pipe");
	here_doc_fd(eof, env, fd[1]);
	close(fd[1]);
	return(fd[0]);
}
