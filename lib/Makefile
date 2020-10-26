# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/03 18:09:11 by judecuyp          #+#    #+#              #
#    Updated: 2020/03/26 23:23:32 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

HEADER_PATH = ./includes

CHAR = CHAR/ft_isalnum.c CHAR/ft_isalpha.c CHAR/ft_isascii.c \
	CHAR/ft_isdigit.c CHAR/ft_isprint.c CHAR/ft_tolower.c CHAR/ft_toupper.c
CONV = CONV/ft_atoi.c CONV/ft_itoa.c
GNL = GNL/get_next_line.c GNL/get_next_line_utils.c
MEM = MEM/ft_bzero.c MEM/ft_calloc.c MEM/ft_memccpy.c MEM/ft_memchr.c \
	MEM/ft_memcmp.c MEM/ft_memcpy.c MEM/ft_memmove.c MEM/ft_memset.c
PUT = PUT/ft_putchar_fd.c PUT/ft_putendl_fd.c PUT/ft_putnbr_fd.c \
		PUT/ft_putstr_fd.c
STR = STR/ft_find.c STR/ft_ilen.c STR/ft_split.c STR/ft_strchr.c \
	STR/ft_strcmp.c STR/ft_strdup.c STR/ft_strjoin.c STR/ft_strlcat.c \
	STR/ft_strlcpy.c STR/ft_strlen.c STR/ft_strmapi.c STR/ft_strncmp.c \
	STR/ft_strncpy.c STR/ft_strndup.c STR/ft_strnstr.c STR/ft_strrchr.c \
	STR/ft_strtrim.c STR/ft_substr.c STR/ft_strnjoin.c STR/ft_strcat.c \
	STR/ft_strcpy.c

OBJS = $(CHAR:.c=.o) $(CONV:.c=.o) $(GNL:.c=.o) $(MEM:.c=.o) $(PUT:.c=.o) \
	$(STR:.c=.o)

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
