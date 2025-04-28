/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amhernandez <alejhern@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:46:39 by amhernandez       #+#    #+#             */
/*   Updated: 2025/04/12 13:46:42 by amhernandez      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_token(t_token *token)
{
	char	*types;
	t_token	*aux;
	t_token	*puta;

	types = "w|o&()<>";
	puta = token;
	while (puta)
	{
		aux = puta->next;
		if (puta->token)
			ft_printf("%s", puta->token);
		else
			ft_printf("%c", types[puta->type]);
		puta = aux;
	}
}

void	print_red(void *content)
{
	t_redirect	*red;

	red = content;
	ft_printf("\t\t\t%s", red->path);
	if (red->is_double)
		ft_putstr_fd(" append", STDOUT_FILENO);
	ft_putendl_fd("", STDOUT_FILENO);
}

void	print_comand(void *content)
{
	char		**str_comand;
	int			i;
	t_command	*comand;

	i = -1;
	comand = content;
	ft_printf("	Command:\n		comand:");
	if (comand->comand)
	{
		str_comand = comand->comand;
		while (comand && str_comand[++i])
			ft_printf(" %s", str_comand[i]);
	}
	else if (comand->subshell)
	{
		ft_printf("\n**************SUBSHELL_IN****************\n");
		ft_lstiter(comand->subshell, print_shell);
		ft_printf("**************SUBSHELL_OUT***************");
	}
	ft_printf("\n		redirect_in:\n");
	ft_lstiter(comand->redirect_in, print_red);
	ft_printf("		redirect_out:\n");
	ft_lstiter(comand->redirect_out, print_red);
}

void	print_shell(void *content)
{
	t_shell	*shell;

	shell = content;
	ft_printf("Conditional: \n	type %d\n", shell->type);
	ft_lstiter(shell->commands, print_comand);
}
