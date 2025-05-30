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

static char	*get_printable(char *str, char **env)
{
	char	*printable;
	char	*var_env;

	printable = ft_strtrim(str, "' \t\n\"");
	if (!printable)
		return (NULL);
	if (printable[0] == '$')
	{
		var_env = ft_getenv((const char *)printable + 1, env);
		free(printable);
		if (var_env)
			return (ft_strdup(var_env));
		else
			return (NULL);
	}
	return (printable);
}

int	mini_echo(char **command, char ***env)
{
	int		i;
	char	jump;
	char	*printable;

	i = 0;
	jump = 1;
	if (is_flag(command[i]))
	{
		jump = 0;
		i++;
	}
	while (command[++i])
	{
		printable = get_printable(command[i], *env);
		ft_printf("%s", printable);
		free(printable);
		if (command[i + 1])
			ft_printf(" ");
	}
	if (jump)
		ft_printf("\n");
	return (0);
}
