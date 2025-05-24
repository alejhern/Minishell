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

int	mini_env(char **command, char ***env)
{
	int			i;

	command = *env;
	while (*command)
	{
		i = 0;
		while ((*command)[i] && (*command)[i] != '=')
			i++;
		if (i > 0)
			ft_printf("%s", *command);
		if ((*command)[i] == '=')
			ft_printf("=%s", &(*command)[i + 1]);
		ft_printf("\n");
		command++;
	}
	return (0);	
}
