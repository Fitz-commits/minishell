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
SRCS = srcs/main.c srcs/ft_free.c srcs/utils.c srcs/ft_exit.c srcs/ft_echo.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

all: $(NAME)

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

rec: fclean all
	@echo "Removing .o"
	@$(RM) $(OBJS)

.PHONY: all clean fclean re rec