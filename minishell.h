/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:59:04 by pafranco          #+#    #+#             */
/*   Updated: 2025/05/30 18:50:43 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define RESET "\033[0m"

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>

extern int			g_signal;

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
	char			**command;
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

void				print_shell(void *shell);
void				print_token(t_token *token);

void				free_token(t_token *token);
void				free_shell(void *condi);

int					remove_quotes(t_token *token);
int					is_del(char c);
void				heredoc(t_token *token, t_redirect *red, int type);
int					token_cond_util(int or, int and, int *error, t_token *next);

t_token				*token_lstlast(t_token *token);
t_token				*token_lstnew(char *token, int type);
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
char				*expand(char *prompt, char **env);
int					new_subshell(t_list *list_og, t_token **token);
void				check_tokens(t_token *token, t_token **token_sub,
						int *error, char **env);
int					check_subshell(t_token **token, char **env);

// ███████╗██╗  ██╗███████╗ ██████╗
// ██╔════╝╚██╗██╔╝██╔════╝██╔════╝
// █████╗   ╚███╔╝ █████╗  ██║     
// ██╔══╝   ██╔██╗ ██╔══╝  ██║     
// ███████╗██╔╝ ██╗███████╗╚██████╗
// ╚══════╝╚═╝  ╚═╝╚══════╝ ╚═════╝

int					get_input_file(t_list *redirect);
int					*get_output_files(t_list *redirects);
void					transfer_output(int *fds, char *output);
int					launch_shells(t_list *shells, char *proyect_path, char ***env);

// ██╗  ██╗██╗███████╗████████╗ ██████╗ ██████╗ ██╗   ██╗
// ██║  ██║██║██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗╚██╗ ██╔╝
// ███████║██║███████╗   ██║   ██║   ██║██████╔╝ ╚████╔╝ 
// ██╔══██║██║╚════██║   ██║   ██║   ██║██╔══██╗  ╚██╔╝  
// ██║  ██║██║███████║   ██║   ╚██████╔╝██║  ██║   ██║   
// ╚═╝  ╚═╝╚═╝╚══════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝   ╚═╝   

int					add_to_history(char **history, char *line, int size);
void				commit_history(char **history, int size);
char				**get_history(int *size);

//██████  ██    ██ ██ ██      ████████ ██ ███    ██ ███████ 
//██   ██ ██    ██ ██ ██         ██    ██ ████   ██ ██      
//██████  ██    ██ ██ ██         ██    ██ ██ ██  ██ ███████ 
//██   ██ ██    ██ ██ ██         ██    ██ ██  ██ ██      ██ 
//██████   ██████  ██ ███████    ██    ██ ██   ████ ███████ 

int					mini_exit(int exit);
int					mini_cd(char **command, char ***env);
int					mini_pwd(char **command, char ***env);
int					mini_export(char **command, char ***env);
int					mini_unset(char **command, char ***env);
int					mini_env(char **command, char ***env);
int					mini_echo(char **command, char ***env);

//███████ ██  ██████  ███    ██  █████  ██      ███████ 
//██      ██ ██       ████   ██ ██   ██ ██      ██      
//███████ ██ ██   ███ ██ ██  ██ ███████ ██      ███████ 
//     ██ ██ ██    ██ ██  ██ ██ ██   ██ ██           ██ 
//███████ ██  ██████  ██   ████ ██   ██ ███████ ███████ 

void	signal_handler_main(int sig);

#endif
