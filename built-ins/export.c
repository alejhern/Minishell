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

//static int	find_var(char *

int	mini_export(char **command, char ***env)
{
	char **useless;

	useless = command;
	command = *env;
	if (useless[1] == NULL)
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return (1);
	}
	exit(0);
}
