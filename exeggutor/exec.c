/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amhernandez <alejhern@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:57:49 by amhernandez       #+#    #+#             */
/*   Updated: 2025/06/04 13:05:13 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_builtins(char **command, char ***env)
{
	int	result_builtin;

	if (ft_strncmp(command[0], "echo", 5) == 0)
		result_builtin = builtin_echo(command);
	else if (ft_strncmp(command[0], "cd", 3) == 0)
		result_builtin = builtin_cd(command, env);
	else if (ft_strncmp(command[0], "pwd", 4) == 0)
		result_builtin = builtin_pwd(command, env);
	else if (ft_strncmp(command[0], "export", 7) == 0)
		result_builtin = builtin_export(command, env);
	else if (ft_strncmp(command[0], "unset", 6) == 0)
		result_builtin = builtin_unset(command, env);
	else if (ft_strncmp(command[0], "env", 4) == 0)
		result_builtin = builtin_env(env);
	else if (ft_strncmp(command[0], "exit", 5) == 0)
		result_builtin = builtin_exit(command);
	else
		result_builtin = -1;
	return (result_builtin);
}

static int	make_comand(t_command *command, char ***env, t_list *next,
		t_redirs_manage *redirs_manage)
{
	int	result;
	int	pipe_fd;

	result = find_builtins(command->command, env);
	if (result != -1)
		return (result);
	if (!next || redirs_manage->fds_out)
		result = ft_execute(command->command, *env, 1);
	else
	{
		pipe_fd = ft_pipe(redirs_manage->fd_in, command->command, *env);
		if (pipe_fd == -1)
			return (1);
		if (redirs_manage->fd_in != -1)
			close(redirs_manage->fd_in);
		redirs_manage->fd_in = pipe_fd;
		result = 1;
	}
	if (result == 0 || result == 127)
		return (1);
	else
		return (0);
}

static void	launch_shell_commands(t_shell *shell,
		t_redirs_manage *redirs_manage, char ***env, int *result)
{
	t_command	*command;
	t_list		*list;

	list = shell->commands;
	*result = 0;
	redirs_manage->is_pipe = 0;
	while (list)
	{
		command = list->content;
		prepare_redirects(redirs_manage, command, result);
		list = list->next;
		if (*result == 1)
			break ;
		if (command->subshell)
			*result = launch_shells(command->subshell, env);
		else
			*result = make_comand(command, env, list, redirs_manage);
		recover_fds(redirs_manage);
		redirs_manage->is_pipe = 1;
	}
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
		if (result != -1 && ((result == 0 && shell->type == OR) || (result != 0
					&& shell->type == AND)))
			break ;
		launch_shell_commands(shell, &redirs_manage, env, &result);
		list = list->next;
	}
	if (dup2(redirs_manage.save_in, STDIN_FILENO) == -1)
		ft_perror_exit("dup2 input");
	close(redirs_manage.save_in);
	return (result);
}
