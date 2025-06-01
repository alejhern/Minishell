/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:24:24 by pafranco          #+#    #+#             */
/*   Updated: 2025/05/19 19:45:39 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(char **command, char ***env, int *fds)
{
	char	*cwd;

	if (command[1])
	{
		ft_printf_fd(STDERR_FILENO, "pwd: too many arguments\n");
		return (1);
	}
	cwd = ft_getenv("PWD", *env);
	if (!cwd)
	{
		perror("pwd: getcwd error");
		return (1);
	}
	transfer_output(fds, cwd);
	return (0);
}
