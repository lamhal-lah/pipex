# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 16:15:42 by lamhal            #+#    #+#              #
#    Updated: 2024/03/27 21:15:16 by lamhal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC = ft_split.c utils.c pipex.c main.c

OBJ = $(SRC:.c=.o)

SRC_B = bonus/ft_split.c bonus/utils_bonus.c bonus/pipex_bonus.c bonus/here_doc.c\
	bonus/main_bonus.c bonus/getn/get_next_line_utils.c \
	bonus/getn/get_next_line.c 

OBJ_B = $(SRC_B:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^

bonus: $(BONUS)

$(BONUS): $(OBJ_B)
	$(CC) -o $@ $^

bonus/%.o: bonus/%.c bonus/pipex_bonus.h bonus/getn/get_next_line.h
	$(CC) -o $@ -c $< $(CFLAGS)

%.o: %.c pipex.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ) $(OBJ_B)

fclean: clean
	rm -f $(NAME) $(BONUS)
	
re: fclean all

.PHONY: clean
