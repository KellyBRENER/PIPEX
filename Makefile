# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 15:53:15 by kbrener-          #+#    #+#              #
#    Updated: 2024/02/13 14:43:23 by kbrener-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

LIBFT = ./library42/libft.a

SRC = pipex.c

BONUS = pipex_bonus.c

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS:.c=.o)

all: $(NAME)

$(LIBFT):
		@make -C ./library42

$(NAME): $(OBJ) $(LIBFT)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		@$(RM) -r $(OBJ) $(BONUS_OBJ)
		@make clean -C ./libft

fclean: clean
		@$(RM) $(NAME)
		@$(RM) $(LIBFT)

re: fclean all

bonus: $(OBJ) $(BONUS_OBJ) $(LIBFT)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(BONUS_OBJ) $(LIBFT)

.PHONY: all clean fclean re bonus
