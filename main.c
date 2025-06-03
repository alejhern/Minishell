/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:49:10 by pafranco          #+#    #+#             */
/*   Updated: 2025/06/03 21:42:52 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parsing_pwd(char **env, char *cwd, char *aux1, char * aux2)
{
	char	*home;
	char	*aux;

	home = ft_getenv("HOME", env);
	aux = ft_strjoin(":", BLUE);
	if (!aux)
		exit(0);
	aux2 = ft_strjoin_free(aux1, aux);
	if (home)
	{
		if (ft_strncmp(cwd, home, ft_strlen(home)) == 0)
			aux = ft_strjoin("~", cwd + ft_strlen(home));
		else
			aux = ft_strdup(cwd);
	}
	else
		aux = ft_strdup(cwd);
	if (!aux)
		exit(0);
	aux1 = ft_strjoin_free(aux2, aux);
	return (aux1);
}

static char	*get_line_prompt(char **env, int error)
{
	char	*cwd;
	char	*aux1;
	char	*aux2;
	char	*prompt;
	char	**hostname;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("");
	aux1 = ft_strjoin((char *)GREEN, (char *) ft_getenv("USER", env));
	hostname = NULL;
	ft_append_array((void ***)&hostname, ft_strdup("hostname"));
	aux2 = ft_strjoin("@", ft_exec_catch(hostname, env));
	ft_free_array((void ***)&hostname);
	aux2 = parsing_pwd(env, cwd, ft_strjoin_free(aux1, aux2), aux2);
	free(cwd);
	if (error)
		aux1 = ft_strjoin(aux2, RED);
	else
		aux1 = ft_strjoin(aux2, GREEN);
	free(aux2);
	if (!aux1)
		exit(0);
	aux2 = ft_strjoin_free(aux1, ft_strjoin(">", RESET));
	prompt = readline(aux2);
	free(aux2);
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
		ft_lstiter(shells, print_shell);
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
