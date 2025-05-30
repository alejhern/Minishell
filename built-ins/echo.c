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
	while (flag[i] == 'n')
		i++;
	if (flag[i] == 0)
		return (1);
	return (0);
}

int	mini_echo(char **command, char ***env)
{
	int		i;
	char	jump;

	env = env;
	i = 0;
	jump = 1;
	if (is_flag(command[i]))
	{
		jump = 0;
		i++;
	}
	while (command[++i])
	{
		ft_printf("%s", command[i]);
		if (command[i + 1])
			ft_printf(" ");
	}
	if (jump)
		ft_printf("\n");
	return (0);
}
