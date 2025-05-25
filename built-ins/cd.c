/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:23:31 by pafranco          #+#    #+#             */
/*   Updated: 2025/05/19 20:08:14 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_env_path(char *var, char **env)
{
	char	*value;

	value = ft_getenv(var, env);
	if (!value)
	{
		ft_printf_fd(2, "cd: %s not set\n", var);
		return (NULL);
	}
	return (ft_strdup(value));
}

static char	*handle_tilde_path(char *path, char **env)
{
	char	*home;
	char	*new_path;

	home = get_env_path("HOME", env);
	if (!home)
		return (NULL);
	if (path[1] == '\0' || path[1] == '/')
	{
		if (path[1] == '/')
			new_path = ft_strjoin(home, path + 1);
		else
			new_path = ft_strdup(home);
	}
	else
	{
		ft_putstr_fd("cd: ~USER not implemented\n", 2);
		free(home);
		return (NULL);
	}
	free(home);
	return (new_path);
}

static char	*get_new_path(char **command, char **env)
{
	if (!command[1] || !command[1][0] || (ft_strncmp(command[1], "--", 3) == 0))
		return (get_env_path("HOME", env));
	else if (ft_strncmp(command[1], "-", 2) == 0)
	{
		ft_putendl_fd(ft_getenv("OLDPWD", env), 1);
		return (get_env_path("OLDPWD", env));
	}
	else if (ft_strncmp(command[1], ".", 2) == 0 || ft_strncmp(command[1], "..",
			3) == 0)
		return (ft_strdup(command[1]));
	else if (ft_strncmp(command[1], "~", 1) == 0)
		return (handle_tilde_path(command[1], env));
	else
		return (ft_strdup(command[1]));
}

static int	change_directory(char *new_path, char ***env)
{
	char	*old_path;

	old_path = getcwd(NULL, 0);
	if (!old_path)
	{
		perror("cd: getcwd error");
		return (1);
	}
	if (chdir(new_path) == -1)
	{
		ft_printf_fd(2, "cd: no such file or directory: %s\n", new_path);
		free(old_path);
		return (1);
	}
	if (!ft_setenv("OLDPWD", old_path, env))
		ft_putstr_fd("cd: failed to set OLDPWD\n", 2);
	free(old_path);
	old_path = getcwd(NULL, 0);
	if (!old_path || !ft_setenv("PWD", old_path, env))
		ft_putstr_fd("cd: failed to set PWD\n", 2);
	free(old_path);
	return (0);
}

int	mini_cd(char **command, char ***env)
{
	char	*new_path;
	int		ret;

	new_path = get_new_path(command, *env);
	if (!new_path)
		return (1);
	ret = change_directory(new_path, env);
	if (ret != 0)
	{
		free(new_path);
		return (ret);
	}
	free(new_path);
	return (0);
}
