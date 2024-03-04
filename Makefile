# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 15:53:15 by kbrener-          #+#    #+#              #
#    Updated: 2024/03/04 14:13:10 by kbrener-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME	= pipex
BONUS	= pipex

# Compiler options
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g #-fsanitize=address

# Libft
LIBFT_PATH = ./libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a

# program files
SRC		= 	pipex.c \
			pipex_utils.c \


SRC_BONUS	= pipex_bonus.c \
			pipex_utils.c \

OBJ		= $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

# Includes
INCLUDES = 	-I ./includes/\
			-I ./libft/\

all : $(LIBFT_LIB) $(NAME)

# Compiling Libft
%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(LIBFT_LIB):
	@make -sC $(LIBFT_PATH)

# Compiling PIPEX
$(NAME): $(OBJ) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME) -g

# Compiling BONUS
bonus: $(OBJ_BONUS) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT_LIB) -o $(BONUS) -g

clean:
	@echo "les fichiers ont ete supprimes"
	@make clean -sC $(LIBFT_PATH)
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_BONUS)


fclean: clean
	@echo "les fichers ont ete supprimes"
	@make fclean -sC $(LIBFT_PATH)
	@rm -rf $(BONUS) $(LIBFT_LIB) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
