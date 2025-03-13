/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:59:04 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/13 22:24:22 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <limits.h>

# include "libft/libft.h"

typedef struct s_redirect
{
	char					*path;
	int						is_double;
	struct s_redirect		*next;
}				t_redirect;

typedef struct s_command
{
	char					**argv;
	t_redirect				*redirect_out;
	t_redirect				*redirect_in;
	struct s_command		*next;
}				t_command;

typedef struct s_conditional
{
	int						type;
	t_command				*command;
	struct s_conditional	*subshell;
	struct s_conditional	*next;
}				t_conditional;

typedef struct s_history
{
	char					*prompt;
	struct s_history		*next;
	struct s_history		*prev;
}				t_history;

typedef struct s_token
{
	char					*token;
	int						type;
	struct s_token			*next;
}				t_token;

void			free_cond(t_conditional *c);
void			free_token(t_token *token, int util);

void			*p_calloc(size_t nmeb, size_t size, t_conditional *c);
char			*p_substr(char *s, int start, int len, t_conditional *cond);
char			*p_strdup(char *s, t_conditional *cond);

int				parser_input(int util);

t_token			*tokenize(char *prompt, int *error);

t_conditional	*token_parser(t_token *token, int *error);

void			print_cond(t_conditional *cond);
void			print_token(t_token *token);

t_token			*token_lstlast(t_token *token);
t_command		*command_lstlast(t_command *command);
t_redirect		*redirect_lstlast(t_redirect * redirect);
t_conditional	*cond_lstlast(t_conditional *cond);

int				is_del(char c);

void			token_lstadd_back(t_token **token, t_token *new_token);
void			command_lstadd_back(t_command **command, t_command *new_command);
void			redirect_lstadd_back(t_redirect **redirect, t_redirect *new_redirect);
void			cond_lstadd_back(t_conditional **cond, t_conditional *new_cond);

#endif /* MINISHELL_H */
