# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 15:53:15 by kbrener-          #+#    #+#              #
#    Updated: 2024/02/23 11:26:57 by kbrener-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

VPATH = ./libft/ ./printf/ ./gnl/

AR = ar

ARFLAGS = rc

CFLAGS = -Wall -Wextra -Werror

SRC_LIBFT = ft_isascii.c ft_memcpy.c ft_putendl_fd.c ft_strdup.c ft_strtrim.c \
      ft_atoi.c ft_isdigit.c ft_memmove.c ft_striteri.c ft_strlen.c \
      ft_bzero.c ft_isprint.c ft_putnbr_fd.c ft_strmapi.c ft_substr.c \
      ft_calloc.c ft_itoa.c ft_memset.c ft_strjoin.c ft_memchr.c \
      ft_putstr_fd.c ft_strlcat.c ft_strncmp.c ft_tolower.c ft_isalnum.c \
      ft_putchar_fd.c ft_split.c ft_strnstr.c ft_toupper.c ft_isalpha.c \
      ft_memcmp.c ft_strchr.c ft_strlcpy.c ft_strrchr.c ft_lstnew.c \
	  ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
	  ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

SRC_GNL = get_next_line_utils.c get_next_line.c

SRC_PRINTF = ft_printf_utils.c ft_printf.c

SRC_NAME = $(SRC_LIBFT) $(SRC_GNL) $(SRC_PRINTF)

OBJS_PATH = objs/

OBJS_NAME = $(SRC_NAME:%.c=%.o)

OBJS = $(addprefix $(OBJS_PATH),$(OBJS_NAME))

all: $(NAME)

$(NAME): $(OBJS)
		$(AR) $(ARFLAGS) $(NAME) $(OBJS)
		ranlib $(NAME)

$(OBJS_PATH)%.o: %.c
	@mkdir -p $(OBJS_PATH)
	@ $(CC) $(CFLAGS) -c $^ -o $@

clean:
		rm -f $(OBJS_PATH)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
