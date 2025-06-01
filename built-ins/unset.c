/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:24:31 by pafranco          #+#    #+#             */
/*   Updated: 2025/05/21 17:36:20 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(char **command, char ***env)
{
	if (!command[1])
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return (1);
	}
	if (ft_strncmp(command[1], "SHELL", 5) == 0)
	{
		ft_putstr_fd("unset: cannot unset environment variable\n", 2);
		return (1);
	}
	if (!ft_unsetenv(command[1], env))
		return (1);
	return (0);
}
