/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:52:18 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/04 15:49:01 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_redirect(t_redirect *redirect)
{
	t_redirect		*aux;

	while (redirect)
	{
		aux = redirect->next;
		free(redirect->path);
		free(redirect);
		redirect = aux;
	}
}

void	free_split(char **argv)
{
	int			i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_comm(t_command *command)
{
	t_command		*aux;

	while (command)
	{
		aux = command->next;
		free_split(command->argv);
		free_redirect(command->redirect_out);
		free_redirect(command->redirect_in);
		free(command);
		command = aux;
	}
}

void	free_cond(t_conditional *cond)
{
	t_conditional	*aux;

	while (cond)
	{
		aux = cond->next;
		free_comm(cond->command);
		free(cond);
		cond = aux;
	}
}

void	*p_calloc(size_t nmeb, size_t size, t_conditional *cond)
{
	void		*ret;
	char		*error;

	ret = ft_calloc(nmeb, size);
	if (ret == 0)
	{
		error = "CALLOC FAIL";
		write(2, error, 11);
		free_cond(cond);
		exit(0);
	}
	return (ret);
}

char	*p_substr(char *s, int start, int len, t_conditional *cond)
{
	char		*ret;
	char		*error;

	ret = 0;
	ret = ft_substr(s, start, len);
	if (ret == 0)
	{
		error = "SUBSTR FAIL";
		write(2, error, 11);
		free_cond(cond);
		exit(0);
	}
	return (ret);
}

int	double_strchr(char *prompt, char c)
{
	long long				i;

	i = ft_strchr(prompt, c) - prompt;
	if (i < 0 || (ft_strchr(&prompt[i + 1], c) != &prompt[i + 1]))
		i = -1;
	return (i);
}
