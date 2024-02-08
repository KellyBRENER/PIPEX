# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 15:53:15 by kbrener-          #+#    #+#              #
#    Updated: 2024/02/05 16:06:11 by kbrener-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a

CC = cc

AR = ar

ARFLAGS = rc

CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = ./libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a

SRC = pipex.c

BONUS = pipex_bonus.c

OBJ = $(SRC:.c=.o)

INCLUDES = -I ./includes/\
					-I ./libft/\

BONUS_OBJ = $(BONUS:.c=.o)

all: $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJ)
		$(AR) $(ARFLAGS) $(NAME) $(OBJ) $(LIBFT_LIB)
		ranlib $(NAME)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDES)

$(LIBFT_LIB):
		@make -sC $(LIBFT_PATH)

clean:
		rm -f $(OBJ) $(BONUS_OBJ) $(LIBFT_PATH)

fclean: clean
		rm -f $(NAME) $(LIBFT_LIB)

re: fclean all

bonus: $(OBJ) $(BONUS_OBJ)
	ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)

.PHONY: all clean fclean re bonus
