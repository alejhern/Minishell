/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:22:01 by pafranco          #+#    #+#             */
/*   Updated: 2025/02/28 19:20:10 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
int	check_cond(char *prompt, char **next)
{
	int			found_and;
	int			found_or;
	char		*and;
	char		*or;

	found_and = 0;
	found_or = 0;
	or = ft_strchr(prompt, '|');
	if (or && ft_strchr(or + 1, '|') == or + 1)
		found_or = 1;
	and = ft_strchr(prompt, '&');
	if (and && ft_strchr(and + 1, '&') == and + 1)
		found_and = 1;
	if ((found_and && !found_or) || (found_or && found_and && and < or))
	{
		*and = 0;
		*next = and + 2;
		return (1);
	}
	if ((found_or && !found_and) || (found_and && found_or && or < and))
	{
		*or = 0;
		*next = or + 2;
		return (2);
	}
	return (0);
}
*/
int	find_conditional(char *prompt, int *type)
{
	int			and;
	int			or;
	int			sub;

	and = ft_strchr(prompt, '&') - prompt;
	if (and < 0 ||( ft_strchr(&prompt[and + 1], '&') != &prompt[and + 1]))
		and = INT_MAX;
	or = ft_strchr(prompt, '|') - prompt;
	if (or < 0 ||( ft_strchr(&prompt[or + 1], '|') != &prompt[or + 1]))
		or = INT_MAX;
	sub = ft_strchr(prompt, '(') - prompt;
	if (sub < 0 || ft_strchr(&prompt[sub], ')') == 0)
		sub = INT_MAX;
	*type = 0;
	if (and < or && and < sub)
		*type = 1;
	if (or < and && or < sub)
		*type = 2;
	if (sub < and && sub < or)
		*type = 3;
	return ((and * (*type == 1)) + (or * (*type == 2)) + (sub * (*type == 3)));
}
/*
int	find_cond(char *prompt, int *type)
{
	char			*and;
	char			*or;
	char			*sub;
	int				done;

	done = 0;
	while (!done)
	{
		and = ft_strchr(prompt, '&');
		if (and != 0 && prompt[and + 1] == '&')
			done = 1;
	}
	done = 0;
	while (!done)
	{
		and = ft_strchr(prompt, ')');
		if (and != 0 && prompt[and + 1] == '&')
			done = 1;
	}
	done = 0;
	while (!done)
	{
		and = ft_strchr(prompt, '(');
		if (and != 0 && prompt[and + 1] == '&')
			done = 1;
	}
}
*/
int	find_delimiter(char *prompt)
{
	int			i;
	int			aux;

	i = ft_strchr(prompt, '<') - prompt;
	aux = ft_strchr(prompt, '>') - prompt;
	if (i < 0 || (aux < i && aux > 0))
		i = aux;
	aux = ft_strchr(prompt, ' ') - prompt;
	if (i < 0 || (aux < i && aux > 0))
		i = aux;
	aux = ft_strchr(prompt, '	') - prompt;
	if (i < 0 || (aux < i && aux > 0))
		i = aux;
	aux = ft_strchr(prompt, 0) - prompt;
	if (i < 0 || (aux < i && aux > 0))
		i = aux;
	return (i * (i > 0));
}

int	find_pipe(char *prompt)
{
	int			i;

	i = ft_strchr(prompt, '|') - prompt;
	if (i < 0)
		i = ft_strchr(prompt, 0) - prompt;
	return (i);
}

t_redirect	*create_redirect(char *prompt, t_redirect *prev, int *pos, t_conditional *con)
{
	int				i;
	int				j;
	t_redirect		*redirect;
	t_redirect		*aux;

	redirect = p_calloc(1, sizeof(t_redirect), con);
	i = 0;
	j = 0;
	if (prompt[i] == '<' || prompt[i] == '>')
	{
		i++;
		redirect->is_double = 1;
	}
	while (prompt[i] == ' ' || prompt[i] == '	')
		i++;
	j = find_delimiter(prompt);
	redirect->path = p_substr(prompt, i, j, con);
	*pos = *pos + j;
	if (prev == 0)
		return(redirect);
	aux = prev;
	while (aux->next)
		aux = aux->next;
	aux->next = redirect;
	return (aux);
}

int	new_argv(char ***argv, char *prompt, t_conditional *cond, int quotes)
{
	int			i;
	int			j;
	char		**new;

	i = 0;
	if (quotes)
		j = ft_strchr(prompt + 1, *prompt) - prompt;
	else
		j = find_delimiter(prompt);
	while(*argv && (*argv)[i])
		i++;
	new = p_calloc(i + 2, sizeof(char *), cond);
	i = 0;
	while(*argv && (*argv)[i])
	{
		new[i] = (*argv)[i];
		i++;
	}
	new[i] = p_substr(prompt, 0, j, cond);
	if (*argv)
		free(*argv);
	*argv = new;
	return (j);
}

t_command	*create_command(char *p, t_conditional *cond)
{
	int					i;
	t_command			*c;
	char				**argv;

	i = 0;
	argv = 0;
	c = p_calloc(1, sizeof(t_command), cond);
	while (p[i])
	{
		while (p[i] == ' ' || p[i] == '	')
			i++;
		if (p[i] == '<')
			c->redirect_in = create_redirect(&p[i + 1], c->redirect_in, &i, cond);
		else if (p[i] == '>')
			c->redirect_out = create_redirect(&p[i + 1], c->redirect_out, &i, cond);
		else
		{
			i += new_argv(&argv, &p[i], cond, (p[i] == 39 || p[i] == 34));//39 == '     34 == "
			c->argv = argv;
		}
	}
	return(c);
}

t_command	*new_command(char *prompt, int *pos, t_conditional *cond)
{
	int					i;
	int					j;
	t_command			*command;
	t_command			*next;
	t_command			*aux;

	command = 0;
	i = 0;
	while (prompt[i])
	{
		j = find_pipe(prompt);
		j = j * (j >= 0);
		if (j && prompt[i + j])
			prompt[i + j] = 0;
		next = create_command(&prompt[i], cond);
		if (command == 0)
		{
			command = next;
			aux = next;
		}
		else
			aux->next = next;
		i += j;
	}
	*pos = i;
	return (command);
}

t_conditional	*lexer_start(char *prompt)//cal alliberar prompt a fora perque perdo el punter
{
	int					i;
	int					j;
	t_conditional		*conditional;
	t_conditional		*next;
	t_conditional		*aux;

	i = 0;
	conditional = 0;
	while (prompt[i])
	{
		next = p_calloc(1, sizeof(t_conditional), conditional);
		j = find_conditional(prompt, &(next->type));
		if (conditional == 0)
		{
			conditional = next;
			aux = conditional;
		}
		else
			aux->next = next;
		next->command = new_command(&prompt[i], &i, conditional);
		i += j + (j != 0) + (next->type == 1 || next->type == 2);
	}
	return(conditional);
}
