/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amhernandez <alejhern@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:57:49 by amhernandez       #+#    #+#             */
/*   Updated: 2025/05/14 18:38:22 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	launch_commands(t_list *shells, char **env)
{
	t_list		*list;
	t_shell		*shell;
	t_list		*commands;
	t_command	*command;

	list = shells;
	while (list != NULL)
	{
		shell = list->content;
		commands = shell->commands;
		while (commands)
		{
			command = commands->content;
			ft_execute(command->command, env, 1);
			commands = commands->next;
		}
		list = list->next;
	}
	return (0);
}
