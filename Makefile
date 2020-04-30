# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/26 16:03:23 by marvin            #+#    #+#              #
#    Updated: 2020/03/26 16:03:23 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell
HEADER_PATH = ./includes
LIB_PATH = ./lib/libft.a
LIB_REPO_PATH = ./lib
SRCS = srcs/main.c srcs/ft_free.c srcs/utils.c srcs/ft_exit.c srcs/ft_echo.c \
	srcs/ft_splitq.c srcs/ft_append.c srcs/ft_getenv.c srcs/free_tabs.c \
	srcs/env.c srcs/export.c srcs/launch_exec.c srcs/ft_cd.c srcs/parsing.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

all: libft_make $(NAME)

$(NAME):	$(OBJS)
			@echo "Compiling $@"
			@$(CC) $(CFLAGS) $(OBJS) $(LIB_PATH) -o $@ -I $(HEADER_PATH)
			@echo "Success"
.c.o:
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_PATH)

clean:
	@echo "Removing .o"
	@$(RM) $(OBJS)

fclean:	clean
		@echo "Removing Minishell"
		@$(RM) $(NAME)

re: fclean all

libft_make:
	make -C $(LIB_REPO_PATH) all


rec: fclean all
	@echo "Removing .o"
	@$(RM) $(OBJS)
	@echo "Removing lib .o"
	@make -C $(LIB_REPO_PATH) clean

.PHONY: all clean fclean re rec