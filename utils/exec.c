/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejhern <alejhern@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:41:42 by alejhern          #+#    #+#             */
/*   Updated: 2025/06/29 14:27:48 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_exec_process(t_command *command, t_redirs_manage *redirs_manage,
		char ***env, int *error)
{
	signal(SIGINT, signal_handler_fork);
	*error = ft_execute(command->command, *env, &command->pid);
	if (redirs_manage->is_pipe)
		redirs_manage->forced_pipe = 1;
	else if (*error  != 127)
	{
		waitpid(command->pid, error, 0);
		if (WIFEXITED(*error))
			*error = WEXITSTATUS(*error);
	}
}

void	pipe_exec_process(t_command *command, t_redirs_manage *redirs_manage,
		char ***env, int *error)
{
	int	pipe_fd;

	pipe_fd = ft_pipe(redirs_manage->fd_in, command->command, *env,
			&command->pid);
	if (pipe_fd == -1)
		return (*error = 1, (void)0);
	if (redirs_manage->fd_in != -1)
		close(redirs_manage->fd_in);
	redirs_manage->fd_in = pipe_fd;
	*error = 0;
}

void	wait_pids(t_list *list, int *error)
{
	t_list		*aux;
	t_command	*command;
	int			status;

	aux = list;
	status = 0;
	while (aux)
	{
		command = aux->content;
		aux = aux->next;
		waitpid(command->pid, &status, 0);
	}
	if (*error != 0)
		return ;
	if (WIFEXITED(status))
		*error = WEXITSTATUS(status);
}
