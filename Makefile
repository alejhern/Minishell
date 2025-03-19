# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 18:59:32 by pafranco          #+#    #+#              #
#    Updated: 2025/03/19 19:49:16 by pafranco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                 VARIABLES                                    #
# **************************************************************************** #

SRCS	= main.c \
		  minishell_parser/input.c \
		  minishell_parser/parser.c \
		  minishell_parser/printer.c \
		  minishell_parser/tokenizer.c \
		  minishell_parser/token_lists.c \
		  minishell_parser/subshell_parser.c \
		  minishell_utils/parser_utils.c \

OBJS	= ${SRCS:.c=.o}

LIB_DIR = libft/
LIBFT = $(LIB_DIR)libft.a

CC = cc -g
CFLAGS = -Wall -Werror -Wextra -I $(LIB_DIR)# -fsanitize=address

DEPS	= ${SRCS:.c=.d}

NAME	= minishell

RM		= rm -f

# **************************************************************************** #
#                                 RULES                                        #
# **************************************************************************** #

all:		$(LIBFT) ${NAME}

-include ${DEPS}
$(NAME):	$(OBJS) $(LIBFT)
	$(CC) ${CFLAGS} $(OBJS) -L$(LIB_DIR) -lft -o ${NAME} -MMD

%.o: %.c Makefile
	$(CC) ${CFLAGS} -I $(LIB_DIR) -o $@ -c $<

$(LIBFT):
	@if [ ! -d "$(LIB_DIR)" ]; then \
		git clone https://github.com/alejhern/libft.git $(LIB_DIR); \
	fi
	@make -C $(LIB_DIR)
	@make -C $(LIB_DIR) bonus

clean:
	@make -C $(LIB_DIR) clean
	rm -f $(OBJS)

fclean: clean
	@make -C $(LIB_DIR) fclean
	rm -f $(NAME)
	rm -rf $(MLX42_DIR)build

re:			fclean all

.PHONY:		clean fclean re all
