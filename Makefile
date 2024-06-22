# **************************************************************************** #
#                                                                              #

#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/16 10:39:52 by Gecko             #+#    #+#              #
#    Updated: 2023/08/06 17:52:47 by Gecko            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC	=	string/ft_atoi.c		\
		string/ft_bzero.c		\
		string/ft_isalnum.c	\
		string/ft_isalpha.c	\
		string/ft_isascii.c	\
		string/ft_isdigit.c	\
		string/ft_isprint.c	\
		string/ft_itoa.c		\
		string/ft_split.c		\
		string/ft_split_charset.c		\
		string/ft_strchr.c		\
		string/ft_strdup.c		\
		string/ft_striteri.c	\
		string/ft_strjoin.c	\
		string/ft_strlcat.c 	\
		string/ft_strlcpy.c	\
		string/ft_strcpy.c	\
		string/ft_strlen.c 	\
		string/ft_strmapi.c	\
		string/ft_strncmp.c	\
		string/ft_strnstr.c	\
		string/ft_strrchr.c	\
		string/ft_strtrim.c	\
		string/ft_substr.c		\
		string/ft_tolower.c	\
		string/ft_toupper.c	\
		string/ft_strcmp.c		\
		string/ft_tabtablen.c		\
		string/ft_tabtabheigth.c		\
		string/ft_affix.c		\
		string/ft_strtolower.c \
		string/ft_sorttabtab.c \
		string/ft_strstr.c \
		string/ft_strncat.c \
		string/ft_isblank.c \
		mem/ft_calloc.c		\
		mem/ft_realloc.c		\
		mem/ft_memchr.c		\
		mem/ft_memcmp.c		\
		mem/ft_memcpy.c		\
		mem/ft_memmove.c	\
		mem/ft_memset.c		\
		io/ft_putchar_fd.c	\
		io/ft_putendl_fd.c	\
		io/ft_putnbr_fd.c	\
		io/ft_putstr_fd.c	\
		math/ft_abs.c \
		allocator/allocator.c		\
		allocator/allocator_warpers.c \
		allocator/mlist_utils.c		\
		allocator/mlist_utils2.c		\
		get_next_line/get_next_line.c \
		containers/ft_lst.c \
		containers/ft_vector.c \
		containers/ft_string.c \
		containers/ft_stack.c

OBJS = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3
RM = rm -rf
AR = ar crs

$(NAME): $(OBJS)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
