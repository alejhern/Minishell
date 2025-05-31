/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amhernandez <alejhern@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:57:49 by amhernandez       #+#    #+#             */
/*   Updated: 2025/05/30 17:51:04 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_builtin(char **command, char ***env, int (*f)(char **cmd, char ***env))
{
	int	result;

	result = f(command, env);
	if (result == -1)
	{
		perror("Cannot execute command");
		return (1);
	}
	return (result);
}

int	find_builtins(char **command, char ***env)
{
	int	result_builtin;

	if (ft_strncmp(command[0], "echo", 5) == 0)
		result_builtin = exec_builtin(command, env, mini_echo);
	else if (ft_strncmp(command[0], "cd", 3) == 0)
		result_builtin = exec_builtin(command, env, mini_cd);
	else if (ft_strncmp(command[0], "pwd", 4) == 0)
		result_builtin = exec_builtin(command, env, mini_pwd);
	else if (ft_strncmp(command[0], "export", 7) == 0)
		result_builtin = exec_builtin(command, env, mini_export);
	else if (ft_strncmp(command[0], "unset", 6) == 0)
		result_builtin = exec_builtin(command, env, mini_unset);
	else if (ft_strncmp(command[0], "env", 4) == 0)
		result_builtin = exec_builtin(command, env, mini_env);
	else if (ft_strncmp(command[0], "exit", 5) == 0)
		exit(0);
	else
		result_builtin = -1;
	return (result_builtin);
}

static int	make_comand(t_command *command, char ***env)
{
	int		result;
	int		fd_in;
	int		*fds_out;
	char	*output;

	fd_in = -1;
	result = find_builtins(command->command, env);
	if (result != -1)
		return (result);
	fd_in = get_input_file(command->redirect_in);
	fds_out = get_output_files(command->redirect_out);
	output = ft_exec_catch(command->command, *env);
	if (fd_in != -1)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			ft_perror_exit("Error redirecting input");
		close(fd_in);
	}
	transfer_output(fds_out, output);
	ft_free_array((void ***)&fds_out);
	if (!output)
		return (1);
	free(output);
	return (0);
}

static int	launch_shell_commands(t_shell *shell, char *proyect_path,
		char ***env)
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
			result = launch_shells(command->subshell, proyect_path, env);
		else
			result = make_comand(command, env);
		commands = commands->next;
	}
	return (result);
}

int	launch_shells(t_list *shells, char *proyect_path, char ***env)
{
	t_list	*list;
	t_shell	*shell;
	int		result;

	(void)proyect_path;
	list = shells;
	result = 0;
	while (list != NULL)
	{
		shell = list->content;
		if (result == 1 && shell->type == OR)
			break ;
		result = launch_shell_commands(shell, proyect_path, env);
		if (result == -1)
		{
			ft_putstr_fd("Error: command not found\n", 2);
			return (-1);
		}
		list = list->next;
	}
	return (0);
}
