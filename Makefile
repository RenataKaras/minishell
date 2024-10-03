# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rshaheen <rshaheen@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2024/04/09 16:12:46 by rkaras        #+#    #+#                  #
#    Updated: 2024/10/03 14:54:06 by rshaheen      ########   odam.nl          #
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
		builtin/pwd.c \
		builtin/echo.c \
		builtin/env.c \
		builtin/unset.c \
		builtin/cd.c \
		builtin/export.c \
		builtin/exit.c \
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
		expander/expander_split.c \
		execution/init_tree.c \
		execution/exec.c \
		execution/exec_heredoc.c \
		execution/display_error.c \
		execution/exec_smpl_cmd.c \
		execution/exec_redirec.c \
		execution/check_permission.c \
		execution/execute_builtin.c \
		execution/heredoc_expander.c \



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

