# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rshaheen <rshaheen@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2024/04/09 16:12:46 by rkaras        #+#    #+#                  #
#    Updated: 2024/09/03 17:50:16 by rshaheen      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = ./Libft/libft.a
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline

SOURCE = main.c \
		free.c \
		env_list.c \
		env_list_utils.c \
		execute_builtin.c \
		builtin/pwd.c \
		builtin/echo.c \
		builtin/env.c \
		

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
	@$(MAKE) fclean -C ./Libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re