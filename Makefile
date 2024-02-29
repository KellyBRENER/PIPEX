# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 15:53:15 by kbrener-          #+#    #+#              #
#    Updated: 2024/02/29 11:25:08 by kbrener-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME	= pipex
BONUS = pipex_bonus

# Compiler options
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g #-fsanitize=address

# Libft
LIBFT_PATH = ./library42/
LIBFT_LIB = $(LIBFT_PATH)library42.a

# program files
SRC		= 	pipex.c \
			pipex_utils.c \


SRC_BONUS	= pipex_bonus.c \
			pipex_utils.c \

OBJ		= $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

# Includes
INCLUDES = 	-I ./includes/\
			-I ./library42/\

all : $(BONUS) $(LIBFT_LIB) $(NAME)

# Compiling Libft
%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(LIBFT_LIB):
	@make -sC $(LIBFT_PATH)

# Compiling PIPEX
$(NAME): $(OBJ) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME) -g

# Compiling BONUS
$(BONUS): $(OBJ_BONUS) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT_LIB) -o $(BONUS) -g

clean:
	@make clean -sC $(LIBFT_PATH)
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_BONUS)


fclean: clean
	@make fclean -sC $(LIBFT_PATH)
	@rm -rf $(BONUS) $(LIBFT_LIB) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
