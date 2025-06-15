/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amhernandez <alejhern@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:48:55 by amhernandez       #+#    #+#             */
/*   Updated: 2025/06/15 15:48:59 by amhernandez      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	create_pipe(t_redirs_manage *redirs_manage, int save_stdin,
		int save_stdout)
{
	if (redirs_manage->is_pipe)
	{
		if (pipe(redirs_manage->pipes) == -1)
		{
			perror("pipe error");
			close(save_stdin);
			close(save_stdout);
			return (-1);
		}
		if (redirs_manage->fd_in != -1)
			close(redirs_manage->fd_in);
		redirs_manage->fd_in = redirs_manage->pipes[0];
	}
	return (0);
}

static void	execute_child_process(t_command *command,
		t_redirs_manage *redirs_manage, char ***env, int *result)
{
	if (redirs_manage->is_pipe && !redirs_manage->fds_out)
		if (dup2(redirs_manage->pipes[1], STDOUT_FILENO) == -1)
			ft_perror_exit("dup2 output redirection");
	if (redirs_manage->pipes[0] != -1)
		close(redirs_manage->pipes[0]);
	if (redirs_manage->pipes[1] != -1)
		close(redirs_manage->pipes[1]);
	*result = launch_shells(command->subshell, env);
	if (*result == -1 || *result == 127 || *result == 1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

void	make_fork(t_command *command, t_redirs_manage *redirs_manage,
		char ***env, int *result)
{
	int		save_stdin;
	int		save_stdout;
	pid_t	pid;

	*result = 1;
	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (save_stdin == -1 || save_stdout == -1)
		return (perror("dup error"));
	if (create_pipe(redirs_manage, save_stdin, save_stdout) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return (perror("fork error"));
	if (pid == 0)
		execute_child_process(command, redirs_manage, env, result);
	if (redirs_manage->is_pipe)
		close(redirs_manage->pipes[1]);
	waitpid(pid, result, 0);
	if (WIFEXITED(*result))
		*result = WEXITSTATUS(*result);
	dup2(save_stdin, STDIN_FILENO);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdin);
	close(save_stdout);
}
