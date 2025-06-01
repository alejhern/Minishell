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

int	find_builtins(char **command, char ***env, int *fds)
{
	int	result_builtin;

	if (ft_strncmp(command[0], "echo", 5) == 0)
		result_builtin = builtin_echo(command, fds);
	else if (ft_strncmp(command[0], "cd", 3) == 0)
		result_builtin = builtin_cd(command, env, fds);
	else if (ft_strncmp(command[0], "pwd", 4) == 0)
		result_builtin = builtin_pwd(command, env, fds);
	else if (ft_strncmp(command[0], "export", 7) == 0)
		result_builtin = builtin_export(command, env);
	else if (ft_strncmp(command[0], "unset", 6) == 0)
		result_builtin = builtin_unset(command, env);
	else if (ft_strncmp(command[0], "env", 4) == 0)
		result_builtin = builtin_env(env, fds);
	else if (ft_strncmp(command[0], "exit", 5) == 0)
		result_builtin = builtin_exit(command);
	else
		result_builtin = -1;
	return (result_builtin);
}

static int	make_comand(t_command *command, char ***env, int *fds_out)
{
	int		result;
	char	*output;

	result = find_builtins(command->command, env, fds_out);
	if (result != -1)
		return (result);
	output = ft_exec_catch(command->command, *env);
	transfer_output(fds_out, output);
	if (!output)
		return (1);
	free(output);
	return (0);
}

static int	prepare_and_launch(t_command *command, char ***env)
{
	int	result;
	int	*fds_out;
	int	fd_in;

	fd_in = get_input_file(command->redirect_in);
	fds_out = get_output_files(command->redirect_out);
	result = make_comand(command, env, fds_out);
	if (fd_in != -1)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			ft_perror_exit("Error redirecting input");
		close(fd_in);
	}
	free(fds_out);
	return (result);
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
			result = prepare_and_launch(command, env);
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
