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
		ft_putendl_fd("export: not enough arguments", STDERR_FILENO);
		return (1);
	}
	if (ft_strchr(var, '=') == NULL)
	{
		ft_putendl_fd("export: invalid variable format", STDERR_FILENO);
		return (1);
	}
	if (ft_isdigit(var[0]))
	{
		ft_putendl_fd("export: variable name cannot start with a digit", 2);
		return (1);
	}
	if (ft_strncmp(var, "SHELL", 5) == 0)
	{
		ft_putendl_fd("export: SHELL: cannot modify environment variable", STDERR_FILENO);
		return	(1);
	}
	return (0);
}

int	builtin_export(char **command, char ***env)
{
	char	*var;
	char	*value;

	if (prevalidate_export(command[1]))
		return (1);
	var = ft_strchr(command[1], '=');
	if (var)
		*var = '\0';
	value = ft_strtrim(var + 1, "\"");
	if (!value)
	{
		ft_putendl_fd("export: memory allocation error", STDERR_FILENO);
		return (1);
	}
	if (!ft_setenv(command[1], value, env))
	{
		free(value);
		ft_putendl_fd("export: failed to set environment variable", STDERR_FILENO);
		return (1);
	}
	free(value);
	return (0);
}
