/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:52:06 by pafranco          #+#    #+#             */
/*   Updated: 2025/05/30 19:29:28 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			g_signal = 0;

void	signal_handler_main(int sig)
{
	g_signal = sig;
	ft_printf("\n");
	rl_done = 1;
}
