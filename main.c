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

static void	parsing_home(char **env, char *cwd)
{
	char	*home;
	int		len_home;

	home = ft_getenv("HOME", env);
	if (home)
	{
		len_home = ft_strlen(home);
		if (ft_strncmp(cwd, home, len_home) == 0)
		{
			ft_putchar_fd('~', STDOUT_FILENO);
			ft_putstr_fd(cwd + len_home, STDOUT_FILENO);
		}
		else
			ft_putstr_fd(cwd, STDOUT_FILENO);
	}
	else
		ft_putstr_fd(cwd, STDOUT_FILENO);
}

static char	*get_line_prompt(char **env, int error)
{
	char	*cwd;
	char	*prompt;
	char	**hostname;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("");
	ft_putstr_fd((const char *)GREEN, STDOUT_FILENO);
	ft_putstr_fd((const char *) ft_getenv("USER", env), STDOUT_FILENO);
	ft_putchar_fd((const char) '@', STDOUT_FILENO);
	hostname = NULL;
	ft_append_array((void ***)&hostname, ft_strdup("hostname"));
	prompt = ft_exec_catch(hostname, env);
	ft_free_array((void ***)&hostname);
	ft_putstr_fd(prompt, STDOUT_FILENO);
	free(prompt);
	ft_putchar_fd((const char) ':', STDOUT_FILENO);
	ft_putstr_fd((const char *)BLUE, STDOUT_FILENO);
	parsing_home(env, cwd);
	free(cwd);
	ft_putstr_fd((const char *)GREEN, STDOUT_FILENO);
	if (error)
		ft_putstr_fd((const char *)RED, STDOUT_FILENO);
	prompt = readline("> " RESET);
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
	int		result;

	error = 0;
	result = 0;
	while (1)
	{
		prompt = get_line_prompt(*env, result);
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
		result = launch_shells(shells, proyect_path, env);
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
	envp = ft_env((const char **)env);
	if (!envp)
		ft_perror_exit("Error: malloc");
	proyect_path = getcwd(NULL, 0);
	if (!proyect_path)
		ft_perror_exit("Error: getcwd");
	signal(SIGINT, signal_handler_main);
	line_shell(&envp, proyect_path);
	free(proyect_path);
	ft_free_array((void ***)&envp);
	return (0);
}
