/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:52:06 by pafranco          #+#    #+#             */
/*   Updated: 2025/06/28 22:51:03 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			g_signal = 0;

void	signal_handler_main(int sig)
{
	g_signal = sig;
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		rl_done = 1;
		rl_on_new_line();
		ft_printf("\n");
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		ft_printf("Quit:\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_handler_here(int sig)
{
	g_signal = sig;
	if (sig == SIGINT)
		rl_done = 1;
}

void	signal_handler_fork(int sig)
{
	g_signal = sig;
	ft_printf("\n");
	return ;
}
