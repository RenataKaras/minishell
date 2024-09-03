# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rshaheen <rshaheen@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2023/10/24 12:28:12 by rkaras        #+#    #+#                  #
#    Updated: 2024/09/02 15:42:06 by rshaheen      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
AR = ar -rsc

LIBRARY = libft
SRCS = ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_atoi.c \
			ft_atol.c \
			ft_itoa.c \
			ft_split.c \
			ft_strchr.c \
			ft_strcmp.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			get_next_line_utils.c \
			get_next_line.c \
			ft_inthex.c \
			ft_itoa_printf.c \
			ft_pointhex.c \
			ft_printf.c \
			ft_putchar_printf.c \
			ft_putnbr_printf.c \
			ft_putstr_printf.c \
			ft_lstadd_back_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstmap_bonus.c \
			ft_lstnew_bonus.c \
			ft_lstsize_bonus.c \

OBJS = $(SRCS:.c=.o)

OBJS_B = $(BSRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)

bonus: $(OBJS_B)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
	ar rc $(NAME) $@

clean:
	$(RM) $(OBJS) $(OBJS_B)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus