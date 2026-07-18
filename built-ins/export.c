/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:24:14 by pafranco          #+#    #+#             */
/*   Updated: 2025/06/20 22:57:09 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int valid_identifier(char *s)
{
    int i;

    if (!ft_isalpha(s[0]) && s[0] != '_')
        return (0);
    i = 1;
    while (s[i] && s[i] != '=')
    {
        if (!ft_isalnum(s[i]) && s[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

static int	prevalidate_export(char *var)
{
	if (!var || !var[0])
	{
		ft_putendl_fd("export: not enough arguments", STDERR_FILENO);
		return (1);
	}
	if (ft_isdigit(var[0]))
	{
		ft_putendl_fd("export: variable name cannot start with a digit", 2);
		return (1);
	}
	if (ft_strncmp(var, "SHELL", 5) == 0)
	{
		ft_putendl_fd("export: SHELL: cannot modify environment variable",
			STDERR_FILENO);
		return (1);
	}
	if (!valid_identifier(var))
	{
		ft_putendl_fd("not a valid identifier", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	builtin_export(char **command, char ***env)
{
	char	*equal;
	char	*value;
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (command[++i])
	{
		if (prevalidate_export(command[i]))
			return (1);
		equal = ft_strchr(command[i], '=');
		if (!equal)
			continue ;
		*equal = '\0';
		value = ft_strtrim(equal + 1, "\"");
		if (!value)
			exit(0);
		status = !ft_setenv(command[i], value, env);
		free(value);
		*equal = '=';
	}
	return (status);
}
