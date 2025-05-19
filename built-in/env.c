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

int	mini_env(char **command, char **env)
{
	char		**useless;
	int			i;

	useless = command;
	command = env;
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	exit(0);
}
