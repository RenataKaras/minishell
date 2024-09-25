# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rshaheen <rshaheen@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2024/04/09 16:12:46 by rkaras        #+#    #+#                  #
#    Updated: 2024/09/25 16:18:49 by rkaras        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = ./Libft/libft.a
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline

SOURCE = main.c \
		free.c \
		make_env_list.c \
		env_list_utils.c \
		execute_builtin.c \
		builtin/pwd.c \
		builtin/echo.c \
		builtin/env.c \
		builtin/unset.c \
		builtin/cd.c \
		builtin/export.c \
		signals.c \
		tokenizing/tokenize.c \
		tokenizing/tokenizing_utils.c \
		tokenizing/token_list.c \
		tokenizing/token_adder.c \
		parsing/parser.c \
		parsing/parser_utils.c \
		parsing/parser_cleaner.c \
		parsing/parser_helpers.c \
		parsing/parser_lists.c \
		expander/expand_utils.c \
		expander/expand.c \
		expander/expand_helpers.c \



OBJECTS = $(SOURCE:%.c=%.o)

all: $(NAME)

$(LIBFT):
		@$(MAKE) -C ./Libft

$(NAME): $(LIBFT) $(OBJECTS)
		@cc $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME) $(LDFLAGS)

%.o:%.c
	@cc $(CFLAGS) -c  $< -o $@

clean:
	@$(MAKE) clean -C ./Libft
	@rm -f $(OBJECTS)

fclean:	clean
	@$(MAKE) fclean -C ./Libft
	@rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re

