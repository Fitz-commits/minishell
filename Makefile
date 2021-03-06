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

NAME = minishell
HEADER_PATH = ./includes
LIB_PATH = ./lib/libft.a
LIB_REPO_PATH = ./lib
SRCS = srcs/main.c srcs/ft_free.c srcs/utils.c srcs/ft_exit.c srcs/ft_echo.c \
	srcs/ft_getenv.c srcs/utils3.c srcs/utils4.c srcs/ft_ext.c\
	srcs/env.c srcs/ft_export.c srcs/launch_exec.c srcs/ft_cd.c srcs/parsing.c \
	srcs/ft_unset.c srcs/expansions.c srcs/quote_removal.c  srcs/redirect.c \
	srcs/signal.c srcs/pipes.c srcs/utils2.c srcs/set_std.c srcs/ft_pwd.c \
	srcs/permission_check.c srcs/ft_errors.c srcs/buf_cmd.c srcs/redir_utils.c \
	srcs/parsing_utils.c srcs/set_err.c srcs/parsing_utils2.c \
	srcs/ft_export_other.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
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
	@echo "Removing lib .o"
	@make -C $(LIB_REPO_PATH) clean

fclean:	clean
		@echo "Removing Minishell"
		@$(RM) $(NAME)
		@make -C $(LIB_REPO_PATH) fclean

re: fclean all

libft_make:
	make -C $(LIB_REPO_PATH) all


rec: fclean all
	@echo "Removing .o"
	@$(RM) $(OBJS)
	@echo "Removing lib .o"
	@make -C $(LIB_REPO_PATH) clean

.PHONY: all clean fclean re rec
