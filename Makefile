# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 15:53:15 by kbrener-          #+#    #+#              #
#    Updated: 2024/02/08 12:14:50 by kbrener-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

LIBFT = ./libft/libft.a

SRC = pipex.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
		@make -C ./libft

$(NAME): $(OBJ) $(LIBFT)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		@$(RM) -r $(OBJ)
		@make clean -C ./libft

fclean: clean
		@$(RM) $(NAME)
		@$(RM) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re bonus
