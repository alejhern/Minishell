# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 18:59:32 by pafranco          #+#    #+#              #
#    Updated: 2025/05/30 19:01:23 by pafranco         ###   ########.fr        #
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

SRCS = $(shell find $(UTIL_DIR) $(PARSE_DIR) $(EXEC_DIR) $(BUILT-IN_DIR) $(SIGNALS_DIR) -type f -name "*.c") \
		main.c \

OBJS	= ${SRCS:.c=.o}

LIB_DIR = libft/
LIBFT = $(LIB_DIR)libft.a

PIPEX = pipex/

CC = cc -g
CFLAGS = -Wall -Werror -Wextra -I $(LIB_DIR) # -fsanitize=address

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

$(PIPEX):
	@if [ ! -d "$(PIPEX)" ]; then \
		git clone https://github.com/alejhern/pipex.git $(PIPEX); \
	fi
	@make minishell -C $(PIPEX)
	@make -C $(PIPEX)
	@echo "Pipex built successfully."

clean:
	@make -C $(LIB_DIR) clean
	rm -f $(OBJS)

fclean: clean
	@make -C $(LIB_DIR) fclean
	@make -C $(PIPEX) fclean
	rm -f $(NAME)

re:			fclean all

.PHONY:		clean fclean re all
