/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amhernandez <alejhern@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:57:49 by amhernandez       #+#    #+#             */
/*   Updated: 2025/05/21 18:23:38 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_builtin(char **command, char **env, int (*f)(char **cmd, char **env))
{
	pid_t	pid;
	int		status;

	pid = 0;
	pid = fork();
	if (pid == -1)
		return (perror("fork failed"), 0);
	else if (pid == 0)
	{
		if (f(command, env) == -1)
		{
			perror("Cannot execute command");
			return (0);
		}
	}
	else
		waitpid(pid, &status, 0);
	return (1);
}

int	find_builtins(char **command, char **env, int *result)
{
	if (ft_strncmp(command[0], "echo", 4) == 0)
		exec_builtin(command, env, mini_echo);
	else if (ft_strncmp(command[0], "cd", 2) == 0)
		exec_builtin(command, env, mini_cd);
	else if (ft_strncmp(command[0], "pwd", 3) == 0)
		exec_builtin(command, env, mini_pwd);
	else if (ft_strncmp(command[0], "export", 6) == 0)
		exec_builtin(command, env, mini_export);
	else if (ft_strncmp(command[0], "unset", 5) == 0)
		exec_builtin(command, env, mini_unset);
	else if (ft_strncmp(command[0], "env", 3) == 0)
		exec_builtin(command, env, mini_env);
	else if (ft_strncmp(command[0], "exit", 4) == 0)
		exit(0);
	else
		return (0);
	*result = 1;
	return (1);
}

static int	launch_shell_commands(t_shell *shell, char **env)
{
	t_list		*commands;
	t_command	*command;
	int			result;

	commands = shell->commands;
	result = -1;
	while (commands)
	{
		command = commands->content;
        if (command->subshell)
            result = launch_commands(command->subshell, env);
		else if (find_builtins(command->command, env, &result) == 0)
            result = ft_execute(command->command, env, 1);
		commands = commands->next;
	}
	return (result);
}

int	launch_commands(t_list *shells, char **env)
{
	t_list	*list;
	t_shell	*shell;
	int		result;

	list = shells;
	result = 0;
	while (list != NULL)
	{
		shell = list->content;
		if (result == 1 && shell->type == OR)
			break ;
		result = launch_shell_commands(shell, env);
		if (result == -1)
		{
			ft_putstr_fd("Error: command not found\n", 2);
			return (-1);
		}
		list = list->next;
	}
	return (0);
}
