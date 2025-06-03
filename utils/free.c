/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amhernandez <alejhern@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:25:32 by amhernandez       #+#    #+#             */
/*   Updated: 2025/06/03 21:58:53 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		if (token->token)
			free(token->token);
		free(token);
		token = next;
	}
}

void	free_redirect(void *red)
{
	t_redirect	*redirect;

	redirect = red;
	free(redirect->path);
	free(redirect);
}

void	free_comm(void *content)
{
	t_command	*command;

	command = content;
	ft_free_array((void ***)&command->command);
	ft_lstclear(&command->subshell, free_shell);
	ft_lstclear(&command->redirect_out, free_redirect);
	ft_lstclear(&command->redirect_in, free_redirect);
	free(content);
}

void	free_shell(void *content)
{
	t_shell	*shell;

	shell = content;
	ft_lstclear(&shell->commands, free_comm);
	free(shell);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*ret;

	if (!s1 || !s2)
		exit(0);
	ret = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (!ret)
		exit(0);
	return (ret);
}
