/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:58:35 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/19 19:41:52 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_cond(void *condi);

void	print_red(void *redi)
{
	t_redirect			*red;

	red = redi;
	printf("			%s   %i\n", red->path, red->is_double);
}

void	print_comm(void *com)
{
	char			**argv;
	int				i;
	t_command		*comm;

	i = -1;
	comm = com;
	printf("	Command:\n		argv:");
	if (comm->is_subshell == 0)
	{
		argv = comm->argv;
		while (argv[++i])
			printf("\n			%s", argv[i]);
	}
	else
	{
		printf("\n**************SUBSHELL_IN****************\n");
		ft_lstiter(comm->subshell, print_cond);
		printf("**************SUBSHELL_OUT***************");
	}
	printf("\n		redirect_in:\n");
	ft_lstiter(comm->redirect_in, print_red);
	printf("		redirect_out:\n");
	ft_lstiter(comm->redirect_out, print_red);
}

void	print_cond(void *condi)
{
	t_shell			*cond;

	cond = condi;
	printf("Conditional: \n	type %d\n", cond->type);
	ft_lstiter(cond->command, print_comm);
}

void	print_shell(t_list *list)
{
	ft_lstiter(list, print_cond);
}
