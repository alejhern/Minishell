/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:49:10 by pafranco          #+#    #+#             */
/*   Updated: 2025/04/09 18:50:58 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	line_shell()
{
	int				error;
	char			*line;
	t_list			*shells;
	t_token			*token;

	error = 0;
	while (1)
	{
		line = readline("shell petit: ");
		if (line == 0)
			ft_perror_exit("EOF");
		token = tokenize(line, &error);
		check_tokens(token, 0, &error);
		if (error != 0)
			ft_error_exit("SYNTAX ERROR");
		shells = token_parser(token, &error, 0);
		if (!shells)
			ft_error_exit("PARSER ERROR");
		ft_lstiter(shells, print_shell);
		ft_lstclear(&shells, free_shell);
		free_token(token);
	}
}

int	main(void)
{
	line_shell();
	return (0);
}
