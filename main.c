/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:49:10 by pafranco          #+#    #+#             */
/*   Updated: 2025/06/18 17:04:58 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*parsing_pwd(char **env, char error)
{
	char	*prompt;
	char	*home;
	char	*cwd;
	char	*aux;

	prompt = ft_strjoin(":", BLUE);
	cwd = getcwd(NULL, 0);
	home = ft_getenv("HOME", env);
	if (ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		aux = ft_strjoin("~", cwd + ft_strlen(home));
	else
		aux = ft_strdup(cwd);
	prompt = ft_strappend(prompt, aux);
	free(aux);
	if (error)
		prompt = ft_strappend(prompt, RED);
	else
		prompt = ft_strappend(prompt, GREEN);
	free(cwd);
	return (prompt);
}

static char	*get_line_prompt(char **env, int error)
{
	char	*prompt;
	char	*prompt_line;
	char	*aux;
	char	**hostname;

	prompt_line = ft_strjoin((char *)GREEN, (char *)ft_getenv("USER", env));
	hostname = NULL;
	ft_append_array((void ***)&hostname, ft_strdup("hostname"));
	prompt_line = ft_strappend(prompt_line, "@");
	aux = ft_exec_catch(hostname, env);
	ft_free_array((void ***)&hostname);
	prompt_line = ft_strappend(prompt_line, aux);
	free(aux);
	aux = parsing_pwd(env, error);
	prompt_line = ft_strappend(prompt_line, aux);
	free(aux);
	prompt_line = ft_strappend(prompt_line, ">");
	prompt_line = ft_strappend(prompt_line, (char *)RESET);
	prompt = readline(prompt_line);
	free(prompt_line);
	ft_putstr_fd(RESET, STDOUT_FILENO);
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
		builtin_exit(ft_split("exit 1", ' '));
	if (ft_strlen(prompt) == 0)
	{
		free(prompt);
		return (0);
	}
	add_history(prompt);
	return (1);
}

static void	line_shell(char ***env)
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
		ft_lstiter(shells, print_shell);
		result = launch_shells(shells, env);
		ft_lstclear(&shells, free_shell);
		free_token(token);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	**envp;

	if (argc != 1 && argv[0])
	{
		ft_putstr_fd("Error: no arguments expected\n", 2);
		return (1);
	}
	envp = ft_env((const char **)env);
	if (!envp)
		ft_perror_exit("Error: malloc");
	signal(SIGINT, signal_handler_main);
	line_shell(&envp);
	ft_free_array((void ***)&envp);
	return (0);
}
