# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 18:59:32 by pafranco          #+#    #+#              #
#    Updated: 2025/02/28 18:20:48 by pafranco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= main.c \
		  minishell_parser/parser_input.c \
		  minishell_parser/lexer.c \
		  minishell_utils/parser_utils.c \

LSRCS	= libft/ft_atoi.c \
		  libft/ft_bzero.c \
		  libft/ft_calloc.c \
		  libft/ft_isalnum.c \
		  libft/ft_isalpha.c \
		  libft/ft_isascii.c \
		  libft/ft_isdigit.c \
		  libft/ft_isprint.c \
		  libft/ft_itoa.c \
		  libft/ft_memchr.c \
		  libft/ft_memcmp.c \
		  libft/ft_memcpy.c \
		  libft/ft_memmove.c \
		  libft/ft_memset.c \
		  libft/ft_putchar_fd.c \
		  libft/ft_putendl_fd.c \
		  libft/ft_putnbr_fd.c \
		  libft/ft_putstr_fd.c \
		  libft/ft_split.c \
		  libft/ft_strchr.c \
		  libft/ft_strdup.c \
		  libft/ft_striteri.c \
		  libft/ft_strjoin.c \
		  libft/ft_strlcat.c \
		  libft/ft_strlcpy.c \
		  libft/ft_strlen.c \
		  libft/ft_strmapi.c \
		  libft/ft_strncmp.c \
		  libft/ft_strnstr.c \
		  libft/ft_strrchr.c \
		  libft/ft_strtrim.c \
		  libft/ft_substr.c \
		  libft/ft_tolower.c \
		  libft/ft_toupper.c \
		  libft/get_next_line.c \
		  libft/get_next_line_utils.c \

HEAD	= minishell.h

OBJS	= ${SRCS:.c=.o}

LOBJS	= ${LSRCS:.c=.o}

DEPS	= ${SRCS:.c=.d}

LDEPS	= ${LSRCS:.c=.d}

NAME	= minishell

AR		= ar rs -g

RM		= rm -f

CC		= cc

CFLAGS	= -Wall -Wextra -Werror# -fsanitize=address

all:		libft ${NAME}

libft:	
				make -C libft

fclibft:
				make -C libft fclean

clibft:
				make -C libft clean

%.o: %.c Makefile llibft/libft.a
	$(CC) ${CFLAGS} -o $@ -c $<

-include ${DEPS}
$(NAME):	$(OBJS)
	$(CC) ${CFLAGS} -o ${NAME} $(OBJS) ${LOBJS} -MMD

clean:		clibft
				${RM} ${OBJS} ${DEPS}

fclean:		clean fclibft
	${RM} ${NAME} ${BNAME}

re:			fclean all

.PHONY:		clean fclean re all libft final bonus fclibft clibft
