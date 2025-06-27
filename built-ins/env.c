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

int	builtin_env(char **command, char ***env)
{
	char	**original_env;

	if (!*env || !(*env)[0])
	{
		ft_printf_fd(STDERR_FILENO, "env: no environment variables set\n");
		return (1);
	}
	if (command[0])
		return (ft_execute(command + 1, *env, 1));
	original_env = *env;
	while (*original_env)
		ft_putendl_fd(*original_env++, STDOUT_FILENO);
	return (0);
}
