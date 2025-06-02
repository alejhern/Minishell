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

int	builtin_echo(char **command)
{
	int	jump;

	command++;
	jump = ft_strncmp("-n", *command, 2);
	if (!jump)
		command++;
	while (*command)
	{
		ft_putstr_fd(*command++, STDOUT_FILENO);
		if (*command)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (jump)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
