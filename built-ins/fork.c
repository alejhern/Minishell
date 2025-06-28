/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejhern <alejhern@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:20:30 by alejhern          #+#    #+#             */
/*   Updated: 2025/06/27 19:20:32 by alejhern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	close_fork(t_redirs_manage *redirs_manage, pid_t pid)
{
	if (redirs_manage->is_pipe)
		close(redirs_manage->pipes[1]);
	waitpid(pid, NULL, 0);
	if (dup2(redirs_manage->save_out, STDOUT_FILENO) == -1)
		ft_perror_exit("restore stdout");
}

static void	close_pipes(t_redirs_manage *redirs_manage)
{
	if (redirs_manage->pipes[0] != -1)
		close(redirs_manage->pipes[0]);
	if (redirs_manage->pipes[1] != -1)
		close(redirs_manage->pipes[1]);
}

static int	fork_exeptions(char **command, char ***env,
		t_redirs_manage *redirs_manage)
{
	if (ft_strncmp(command[0], "exit", 5) == 0 && redirs_manage->is_pipe)
		return (redirs_manage->forced_pipe = 1, -1);
	else if (ft_strncmp(command[0], "exit", 5) == 0)
		return (builtin_exit(command, env));
	if (ft_strncmp(command[0], "cd", 3) == 0 && redirs_manage->is_pipe)
		return (redirs_manage->forced_pipe = 1, -1);
	else if (ft_strncmp(command[0], "cd", 3) == 0)
		return (builtin_cd(command, env));
	if (ft_strncmp(command[0], "export", 7) == 0 && redirs_manage->is_pipe)
		return (redirs_manage->forced_pipe = 1, -1);
	else if (ft_strncmp(command[0], "export", 7) == 0)
		return (builtin_export(command, env));
	if (ft_strncmp(command[0], "unset", 6) == 0 && redirs_manage->is_pipe)
		return (redirs_manage->forced_pipe = 1, -1);
	else if (ft_strncmp(command[0], "unset", 6) == 0)
		return (builtin_unset(command, env));
	return (-1);
}

int	builtin_fork(char **command, t_redirs_manage *redirs_manage, char ***env,
		int f(char **, char ***))
{
	pid_t	pid;
	int		error;

	error = fork_exeptions(command, env, redirs_manage);
	if (error != -1)
		return (error);
	error = 0;
	if (create_pipe(redirs_manage, -1, redirs_manage->save_out) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (perror("fork error"), 1);
	if (pid == 0)
	{
		if (redirs_manage->is_pipe && !redirs_manage->fds_out)
			if (dup2(redirs_manage->pipes[1], STDOUT_FILENO) == -1)
				ft_perror_exit("dup2 output redirection");
		close_pipes(redirs_manage);
		error = f(command, env);
		exit(error);
	}
	close_fork(redirs_manage, pid);
	return (error);
}
