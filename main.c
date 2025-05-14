/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:49:10 by pafranco          #+#    #+#             */
/*   Updated: 2025/05/14 18:32:42 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line_prompt(void)
{
	char	*cwd;
	char	*user;
	char	*line;
	char	*home;

	cwd = ft_exec_catch("pwd");
	if (!cwd)
		cwd = ft_strdup("minishell");
	user = ft_strdup(getenv("USER"));
	if (!user)
		user = ft_strdup("minishell");
	home = getenv("HOME");
	if (!home)
		home = ft_strdup("minishell");
	if (ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		ft_printf(GREEN "%s" YELLOW "@" BLUE "~%s" RESET, user, cwd
			+ ft_strlen(home));
	else
		ft_printf(GREEN "%s" YELLOW "@" BLUE "%s" RESET, user, cwd);
	free(cwd);
	free(user);
	line = readline(GREEN " > " RESET);
	if (!line)
		ft_perror_exit("Error: readline");
	return (line);
}

void	line_shell(char **env)
{
	int		error;
	char	*line;
	t_list	*shells;
	t_token	*token;

	error = 0;
	while (1)
	{
		line = get_line_prompt();
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
