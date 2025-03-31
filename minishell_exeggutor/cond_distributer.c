/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cond_distributer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:19:02 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/31 19:07:22 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	piping_function(t_list *list, int *error)//placeholder name
{
	//TODO
	//This is goinng to do some sick pipes 🛹
	//TODO
	printf("Pipepification\n");
	return (list == 0);
}

int	read_conditional(t_list *list)
{
	int					result;
	int					error;
	t_shell				*cond;

	cond = list->content;
	while (list != 0 && list->content != 0)
	{
		result = piping_function(cond->command, &error);
		if ((cond->type == AND) || (result == 0 && cond->type == OR))
		{
			list = list->next;
			cond = list->content;
		}
		else if (cond->type == END)
			list = 0;
		else
			while (result == 1 && cond->type == OR)
			{
				list = list->next;
				cond = list->content;
			}
	}
	return (error);
}
