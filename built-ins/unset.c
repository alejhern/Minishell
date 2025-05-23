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

int	mini_unset(char **command, char ***env)
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
