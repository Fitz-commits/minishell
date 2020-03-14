# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/03 18:09:11 by judecuyp          #+#    #+#              #
#    Updated: 2020/03/03 20:49:44 by judecuyp         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mylib.a

HEADER_PATH = ./includes

SRCS = $(wildcard ./*/*.c) \
		$(wildcard ./PUT/fpf/*.c)

OBJS = $(SRCS:.c=.o)
OBJS_CHAR = $(SRCS_CHAR:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
all: $(NAME)

$(NAME):	$(OBJS)
			@echo "Making lib"
			@ar rc $(NAME) $(OBJS)
.c.o:
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_PATH)

clean:
	@echo "Removing .o"
	@$(RM) $(OBJS)

fclean:	clean
		@echo "Removing lib"
		@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
