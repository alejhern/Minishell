/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amhernandez <alejhern@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:57:49 by amhernandez       #+#    #+#             */
/*   Updated: 2025/06/27 21:00:52 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_builtins(char **command, char ***env, t_redirs_manage *redirs_manage)
{
	int	result_builtin;

	if (ft_strncmp(command[0], "echo", 5) == 0)
		result_builtin = builtin_fork(command, redirs_manage, env,
				builtin_echo);
	else if (ft_strncmp(command[0], "cd", 3) == 0)
		result_builtin = builtin_fork(command, redirs_manage, env, builtin_cd);
	else if (ft_strncmp(command[0], "pwd", 4) == 0)
		result_builtin = builtin_fork(command, redirs_manage, env, builtin_pwd);
	else if (ft_strncmp(command[0], "export", 7) == 0)
		result_builtin = builtin_fork(command, redirs_manage, env,
				builtin_export);
	else if (ft_strncmp(command[0], "unset", 6) == 0)
		result_builtin = builtin_fork(command, redirs_manage, env,
				builtin_unset);
	else if (ft_strncmp(command[0], "env", 4) == 0)
		result_builtin = builtin_fork(command, redirs_manage, env, builtin_env);
	else if (ft_strncmp(command[0], "exit", 5) == 0)
		result_builtin = builtin_fork(command, redirs_manage, env,
				builtin_exit);
	else if (ft_strncmp(command[0], "history", 8) == 0)
		result_builtin = builtin_fork(command, redirs_manage, env, history);
	else
		result_builtin = -1;
	return (result_builtin);
}

static int	make_comand(t_command *command, char ***env,
		t_redirs_manage *redirs_manage)
{
	int	result;
	int	pipe_fd;

	result = find_builtins(command->command, env, redirs_manage);
	if (result != -1)
		return (result);
	if (!redirs_manage->is_pipe || redirs_manage->fds_out)
	{
		signal(SIGINT, signal_handler_fork);
		result = ft_execute(command->command, *env, &command->pid);
		signal(SIGINT, signal_handler_main);
		if (redirs_manage->is_pipe)
			redirs_manage->forced_pipe = 1;
		else
			waitpid(command->pid, NULL, 0);
	}
	else
	{
		pipe_fd = ft_pipe(redirs_manage->fd_in, command->command, *env,
				&command->pid);
		if (pipe_fd == -1)
			return (1);
		if (redirs_manage->fd_in != -1)
			close(redirs_manage->fd_in);
		redirs_manage->fd_in = pipe_fd;
		result = 0;
	}
	return (result);
}

static void	wait_pids(t_list *list, int *error)
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

static void	launch_shell_commands(t_shell *shell,
		t_redirs_manage *redirs_manage, char ***env, int *result)
{
	t_command	*command;
	t_list		*list;

	list = shell->commands;
	redirs_manage->is_pipe = 0;
	redirs_manage->forced_pipe = 0;
	while (list)
	{
		*result = 0;
		command = list->content;
		prepare_redirects(redirs_manage, command, result, env);
		list = list->next;
		redirs_manage->is_pipe = (list != NULL);
		if (*result == 1 || *result == 2)
			break ;
		if (command->subshell)
			make_fork(command, redirs_manage, env, result);
		else if (command->command)
			*result = make_comand(command, env, redirs_manage);
		recover_fds(redirs_manage);
		redirs_manage->is_pipe = 1;
	}
	wait_pids(list, result);
}

int	launch_shells(t_list *shells, char ***env)
{
	t_list			*list;
	t_shell			*shell;
	int				result;
	t_redirs_manage	redirs_manage;

	list = shells;
	result = -1;
	redirs_manage.save_in = dup(STDIN_FILENO);
	while (list)
	{
		shell = list->content;
		if ((result != -1 && ((result == 0 && shell->type == OR) || (result != 0
						&& shell->type == AND))) || result == 2)
			break ;
		launch_shell_commands(shell, &redirs_manage, env, &result);
		list = list->next;
	}
	if (dup2(redirs_manage.save_in, STDIN_FILENO) == -1)
		ft_perror_exit("dup2 input");
	close(redirs_manage.save_in);
	return (result);
}
