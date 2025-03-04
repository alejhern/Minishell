/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:59:04 by pafranco          #+#    #+#             */
/*   Updated: 2025/03/04 15:46:50 by pafranco         ###   ########.fr       */
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

int				parser_input(void);

void			*p_calloc(size_t nmeb, size_t size, t_conditional *c);
void			free_cond(t_conditional *c);
void			free_comm(t_command *command);
void			free_redirect(t_redirect *redirect);
void			free_split(char **argv);
char			*p_substr(char *s, int start, int len, t_conditional *cond);
int				double_strchr(char *prompt, char c);

int				find_delimiter(char *prompt);
int				find_conditional(char *prompt, int *type);
int				find_pipe(char *prompt);
int				find_quotes(char *prompt);

t_conditional	*lexer_start(char *prompt);
#endif /* MINISHELL_H */
