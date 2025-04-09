/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:38:08 by pafranco          #+#    #+#             */
/*   Updated: 2025/04/09 17:31:53 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

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
	int				stop;
	int				error;
	char			*print;
	t_list			*cond;
	t_token			*token;

	error = 0;
	stop = 0;
	while (stop == 0)
	{
		if (util == 0)
		{
			error = 0;
			print = readline("shell petit: ");
			token = tokenize(print, &error);
		//	add_to_history(print);
		}
		else
		{
			token = tokenize("peta\"$pata\"", &error);
			stop++;
		}
		check_tokens(token, 0, &error);
		if (error != 0)
		{
			printf ("SYNTAX (p)ERROr🐶");
			exit(0);
		}
		cond = token_parser(token, &error, 0);
		print_shell(cond);
		free_shell(cond);
	}
	return (0);
}
