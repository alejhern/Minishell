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

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (!token)
		return ;
	free(token->token); // Libera la cadena si existe
	free(token);        // Libera la estructura t_token
}

// void	print_token(t_token *token)
// {
// 	char	*types;
// 	t_token	*aux;
// 	t_token	*puta;

// 	types = "w|o&()<>";
// 	puta = token;
// 	while (puta)
// 	{
// 		aux = puta->next;
// 		if (puta->token)
// 			printf("%s", puta->token);
// 		else
// 			printf("%c", types[puta->type]);
// 		puta = aux;
// 	}
// 	exit(0);
// }

int	parser_input(void)
{
	int		error;
	char	*print;
	t_list	*cond;
	t_list	*token;

	error = 0;
	print = get_next_line(STDIN_FILENO);
	if (!print)
		ft_error_exit("Error: get_next_line failed");
	token = tokenize(print, &error);
	free(print);
	if (!token)
		ft_error_exit("Error: tokenization failed");
	check_tokens(token, 0, &error);
	if (error != 0)
	{
		ft_lstclear(&token, free_token);
		ft_error_exit("Error: tokenization failed");
	}
	cond = token_parser(token, &error);
	print_shell(cond);
	ft_lstclear(&cond, free_shell);
	ft_lstclear(&token, free_token);
	return (0);
}
