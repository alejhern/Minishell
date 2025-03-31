/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:38:08 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/26 20:34:19 by pafranco         ###   ########.fr       */
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
	if (util == 0)
	{
		error = 0;
		print = get_next_line(0);
//		print = readline("shell petit: ");
		token = tokenize(print, &error);
		free(print);
	}
	else
		token = tokenize(" patata | > pata", &error);
	check_tokens(token, 0, &error);
	if (error != 0)
	{
		printf ("SYNTAX (p)ERROr🐶");
		exit(0);
	}
	cond = token_parser(token, &error, 0);
	print_shell(cond);
	free_shell(cond);
	return (0);
}
