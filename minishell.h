/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:59:04 by pafranco          #+#    #+#             */
/*   Updated: 2025/04/09 18:59:13 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "libft/pipex.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_redirect
{
	char			*path;
	int				is_double;
}					t_redirect;

typedef enum e_comand_type
{
	END,
	AND,
	OR
}					t_type;

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
	PASS
}					t_token_type;

typedef struct s_command
{
	int				pid;
	int				is_subshell;
	char			**comand;
	t_list			*subshell;
	t_list			*redirect_out;
	t_list			*redirect_in;
}					t_command;

typedef struct s_shell
{
	t_type			type;
	t_list			*commands;
}					t_shell;

typedef struct s_token
{
	char			*token;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

// ██╗   ██╗████████╗██╗██╗     ███████╗
// ██║   ██║╚══██╔══╝██║██║     ██╔════╝
// ██║   ██║   ██║   ██║██║     ███████╗
// ██║   ██║   ██║   ██║██║     ╚════██║
// ╚██████╔╝   ██║   ██║███████╗███████║
//  ╚═════╝    ╚═╝   ╚═╝╚══════╝╚══════╝

void				print_shell(void *cond);
void				print_token(t_token *token);

void				free_token(t_token *token);
void				free_shell(void *condi);

int					remove_quotes(t_token *token);
int					is_del(char c);
void				heredoc(t_token *token, t_redirect *red, int type);
int					token_cond_util(int or, int and, int *error, t_token *next);

t_token				*token_lstlast(t_token *token);
void				token_lstadd_back(t_token **token, t_token *new_token);

// ██████╗  █████╗ ██████╗ ███████╗███████╗██████╗
// ██╔══██╗██╔══██╗██╔══██╗██╔════╝██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝███████╗█████╗  ██████╔╝
// ██╔═══╝ ██╔══██║██╔══██╗╚════██║██╔══╝  ██╔══██╗
// ██║     ██║  ██║██║  ██║███████║███████╗██║  ██║
// ╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝

t_token				*tokenize(char *prompt, int *error);
t_list				*token_parser(t_token *token, int *error,
						t_token **token_sub);
void				parser_check(t_token **t_sub, t_token *t);
char				*expand(char *prompt);
int					new_subshell(t_list *list_og, t_token **token);
void				check_tokens(t_token *token, t_token **token_sub,
						int *error);
int					check_subshell(t_token **token);

// ███████╗██╗  ██╗███████╗ ██████╗
// ██╔════╝╚██╗██╔╝██╔════╝██╔════╝
// █████╗   ╚███╔╝ █████╗  ██║     
// ██╔══╝   ██╔██╗ ██╔══╝  ██║     
// ███████╗██╔╝ ██╗███████╗╚██████╗
// ╚══════╝╚═╝  ╚═╝╚══════╝ ╚═════╝

int					launch_commands(t_list *shells, char **env);

// ██╗  ██╗██╗███████╗████████╗ ██████╗ ██████╗ ██╗   ██╗
// ██║  ██║██║██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗╚██╗ ██╔╝
// ███████║██║███████╗   ██║   ██║   ██║██████╔╝ ╚████╔╝ 
// ██╔══██║██║╚════██║   ██║   ██║   ██║██╔══██╗  ╚██╔╝  
// ██║  ██║██║███████║   ██║   ╚██████╔╝██║  ██║   ██║   
// ╚═╝  ╚═╝╚═╝╚══════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝   ╚═╝   
                                                      
int					add_to_history(char **history, char *line, int size);
void				commit_history(char **history, int size);
char				**get_history(int *size);

#endif
