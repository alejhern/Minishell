/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:52:18 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/17 17:14:28 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_redirect(void *red)
{
	t_redirect		*redirect;

	redirect = red;
	free(redirect->path);
	free(redirect);
}

void	free_comm(void *comm)
{
	t_command		*command;

	command = comm;
	ft_free_array((void ***)&command->argv);
	ft_lstclear(&command->redirect_out, free_redirect);
	ft_lstclear(&command->redirect_in, free_redirect);
	free(command);
}

void	free_cond(void *condi)
{
	t_shell			*cond;

	cond = condi;
	ft_lstclear(&cond->command, free_comm);
	free(cond);
}

void	free_shell(t_list *list)
{
	ft_lstclear(&list, free_cond);
}

void	*p_calloc(size_t nmeb, size_t size)
{
	void		*ret;
	char		*error;

	ret = ft_calloc(nmeb, size);
	if (ret == 0)
	{
		error = "CALLOC FAIL";
		write(2, error, 11);
		exit(0);
	}
	return (ret);
}

char	*p_substr(char *s, int start, int len)
{
	char		*ret;
	char		*error;

	ret = ft_substr(s, start, len);
	if (ret == 0)
	{
		error = "SUBSTR FAIL";
		write(2, error, 11);
		exit(0);
	}
	return (ret);
}

char	*p_strdup(char *s)
{
	char		*ret;
	char		*error;

	ret = ft_strdup(s);
	if (ret == 0)
	{
		error = "SUBSTR FAIL";
		write(2, error, 11);
		exit(0);
	}
	return (ret);
}

t_list	*p_lstnew(void *content)
{
	t_list		*list;

	list = ft_lstnew(content);
	if (!content)
		exit(0);
	return (list);
}

int	is_del(char c)
{
	return (c == '<' || c == '>' || c == '"' || c == '\'' || c == '&' ||
				c == '|' || c == '(' || c == ')');
}
