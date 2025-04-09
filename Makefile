# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 18:59:32 by pafranco          #+#    #+#              #
#    Updated: 2025/04/09 15:04:34 by pafranco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                 VARIABLES                                    #
# **************************************************************************** #

SRCS	= main.c \
		  parser/input.c \
		  parser/parser.c \
		  parser/printer.c \
		  parser/tokenizer.c \
		  parser/tokenizer_utils.c \
		  parser/tokenize_expansion.c \
		  parser/token_lists.c \
		  parser/subshells.c \
		  parser/token_checker.c \
		  parser/heredoc.c \
		  parser/parser_utils.c \

OBJS	= ${SRCS:.c=.o}

LIB_DIR = libft/
LIBFT = $(LIB_DIR)libft.a

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
