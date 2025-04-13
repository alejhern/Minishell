/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amhernandez <alejhern@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:54:37 by amhernandez       #+#    #+#             */
/*   Updated: 2025/04/13 17:54:53 by amhernandez      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	child_process(int pipe_fd[2], const char *cmd)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	execlp(cmd, cmd, (char *)NULL);
	perror("execlp");
	exit(1);
}

static char	*parent_process(int pipe_fd[2], pid_t pid)
{
	char	*output;
	char	*line;
	int		status;

	close(pipe_fd[1]);
	output = ft_calloc(1, sizeof(char));
	if (!output)
		return (NULL);
	line = get_next_line(pipe_fd[0]);
	if (!line)
		return (free(output), NULL);
	while (line)
	{
		output = ft_strappend(output, line);
		if (!output)
			return (free(line), NULL);
		free(line);
		line = get_next_line(pipe_fd[0]);
	}
	close(pipe_fd[0]);
	waitpid(pid, &status, 0);
	return (output);
}

char	*capture_output(const char *cmd)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	*output;

	output = NULL;
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), NULL);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), NULL);
	if (pid == 0)
		child_process(pipe_fd, cmd);
	else
		output = parent_process(pipe_fd, pid);
	return (output);
}
