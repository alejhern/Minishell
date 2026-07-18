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

static int	check_code(char *code)
{
	int	i;

	i = -1;
	if (code[0] == '-')
		return (0);
	if (code[0] == '+' || code[0] == '-')
		++i;
	while (code[++i])
		if (!ft_isdigit(code[i]))
			return (0);
	return (1);
}

int	builtin_exit(char **comand, char ***env)
{
	int	status;

	(void)env;
	if (!comand)
		return (EXIT_FAILURE);
	if (comand[1])
	{
		status = ft_atoi(comand[1]);
		if (status < 0)
			return (156);
		if (!check_code(comand[1]))
		{
			ft_putstr_fd("exit: invalid exit code\n", STDERR_FILENO);
			return (2);
		}
	}
	else
		status = EXIT_SUCCESS;
	if (ft_memlen(comand) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd("Bye!\n", STDOUT_FILENO);
	exit(status);
}
