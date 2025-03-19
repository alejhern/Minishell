/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:59:04 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/19 19:50:50 by pafranco         ###   ########.fr       */
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
	int						type;
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

t_list			*token_parser(t_token *token, int *error);

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
int				add_redirect(t_list *list_og, t_token **token);
int				new_pipe(t_list *cond_og);
int				new_conditional(t_list *list_og, t_token *token);
int				add_word(t_list *list_og, t_token *token);
t_list			*subshell_parser(t_token **token, int *error);

#endif /* MINISHELL_H */
