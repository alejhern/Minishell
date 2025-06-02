/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:23:42 by pafranco          #+#    #+#             */
/*   Updated: 2025/05/30 17:52:00 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_flag(char *flag)
{
	int	i;

	i = 1;
	if (flag[0] != '-')
		return (0);
	while (flag[i])
		if (flag[i++] == 'n')
			return (1);
	return (0);
}

int	builtin_echo(char **command, int *fds)
{
	char	jump;
	char	*printeable;
	char	*print_no_quote;

	command++;
	jump = is_flag(*command + 1);
	if (jump)
		command++;
	printeable = NULL;
	while (*command)
	{
		printeable = ft_strappend(printeable, *command++);
		if (command + 1)
			printeable = ft_strappend(printeable, " ");
	}
	if (jump)
		printeable = ft_strappend(printeable, "\n");
	print_no_quote = ft_strtrim(printeable, "\"\'");
	if (!print_no_quote)
		ft_error_exit("echo: memory allocation error");
	transfer_output(fds, print_no_quote);
	free(printeable);
	free(print_no_quote);
	return (0);
}
