/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amhernandez <alejhern@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:57:49 by amhernandez       #+#    #+#             */
/*   Updated: 2025/06/29 20:10:54 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	find_builtins(char **command, char ***env,
		t_redirs_manage *redirs_manage)
{
	int	error_builtin;

	if (ft_strncmp(command[0], "echo", 5) == 0)
		error_builtin = builtin_fork(command, redirs_manage, env, builtin_echo);
	else if (ft_strncmp(command[0], "cd", 3) == 0)
		error_builtin = builtin_fork(command, redirs_manage, env, builtin_cd);
	else if (ft_strncmp(command[0], "pwd", 4) == 0)
		error_builtin = builtin_fork(command, redirs_manage, env, builtin_pwd);
	else if (ft_strncmp(command[0], "export", 7) == 0)
		error_builtin = builtin_fork(command, redirs_manage, env,
				builtin_export);
	else if (ft_strncmp(command[0], "unset", 6) == 0)
		error_builtin = builtin_fork(command, redirs_manage, env,
				builtin_unset);
	else if (ft_strncmp(command[0], "env", 4) == 0)
		error_builtin = builtin_fork(command, redirs_manage, env, builtin_env);
	else if (ft_strncmp(command[0], "exit", 5) == 0)
		error_builtin = builtin_fork(command, redirs_manage, env, builtin_exit);
	else if (ft_strncmp(command[0], "history", 8) == 0)
		error_builtin = builtin_fork(command, redirs_manage, env, history);
	else
		error_builtin = -1;
	return (error_builtin);
}

static int	make_comand(t_command *command, char ***env,
		t_redirs_manage *redirs_manage)
{
	int	error;

	error = find_builtins(command->command, env, redirs_manage);
	if (error != -1)
		return (error);
	error = 0;
	if (!redirs_manage->is_pipe || redirs_manage->fds_out)
		execute_exec_process(command, redirs_manage, env, &error);
	else
		pipe_exec_process(command, redirs_manage, env, &error);
	return (error);
}

static void	launch_shell_commands(t_shell *shell,
		t_redirs_manage *redirs_manage, char ***env, int *error)
{
	t_command	*command;
	t_list		*list;

	list = shell->commands;
	redirs_manage->is_pipe = 0;
	redirs_manage->forced_pipe = 0;
	signal(SIGINT, signal_handler_fork);
	while (list)
	{
		*error = 0;
		g_signal = 0;
		command = list->content;
		prepare_redirects(redirs_manage, command, error, env);
		list = list->next;
		redirs_manage->is_pipe = (list != NULL);
		if (*error == 1 || *error == 2)
			break ;
		if (command->subshell)
			make_fork(command, redirs_manage, env, error);
		else if (command->command)
			*error = make_comand(command, env, redirs_manage);
		recover_fds(redirs_manage);
		redirs_manage->is_pipe = 1;
	}
	wait_pids(shell->commands, error);
}

int	launch_shells(t_list *shells, char ***env)
{
	t_list			*list;
	t_shell			*shell;
	int				error;
	t_redirs_manage	redirs_manage;

	list = shells;
	error = -1;
	redirs_manage.save_in = dup(STDIN_FILENO);
	redirs_manage.fd_in = 0;
	while (list)
	{
		shell = list->content;
		if ((error != -1 && ((error == 0 && shell->type == OR) || (error != 0
						&& shell->type == AND))) || error == 2)
			break ;
		launch_shell_commands(shell, &redirs_manage, env, &error);
		list = list->next;
	}
	if (dup2(redirs_manage.save_in, STDIN_FILENO) == -1)
		ft_perror_exit("dup2 input");
	close(redirs_manage.save_in);
	if (g_signal != 0)
		error = 127 + g_signal;
	g_signal = 0;
	return (error);
}
