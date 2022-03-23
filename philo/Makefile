# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 16:59:53 by rohoarau          #+#    #+#              #
#    Updated: 2022/03/10 13:33:00 by rohoarau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	philo
OBJ_DIR		=	obj/
SRCS_DIR	=	src/
SRCS		=	main.c				\
				utils.c				\
				init.c				\
				routine.c

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

CFLAGS = -Wall -Wextra -Werror
DEBUGGING = -ggdb
PTHREAD = -pthread
CC = gcc
RM = rm -rf
AR = ar rc

all: $(NAME)

$(OBJ_DIR)%.o : $(SRCS_DIR)%.c
		@mkdir -p $(OBJ_DIR)
		$(CC) -c $(CFLAGS) $(DEBUGGING) $(PTHREAD) $< -o $@

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(PTHREAD) $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJ_DIR)
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean re fclean
