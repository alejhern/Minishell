/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:46:25 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/26 20:24:08 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_word(t_list *list_og, t_token *token)
{
	t_shell		*cond;
	t_command	*command;
	t_list		*last_node;
	char		*dup_str;

	if (!list_og || !token || !token->token)
		return (1);
	last_node = ft_lstlast(list_og);
	if (!last_node || !last_node->content)
		return (1);
	cond = (t_shell *)last_node->content;
	if (!cond->command)
	{
		cond->command = ft_lstnew(ft_calloc(1, sizeof(t_command)));
		if (!cond->command || !cond->command->content)
			return (1);
	}
	command = (t_command *)ft_lstlast(cond->command)->content;
	if (!command)
		return (1);
	dup_str = ft_strdup(token->token);
	if (!dup_str)
		return (1);
	ft_append_array((void ***)&command->argv, dup_str);
	if (!command->argv)
	{
		free(dup_str);
		return (1);
	}
	return (0);
}

int	new_conditional(t_list *list_og, t_token *token)
{
	t_list	*last_node;
	t_shell	*last_shell;
	t_shell	*new_shell;
	t_list	*new_node;

	if (!list_og || !token || (token->type != TOKEN_AND
			&& token->type != TOKEN_OR))
		return (1);
	last_node = ft_lstlast(list_og);
	if (!last_node || !last_node->content)
		return (1);
	last_shell = (t_shell *)last_node->content;
	last_shell->type = (token->type == TOKEN_AND) ? AND : OR;
	new_shell = ft_calloc(1, sizeof(t_shell));
	if (!new_shell)
		return (1);
	new_node = ft_lstnew(new_shell);
	if (!new_node)
	{
		free(new_shell);
		return (1);
	}
	ft_lstadd_back(&list_og, new_node);
	return (0);
}

int	new_pipe(t_list *cond_og)
{
	t_shell		*con;
	t_command	*command;
	t_list		*list;
	t_list		*last_node;
	t_list		*last_cmd;

	if (!cond_og)
		return (1);
	last_node = ft_lstlast(cond_og);
	if (!last_node || !last_node->content)
		return (1);
	con = (t_shell *)last_node->content;
	if (!con->command)
		return (1);
	con->type = PIPE;
	last_cmd = ft_lstlast(con->command);
	if (!last_cmd || !last_cmd->content)
		return (1);
	if (((t_command *)last_cmd->content)->argv == NULL)
		return (1);
	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (1);
	list = ft_lstnew(command);
	if (!list)
	{
		free(command);
		return (1);
	}
	ft_lstadd_back(&(con->command), list);
	return (0);
}

int	add_redirect(t_list *list_og, t_list **token_node)
{
	t_shell		*cond;
	t_command	*command;
	t_list		*red;
	t_redirect	*redirect;
	t_token		*token;
	t_list		*last_node;
	t_command	*new_cmd;
	t_list		*new_cmd_node;
	t_token		*next_token;

	if (!list_og || !token_node || !*token_node)
		return (1);
	token = (*token_node)->content;
	if (!token)
		return (1);
	last_node = ft_lstlast(list_og);
	if (!last_node || !last_node->content)
		return (1);
	cond = (t_shell *)last_node->content;
	if (!cond->command)
	{
		new_cmd = ft_calloc(1, sizeof(t_command));
		if (!new_cmd)
			return (1);
		new_cmd_node = ft_lstnew(new_cmd);
		if (!new_cmd_node)
		{
			free(new_cmd);
			return (1);
		}
		ft_lstadd_back(&cond->command, new_cmd_node);
	}
	command = (t_command *)ft_lstlast(cond->command)->content;
	if (!command)
		return (1);
	if (!(*token_node)->next)
		return (1);
	redirect = ft_calloc(1, sizeof(t_redirect));
	if (!redirect)
		return (1);
	red = ft_lstnew(redirect);
	if (!red)
	{
		free(redirect);
		return (1);
	}
	next_token = (*token_node)->next->content;
	if (!next_token)
	{
		free(redirect);
		free(red);
		return (1);
	}
	if (next_token->type == TOKEN_WORD)
		redirect->is_double = 0;
	else if (token->type == next_token->type)
	{
		redirect->is_double = 1;
		*token_node = (*token_node)->next;
		next_token = (*token_node)->next->content;
	}
	*token_node = (*token_node)->next;
	if (!*token_node || !next_token || !next_token->token)
	{
		free(redirect);
		free(red);
		return (1);
	}
	redirect->path = ft_strdup(next_token->token);
	if (!redirect->path)
	{
		free(redirect);
		free(red);
		return (1);
	}
	if (token->type == TOKEN_LESS)
		ft_lstadd_back(&command->redirect_in, red);
	else if (token->type == TOKEN_GREAT)
		ft_lstadd_back(&command->redirect_out, red);
	else
	{
		free(redirect->path);
		free(redirect);
		free(red);
		return (1);
	}
	return (0);
}

t_list	*token_parser(t_list *tokens, int *error)
{
	t_list *shells;
	t_list *current_token;
	t_token *token;

	if (!tokens || !error)
		return (NULL);
	shells = ft_lstnew(ft_calloc(1, sizeof(t_shell)));
	if (!shells || !shells->content)
		return (free(shells), NULL);
	current_token = tokens;
	while (current_token && *error == 0)
	{
		token = current_token->content;
		if (!token)
		{
			*error = 1;
			break ;
		}
		if (token->type == TOKEN_WORD)
			*error = add_word(shells, token);
		else if (token->type == TOKEN_PIPE)
			*error = new_pipe(shells);
		else if (token->type == TOKEN_AND || token->type == TOKEN_OR)
			*error = new_conditional(shells, token);
		else if (token->type == TOKEN_LPAREN || token->type == TOKEN_RPAREN)
			*error = new_subshell(shells, &current_token);
		else if (token->type == TOKEN_LESS || token->type == TOKEN_GREAT)
			*error = add_redirect(shells, &current_token);
		if (*error == 0)
			current_token = current_token->next;
	}
	return (shells);
}
