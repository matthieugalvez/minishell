# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 16:47:49 by mgalvez           #+#    #+#              #
#    Updated: 2025/09/10 12:16:41 by mgalvez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CC				= cc
CFLAGS			= -Wall -Werror -Wextra
LIBS			= -Llibft -lft -lreadline
MAKE			= make

DIR_SRCS		= srcs
DIR_INCS		= includes
DIR_OBJS		= .objs
DIR_LIBFT		= libft

BUILTINS_SRCS	= builtins.c env_builtins.c env_builtins_utils.c ft_echo.c ft_cd.c ft_unset_export.c
EXEC_SRCS		= exec.c pathfinder.c
EXPAND_SRCS		= expand.c expand_parts.c expand_utils.c split_expand.c split_expand_utils.c
PARSING_SRCS	= line_spliter.c syntax_parsing.c init_tokenization.c parsing_utils.c
REDIRECT_SRCS	= get_redirect_fd.c heredoc.c redirect_fd_utils.c
SIGNAL_SRCS		= signal_handler.c
TOKENIZE_SRCS	= tokenize_builtin.c tokenize_other.c tokenization_utils.c
UNQUOTE_SRCS	= unquote_strings.c
VISUAL_SRCS		= prompt.c title.c

LST_SRCS		= 	$(addprefix builtins/, ${BUILTINS_SRCS}) \
					$(addprefix exec/, ${EXEC_SRCS}) \
					$(addprefix expand/, ${EXPAND_SRCS}) \
					$(addprefix parsing/, ${PARSING_SRCS}) \
					$(addprefix redirect/, ${REDIRECT_SRCS}) \
					$(addprefix signal/, ${SIGNAL_SRCS}) \
					$(addprefix tokenization/, ${TOKENIZE_SRCS}) \
					$(addprefix unquote/, ${UNQUOTE_SRCS}) \
					$(addprefix visual/, ${VISUAL_SRCS}) \
					main.c \
					utils.c

LST_OBJS		= $(LST_SRCS:.c=.o)
LST_INCS		= minishell.h

SRCS			= $(addprefix ${DIR_SRCS}/, ${LST_SRCS})
OBJS			= $(addprefix $(DIR_OBJS)/, ${LST_OBJS})
INCS			= $(addprefix $(DIR_INCS)/, ${LST_INCS})

ERASE			= \033[2K\r
BLUE			= \033[34m
YELLOW			= \033[33m
GREEN			= \033[32m
END				= \033[0m

$(DIR_OBJS)/%.o: ${DIR_SRCS}/%.c $(INCS) Makefile libft/libft.a
	@ mkdir -p $(DIR_OBJS)
	@ mkdir -p $(DIR_OBJS)/builtins
	@ mkdir -p $(DIR_OBJS)/exec
	@ mkdir -p $(DIR_OBJS)/expand
	@ mkdir -p $(DIR_OBJS)/parsing
	@ mkdir -p $(DIR_OBJS)/redirect
	@ mkdir -p $(DIR_OBJS)/signal
	@ mkdir -p $(DIR_OBJS)/tokenization
	@ mkdir -p $(DIR_OBJS)/unquote
	@ mkdir -p $(DIR_OBJS)/visual
	@ $(CC) $(CFLAGS) -I $(DIR_INCS) -c $< -o $@
	@ printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

all: libft
	$(MAKE) $(NAME)

$(NAME): $(OBJS)
	@ $(CC) $(CFLAGS) $(OBJS) ${LIBS} -o $@
	@ printf "$(ERASE)$(GREEN)$@ made\n$(END)"

libft:
	@ make -C $(DIR_LIBFT)

clean:
	@ printf "$(YELLOW)$(DIR_OBJS) removed$(END)\n"
	@ rm -rdf $(DIR_OBJS)
	@ printf "libft: "
	@ make clean -C $(DIR_LIBFT)

fclean: clean
	@ printf "$(YELLOW)$(NAME) removed$(END)\n"
	@ rm -rf $(NAME) fsanitize g3
	@ printf "libft: "
	@ make fclean -C $(DIR_LIBFT)

re: fclean
	$(MAKE) all

fsanitize: libft
	$(CC) -fsanitize=address -g $(SRCS) -I $(DIR_INCS) $(CFLAGS) ${LIBS} -o $@

g3: libft
	$(CC) -g3 $(SRCS) -I $(DIR_INCS) $(CFLAGS) ${LIBS} -o $@
	
.PHONY: all clean fclean re libft fsanitize g3
