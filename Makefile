# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 18:59:32 by pafranco          #+#    #+#              #
#    Updated: 2025/06/29 20:09:24 by pafranco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                 VARIABLES                                    #
# **************************************************************************** #

UTIL_DIR = ./utils/
PARSE_DIR = ./parser/
EXEC_DIR = ./exeggutor/
SIGNALS_DIR = ./signals/
BUILT-IN_DIR = ./built-ins/
HISTORY_DIR = ./history/

UTIL_SRC =		cd.c \
				echo.c \
				env.c \
				exit.c \
				export.c \
				export.c \
				fork.c \
				pwd.c \
				unset.c \

EXEC_SRC =		exec.c \
				fork.c \
				redirects.c \

HISTORY_SRC =	history.c \

PARSE_SRC =		here_doc.c \
				parser.c \
				subshells.c \
				token_checker.c \
				tokenize_expansion.c \
				tokenizer.c \

SIGNALS_SRC =	signal_handling.c \

SRCS = $(shell find $(UTIL_DIR) $(PARSE_DIR) $(EXEC_DIR) $(BUILT-IN_DIR) $(SIGNALS_DIR) $(HISTORY_DIR) -type f -name "*.c") \
		main.c \

OBJS	= ${SRCS:.c=.o}

LIB_DIR = libft/
LIBFT = $(LIB_DIR)libft.a

CC = cc -g
CFLAGS = -Wall -Werror -Wextra -I $(LIB_DIR) #-fsanitiz=address

DEPS	= ${SRCS:.c=.d}

NAME	= minishell

RM		= rm -f

# **************************************************************************** #
#                                 RULES                                        #
# **************************************************************************** #

all:		$(LIBFT) ${NAME}

-include ${DEPS}
$(NAME):	$(OBJS) $(LIBFT)
	$(CC) ${CFLAGS} $(OBJS) -L$(LIB_DIR) -lreadline -lft -o ${NAME} -MMD

%.o: %.c Makefile
	$(CC) ${CFLAGS} -I $(LIB_DIR) -o $@ -c $<

$(LIBFT):
	@if [ ! -d "$(LIB_DIR)" ]; then \
		git clone https://github.com/alejhern/libft.git $(LIB_DIR); \
	fi
	@make -C $(LIB_DIR)

clean:
	@make -C $(LIB_DIR) clean
	rm -f $(OBJS)

fclean: clean
	@make -C $(LIB_DIR) fclean
	rm -f $(NAME)

re:			fclean all

.PHONY:		clean fclean re all
