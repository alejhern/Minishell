/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:08:29 by pafranco          #+#    #+#             */
/*   Updated: 2025/06/28 22:21:17 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	persist_exit_status(int status, char ***env)
{
	char	*status_str;

	status_str = ft_itoa(status);
	if (!ft_setenv("?", status_str, env))
	{
		free(status_str);
		ft_putendl_fd("export: failed to set environment variable",
			STDERR_FILENO);
		exit(0);
	}
	free(status_str);
}
