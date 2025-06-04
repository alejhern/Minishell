/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:24:14 by pafranco          #+#    #+#             */
/*   Updated: 2025/05/19 20:18:40 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	prevalidate_export(char *var)
{
	if (!var || !var[0])
	{
		ft_printf_fd(2, "export: not enough arguments\n");
		return (1);
	}
	if (ft_strchr(var, '=') == NULL)
	{
		ft_printf_fd(2, "export: invalid variable format\n");
		return (1);
	}
	if (ft_isdigit(var[0]))
	{
		ft_printf_fd(2, "export: variable name cannot start with a digit\n");
		return (1);
	}
	if (ft_strncmp(var, "SHELL", 5) == 0)
		return (perror("export: SHELL: cannot modify environment variable\n"),
			1);
	return (0);
}

int	builtin_export(char **command, char ***env)
{
	char	*var;

	if (prevalidate_export(command[1]))
		return (1);
	var = ft_strchr(command[1], '=');
	if (var)
		*var = '\0';
	if (!ft_setenv(command[1], var + 1, env))
	{
		perror("export: cannot set environment variable");
		return (1);
	}
	return (0);
}
