# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 12:50:58 by kbrener-          #+#    #+#              #
#    Updated: 2024/03/04 14:02:52 by kbrener-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = \
	libft/ft_isascii.c \
	libft/ft_memcpy.c \
	libft/ft_putendl_fd.c \
	libft/ft_strdup.c \
	libft/ft_strtrim.c \
	libft/ft_atoi.c \
	libft/ft_isdigit.c \
	libft/ft_memmove.c \
	libft/ft_striteri.c \
	libft/ft_strlen.c \
	libft/ft_bzero.c \
	libft/ft_isprint.c \
	libft/ft_putnbr_fd.c \
	libft/ft_strmapi.c \
	libft/ft_substr.c \
	libft/ft_calloc.c \
	libft/ft_itoa.c \
	libft/ft_memset.c \
	libft/ft_strjoin.c \
	libft/ft_memchr.c \
	libft/ft_putstr_fd.c \
	libft/ft_strlcat.c \
	libft/ft_strncmp.c \
	libft/ft_tolower.c \
	libft/ft_isalnum.c \
	libft/ft_putchar_fd.c \
	libft/ft_split.c \
	libft/ft_strnstr.c \
	libft/ft_toupper.c \
	libft/ft_isalpha.c \
	libft/ft_memcmp.c \
	libft/ft_strchr.c \
	libft/ft_strlcpy.c \
	libft/ft_strrchr.c \
	libft/ft_lstnew.c \
	libft/ft_lstadd_front.c \
	libft/ft_lstsize.c \
	libft/ft_lstlast.c \
	libft/ft_lstadd_back.c \
	libft/ft_lstdelone.c \
	libft/ft_lstclear.c \
	libft/ft_lstiter.c \
	libft/ft_lstmap.c \
	gnl/get_next_line_utils.c \
	gnl/get_next_line.c \
	printf/ft_printf.c \
	printf/ft_printf_utils.c \

OBJS = ${SRCS:.c=.o}

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
		ar rcs ${NAME} ${OBJS}

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all
