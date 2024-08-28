# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rkaras <rkaras@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2024/04/09 16:12:46 by rkaras        #+#    #+#                  #
#    Updated: 2024/08/28 15:29:50 by rkaras        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = ./Libft/libft.a
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline

SOURCE = main.c \
			parsing/env_parser.c \
			tokenizing/tokenize.c \
			tokenizing/tokenizing_utils.c \
			tokenizing/token_list.c \
			tokenizing/token_adder.c \


OBJECTS = $(SOURCE:%.c=%.o)

all: $(NAME)

$(LIBFT):
		@$(MAKE) -C ./Libft

$(NAME): $(LIBFT) $(OBJECTS)
		@cc $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME) $(LDFLAGS)

%.o:%.c
	@cc $(CFLAGS) -c -o $@ $^

clean:
	@$(MAKE) clean -C ./Libft
	@rm -f $(OBJECTS)

fclean:	clean
	@$(MAKE) fclean -C $ ./Libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
