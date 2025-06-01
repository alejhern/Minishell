/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:23:53 by pafranco          #+#    #+#             */
/*   Updated: 2025/05/19 20:29:30 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(char ***env, int *fds)
{
	char	*printeable;
	char	**original_env;

	if (!*env || !(*env)[0])
	{
		ft_printf_fd(STDERR_FILENO, "env: no environment variables set\n");
		return (1);
	}
	original_env = *env;
	printeable = NULL;
	while (*original_env)
	{
		printeable = ft_strappend(printeable, *original_env++);
		if (*original_env)
			printeable = ft_strappend(printeable, "\n");
		if (!printeable)
			ft_error_exit("env: memory allocation error");
	}
	transfer_output(fds, printeable);
	free(printeable);
	return (0);
}
