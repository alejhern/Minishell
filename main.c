/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:49:10 by pafranco          #+#    #+#             */
/*   Updated: 2025/06/28 22:39:22 by pafranco         ###   ########.fr       */
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
	if (!cwd)
		cwd = ft_strdup(ft_getenv("PWD", env));
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

	if (!env || ft_memlen(env) == 0)
		return (readline("minishell> "));
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

static int	manage_prompt(char *prompt, int fd)
{
	if (g_signal != 0)
	{
		g_signal = 0;
		return (0);
	}
	if (!prompt)
		builtin_exit(ft_split("exit 1", ' '), NULL);
	if (ft_strlen(prompt) == 0)
	{
		free(prompt);
		return (0);
	}
	add_history(prompt);
	if (fd != -1 && !ft_putendl_fd(prompt, fd))
		ft_putendl_fd("Error: can't write to history file", STDERR_FILENO);
	return (1);
}

static void	line_shell(char ***env, int history_fd)
{
	int		error;
	char	*prompt;
	t_list	*shells;
	t_token	*token;

	error = 0;
	while (1)
	{
		error = 0;
		prompt = get_line_prompt(*env, error);
		if (!manage_prompt(prompt, history_fd))
			continue ;
		token = tokenize(prompt, &error);
		free(prompt);
		syntax_error(token, env, &error);
		if (error != 0)
			continue ;
		shells = token_parser(token, &error, NULL);
		if (!shells)
			ft_error_exit("PARSER ERROR");
		error = launch_shells(shells, env);
		ft_lstclear(&shells, free_shell);
		free_token(token);
		persist_exit_status(error, env);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	**envp;
	int		history_fd;

	if (argc != 1 && argv[0])
	{
		ft_putstr_fd("Error: no arguments expected\n", 2);
		return (1);
	}
	envp = ft_env((const char **)env);
	if (!envp)
		envp = ft_safe_calloc(1, sizeof(char *));
	signal(SIGINT, signal_handler_main);
	signal(SIGQUIT, SIG_IGN);
	history_fd = create_history_file(envp);
	if (history_fd == -1)
		ft_putendl_fd("Error: can't create history file", STDERR_FILENO);
	line_shell(&envp, history_fd);
	ft_free_array((void ***)&envp);
	return (0);
}
