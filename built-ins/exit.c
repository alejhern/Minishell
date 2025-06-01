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

int	builtin_exit(char **comand)
{
	if (ft_memlen(comand) > 2)
	{
		ft_printf_fd(STDERR_FILENO, "exit: too many arguments\n");
		return (1);
	}
	ft_printf_fd(STDOUT_FILENO, "exit\n");
	if (comand[1])
		exit(ft_atoi(comand[1]));
	else
		exit(0);
	return (0);
}
