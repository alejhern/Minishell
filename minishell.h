/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:59:04 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/26 20:30:30 by pafranco         ###   ########.fr       */
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
}							t_redirect;

typedef enum e_comand_type
{
	AND,
	OR,
	END
}							t_type;

typedef enum e_token_type
{
	WORD,
	PIPE,
	ORC,
	ANDC,
	OPEN_SUB,
	CLOSE_SUB,
	IN_RED,
	OUT_RED,
}							t_token_type;

typedef struct s_command
{
	int						pid;
	int						is_subshell;
	char					**argv;
	void					*subshell;
	t_list					*redirect_out;
	t_list					*redirect_in;
}							t_command;

typedef struct s_shell
{
	t_type					type;
	t_list					*command;
}							t_shell;

typedef struct s_token
{
	char					*token;
	t_token_type			type;
	struct s_token			*next;
}							t_token;

void			free_token(t_token *token, int util);
void			free_shell(t_list *list);

void			*p_calloc(size_t nmeb, size_t size);
char			*p_substr(char *s, int st, int l);
char			*p_strdup(char *s);
t_list			*p_lstnew(void *content);

int				parser_input(int util);

t_token			*tokenize(char *prompt, int *error);

t_list			*token_parser(t_token *token, int *error, t_token **token_sub);
void			parser_check(t_token **t_sub, t_token *t);
int				token_cond_util(int or, int and, int *error, t_token *next);

void			print_shell(t_list *list);
void			print_token(t_token *token);

t_token			*token_lstlast(t_token *token);
t_command		*command_lstlast(t_command *command);
t_redirect		*redirect_lstlast(t_redirect *redirect);
t_shell			*cond_lstlast(t_shell *cond);

int				is_del(char c);

void			token_lstadd_back(t_token **token, t_token *new_token);
void			command_lstadd_back(t_command **command, t_command *new_comm);
void			redirect_lstadd_back(t_redirect **redirect, t_redirect *n_red);
void			cond_lstadd_back(t_shell **cond, t_shell *new_cond);

int				new_subshell(t_list *list_og, t_token **token);

void			check_tokens(t_token *token, t_token **token_sub, int *error);
int				check_subshell(t_token **token);

#endif /* MINISHELL_H */
