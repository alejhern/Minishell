/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amhernandez <alejhern@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:57:49 by amhernandez       #+#    #+#             */
/*   Updated: 2025/04/12 16:57:51 by amhernandez      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	launch_shell_commands(t_shell *shell, char ***env)
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
		else
            result = ft_execute(command->command, *env, 1);
		commands = commands->next;
	}
	return (result);
}

int	launch_commands(t_list *shells, char ***env)
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
