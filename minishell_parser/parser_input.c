/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:58:35 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/04 15:41:38 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_red(t_redirect *red)
{
	while (red)
	{
		printf("			%s   %i\n", red->path, red->is_double);
		red = red->next;
	}
}

void	print_comm(t_command *comm)
{
	char			**argv;
	int				i;

	i = 0;
	while (comm)
	{
		printf("	Command:\n		argv:");
		argv = comm->argv;
		while (argv[i])
		{
			printf("\n			%s", argv[i]);
			i++;
		}
		i = 0;
		printf("		redirect_in:\n");
		print_red(comm->redirect_in);
		printf("		redirect_out:\n");
		print_red(comm->redirect_out);
		comm = comm->next;
	}
}

void	print_cond(t_conditional *cond)
{
	while (cond)
	{
		printf("Conditional: \n	type %d\n", cond->type);
		print_comm(cond->command);
		cond = cond->next;
	}
}

int	parser_input(void)
{
	t_conditional		*cond;
	char				*print;

	print = get_next_line(0);
	cond = lexer_start(print);
//						0         10        20        30        40        50        60        70
//	cond = lexer_start("puta \">> joder < hostia || patata | a |\" aaaa > a (cat < b) && puta");
	print_cond(cond);
	free(print);
	free_cond(cond);
	return (0);
}
