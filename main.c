/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:49:10 by pafranco          #+#    #+#             */
/*   Updated: 2025/05/30 19:17:49 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_line_prompt(char **env)
{
	char	*cwd;
	char	*prompt;
	char	**hostname;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("");
	ft_putstr_fd((const char *) GREEN, STDOUT_FILENO);
	ft_putstr_fd((const char*) ft_getenv("USER", env), STDOUT_FILENO);
	ft_putchar_fd((const char)'@', STDOUT_FILENO);
	hostname = NULL;
	ft_append_array((void ***)&hostname, ft_strdup("hostname"));
	prompt = ft_exec_catch(hostname, env);
	ft_free_array((void ***)&hostname);
	ft_putstr_fd(prompt, STDOUT_FILENO);
	free(prompt);
	ft_putchar_fd((const char)':', STDOUT_FILENO);
	ft_putstr_fd((const char *) BLUE, STDOUT_FILENO);
	if (ft_strcmp(cwd, ft_getenv("HOME", env)) == 0)
		ft_putchar_fd('~', STDOUT_FILENO);
	ft_printf("%s" RESET, cwd);
	free(cwd);
	prompt = readline(GREEN " > " RESET);
	return (prompt);
}

static int	manage_prompt(char *prompt)
{
	if (g_signal != 0)
	{
		g_signal = 0;
		return (0);
	}
	if (!prompt)
		ft_perror_exit("Error: readline");
	if (ft_strlen(prompt) == 0)
	{
		free(prompt);
		return (0);
	}
	add_history(prompt);
	return (1);
}

static void	line_shell(char ***env, char *proyect_path)
{
	int		error;
	char	*prompt;
	t_list	*shells;
	t_token	*token;

	error = 0;
	while (1)
	{
		prompt = get_line_prompt(*env);
		if (!manage_prompt(prompt))
			continue ;
		token = tokenize(prompt, &error);
		free(prompt);
		check_tokens(token, 0, &error, *env);
		if (error != 0)
			ft_error_exit("SYNTAX ERROR");
		shells = token_parser(token, &error, NULL);
		if (!shells)
			ft_error_exit("PARSER ERROR");
		launch_shells(shells, proyect_path, env);
		ft_lstclear(&shells, free_shell);
		free_token(token);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	**envp;
	char	*proyect_path;

	if (argc != 1 && argv[0])
	{
		ft_putstr_fd("Error: no arguments expected\n", 2);
		return (1);
	}
	signal(SIGINT, signal_handler_main);
	envp = ft_env((const char **)env);
	if (!envp)
		ft_perror_exit("Error: malloc");
	proyect_path = getcwd(NULL, 0);
	if (!proyect_path)
		ft_perror_exit("Error: getcwd");
	line_shell(&envp, proyect_path);
	free(proyect_path);
	ft_free_array((void ***)&envp);
	return (0);
}
