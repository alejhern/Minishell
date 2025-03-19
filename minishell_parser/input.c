/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:38:08 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/19 19:31:49 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token(t_token *token, int util)
{
	t_token				*next;

	while (token)
	{
		next = token->next;
		if (token->token)
			free(token->token);
		free(token);
		token = next;
	}
	if (util)
		exit(0);
}

void	print_token(t_token *token)
{
	char		*types;
	t_token		*aux;
	t_token		*puta;

	types = "w|o&()<>";
	puta = token;
	while (puta)
	{
		aux = puta->next;
		if (puta->token)
			printf("%s", puta->token);
		else
			printf("%c", types[puta->type]);
		puta = aux;
	}
	exit(0);
}

int	parser_input(int util)
{
	int				error;
	char			*print;
	t_list			*cond;
	t_token			*token;

	error = 0;
	while (util == 0)
	{
		error = 0;
		print = get_next_line(0);
		if (error == 0)
		{
			token = tokenize(print, &error);
			print_token(token);
			free_token(token, 0);
		}
		else
			printf("Syntax error!");
		free(print);
	}
//						0         10        20        30        40        50        60        70
	token = tokenize("puta >> joder < hostia && patata | a | aaaa > a && puta | (puta espanya | (joder tot << aqui > alla))", &error);
//	token = tokenize("puta a", &error);
//	print_token(token);
	cond = token_parser(token, &error);
	print_shell(cond);
//	free_token(token, 0);
	free_shell(cond);
	return (0);
}
