/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:24:06 by pafranco          #+#    #+#             */
/*   Updated: 2025/05/19 19:44:06 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_exit(char **comand, char ***env)
{
	(void)env;
	if (!comand)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	if (ft_memlen(comand) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (comand[1])
		exit(ft_atoi(comand[1]));
	else
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
