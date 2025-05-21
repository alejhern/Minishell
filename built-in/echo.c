/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:23:42 by pafranco          #+#    #+#             */
/*   Updated: 2025/05/21 18:25:38 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int is_flag(char *flag)
{
	int			i;

	i = 1;
	if (flag[0] != '-')
		return (0);
	while (flag[i] == 'n')
		i++;
	if (flag[i] == 0)
		return (1);
	return (0);
}

int	mini_echo(char **command, char **env)
{
	char		**useless;
	int			i;
	char		jump;
	char		space;

	useless = env;
	i = 1;
	jump = '\n';
	space = 0;
	while (is_flag(command[i]) == 1)
	{
		jump  = 0;
		i++;
	}
	while (command[i] != 0)
	{
		ft_printf("%c%s", space, command[i]);
		space = ' ';
		i++;
	}
	printf("%c", jump);
	return (0);
	exit(0);
}
