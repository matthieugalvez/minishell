# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 16:47:49 by mgalvez           #+#    #+#              #
#    Updated: 2025/01/30 18:07:07 by mmanuell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc 
CFLAGS = -Wall -Werror -Wextra
LIBS = -Llibft -lft -lreadline

DIR_SRCS = srcs
DIR_INCS = includes
DIR_OBJS = .objs
DIR_LIBFT = libft

BUILTINS_SRCS	= builtins.c env_builtins.c env_builtins_utils.c
EXEC_SRCS		= heredoc.c exec.c pathfinder.c exec_builtins.c
PARSING_SRCS	= line_spliter.c syntax_parsing.c expand.c expand_utils.c parsing_utils.c
TOKENIZE_SRCS	= tokenize_builtin.c tokenize_other.c unquote_strings.c \
				  get_redirect_fd.c tokenization_utils.c
VISUAL_SRCS		= prompt.c

LST_SRCS	= 	$(addprefix builtins/, ${BUILTINS_SRCS}) \
				$(addprefix exec/, ${EXEC_SRCS}) \
				$(addprefix parsing/, ${PARSING_SRCS}) \
				$(addprefix tokenization/, ${TOKENIZE_SRCS}) \
				$(addprefix visual/, ${VISUAL_SRCS}) \
				main.c \
				print_linetab.c ##A SUPPRIMER !!

LST_OBJS = $(LST_SRCS:.c=.o)
LST_INCS = minishell.h

SRCS = $(addprefix ${DIR_SRCS}/, ${LST_SRCS})
OBJS = $(addprefix $(DIR_OBJS)/, ${LST_OBJS})
INCS = $(addprefix $(DIR_INCS)/, ${LST_INCS})

ERASE		=	\033[2K\r
BLUE		=	\033[34m
YELLOW		=	\033[33m
GREEN		=	\033[32m
END			=	\033[0m

$(DIR_OBJS)/%.o: ${DIR_SRCS}/%.c $(INCS) Makefile libft/libft.a
	@ mkdir -p $(DIR_OBJS)
	@ mkdir -p $(DIR_OBJS)/builtins
	@ mkdir -p $(DIR_OBJS)/data
	@ mkdir -p $(DIR_OBJS)/exec
	@ mkdir -p $(DIR_OBJS)/parsing
	@ mkdir -p $(DIR_OBJS)/tokenization
	@ mkdir -p $(DIR_OBJS)/visual
	@ $(CC) $(CFLAGS) -I $(DIR_INCS) -c $< -o $@
	@ printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

all : libft ${NAME}

$(NAME):	$(OBJS)
	@ $(CC) $(CFLAGS) $(OBJS) ${LIBS} -o $@
	@ printf "$(ERASE)$(GREEN)$@ made\n$(END)"

libft :
	@ make -C $(DIR_LIBFT)

clean:
	@ printf "$(YELLOW)$(DIR_OBJS) removed$(END)\n"
	@ rm -rdf $(DIR_OBJS)
	@ printf "libft : "
	@ make clean -C $(DIR_LIBFT)

fclean:		clean
	@ printf "$(YELLOW)$(NAME) removed$(END)\n"
	@ rm -rf $(NAME) fsanitize g3
	@ printf "libft : "
	@ make fclean -C $(DIR_LIBFT)

re:	fclean all

fsanitize : libft
	$(CC) -fsanitize=address -g $(SRCS) -I $(DIR_INCS) $(CFLAGS) ${LIBS} -o $@

g3 : libft
	$(CC) -g3 $(SRCS) -I $(DIR_INCS) $(CFLAGS) ${LIBS} -o $@
	
.PHONY: all clean fclean re libft fsanitize g3
