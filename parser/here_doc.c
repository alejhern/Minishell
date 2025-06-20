/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:11:31 by pafranco          #+#    #+#             */
/*   Updated: 2025/06/20 23:12:54 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	here_doc_fd(char *eof, char **env, int fd, int error)
{
	char		*in;
	char		*ret;
	int			quotes;
	int			util;

	util = 0;
	quotes = (ft_strchr(eof, '\'') != 0 || ft_strchr(eof, '\"') != 0);
	eof = quote_remover(ft_strdup(eof), 0);
	while (!util)
	{
		in = readline("> ");
		if (g_signal != 0)
		{
			g_signal = 0;
			write(error, "e", 1);
			exit(0);
		}
		if (ft_strncmp(in, eof, INT_MAX) == 0)
			break ;
		else if (in != 0 && ft_strchr(in, '$') && quotes == 0)
			in = expand(in, env, 1);
		ret = ft_strjoin_free(in, "\n", 1);
		write(fd, ret, ft_strlen(ret));
	}
	free(eof);
}

static void	here_child(char *eof, char **env, int *fd, int *error)
{
	close(fd[0]);
	close(error[0]);
	signal(SIGINT, signal_handler_here);
	here_doc_fd(eof, env, fd[1], error[1]);
	signal(SIGINT, signal_handler_main);
	close(fd[1]);
	close(error[1]);
	exit(0);
}

int	here_doc(char *eof, char **env)
{
	int			fd[2];
	int			error[2];
	int			id;
	char		ret;

	if (pipe(fd) == -1)
		ft_perror_exit("Error generating pipe");
	if (pipe(error) == -1)
		ft_perror_exit("Error generating pipe");
	id = fork();
	if (id == 0)
		here_child(eof, env, fd, error);
	close(fd[1]);
	close(error[1]);
	read(error[0], &ret, sizeof(char));
	if (ret == 'e')
	{
		g_signal = 0;
		return (-2);
	}
	close(error[0]);
	return (fd[0]);
}
