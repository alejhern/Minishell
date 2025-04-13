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

static char	*get_line_prompt(void)
{
	char		*prompt;
	char		*line;

	prompt = capture_output("pwd");
	if (!prompt)
		prompt = ft_strdup("minishell");
	ft_clean_line(&prompt);
	prompt = ft_strappend(prompt, " > ");
	if (!prompt)
		prompt = ft_strdup("minishell > ");
	line = readline(prompt);
	free(prompt);
	return (line);
}

void	line_shell(char **env)
{
	int				error;
	char			*line;
	t_list			*shells;
	t_token			*token;

	error = 0;
	while (1)
	{
		line = get_line_prompt();
		if (!line)
			ft_error_exit("EOF");
		token = tokenize(line, &error);
		free(line);
		check_tokens(token, 0, &error);
		if (error != 0)
			ft_error_exit("SYNTAX ERROR");
		shells = token_parser(token, &error, 0);
		if (!shells)
			ft_error_exit("PARSER ERROR");
		ft_lstiter(shells, print_shell);
		launch_commands(shells, env);
		ft_lstclear(&shells, free_shell);
		free_token(token);
	}
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 1 && argv[0])
	{
		ft_putstr_fd("Error: no arguments expected\n", 2);
		return (1);
	}
	line_shell(env);
	return (0);
}
