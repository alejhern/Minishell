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

static void	launch_shell_commands(t_shell *shell, char *proyect_path,
		char ***env, int *result)
{
	t_command				*command;
	t_redirects_response	redirects_response;

	while (shell->commands)
	{
		command = shell->commands->content;
		redirects_response = prepare_redirects(command);
		shell->commands = shell->commands->next;
		if (command->subshell)
			*result = launch_shells(command->subshell, proyect_path, env);
		else
			*result = make_comand(command, env, redirects_response.fds_out);
		recover_fds(redirects_response);
	}
}

int	launch_shells(t_list *shells, char *proyect_path, char ***env)
{
	t_list	*list;
	t_shell	*shell;
	int		result;

	(void)proyect_path;
	list = shells;
	result = 1;
	while (list)
	{
		shell = list->content;
		if (result == 0 && shell->type == OR)
			break ;
		launch_shell_commands(shell, proyect_path, env, &result);
		list = list->next;
	}
	return (result);
}
