/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:22:01 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/04 15:48:24 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirect	*create_redirect(char *p, t_redirect *pv, int *ps, t_conditional *c)
{
	int				i;
	int				j;
	t_redirect		*redirect;
	t_redirect		*aux;

	redirect = p_calloc(1, sizeof(t_redirect), c);
	i = 0;
	j = 0;
	if (p[i] == '<' || p[i] == '>')
	{
		i++;
		redirect->is_double = 1;
	}
	while (p[i] == ' ' || p[i] == '	')
		i++;
	j = find_delimiter(&p[i]);
	redirect->path = p_substr(p, i, j, c);
	*ps = *ps + j + i + 1;
	if (pv == 0)
		return (redirect);
	aux = pv;
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
		j = find_quotes(prompt) + 1;
	else
		j = find_delimiter(prompt);
	while (*argv && (*argv)[i])
		i++;
	new = p_calloc(i + 2, sizeof(char *), cond);
	i = 0;
	while (*argv && (*argv)[i])
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
	int					del;
	t_command			*c;
	char				**argv;

	i = 0;
	del = find_pipe(p);
	argv = 0;
	c = p_calloc(1, sizeof(t_command), cond);
	while (p[i] && i < del)
	{
		while ((p[i] == ' ' || p[i] == '	' || p[i] == '|') && i < del)
			i++;
		if (p[i] == '<')
			c->redirect_in = create_redirect(&p[i + 1],
					c->redirect_in, &i, cond);
		else if (p[i] == '>')
			c->redirect_out = create_redirect(&p[i + 1],
					c->redirect_out, &i, cond);
		else if (i < del)
		{
			i += new_argv(&argv, &p[i], cond, (p[i] == '\'' || p[i] == '\"'));
			c->argv = argv;
		}
	}
	return (c);
}

t_command	*fill_conditional(char *prompt, t_conditional *cond)
{
	int					i;
	int					j;
	int					del;
	t_command			*command;
	t_command			*next;
	t_command			*aux;

	command = 0;
	i = 0;
	del = find_conditional(prompt, 0);
	while (prompt[i] && (i < del || del == 0))
	{
		j = find_pipe(&prompt[i]);
		next = create_command(&prompt[i], cond);
		if (command == 0)
			command = next;
		else
			aux->next = next;
		aux = next;
		i += j;
	}
	return (command);
}

t_conditional	*lexer_start(char *prompt)
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
		j = find_conditional(&prompt[i], &(next->type));
		if (conditional == 0)
			conditional = next;
		else
			aux->next = next;
		aux = next;
		next->command = fill_conditional(&prompt[i], conditional);
		i += j + (j != 0 && next->type != 0) + (next->type == 1 || next->type == 2);
	}
	return (conditional);
}
