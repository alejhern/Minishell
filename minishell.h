/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:59:04 by pafranco          #+#    #+#             */
/*   Updated: 2025/04/22 19:26:04 by pafranco         ###   ########.fr       */
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

#endif