# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 16:47:49 by mgalvez           #+#    #+#              #
#    Updated: 2025/01/23 16:47:51 by mgalvez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc 
CFLAGS = -Wall -Werror -Wextra
LIBS = -Llibft -lft -lreadline

DIR_SRCS = srcs
DIR_INCS = includes
DIR_OBJS = .objs

LST_SRCS =	main.c \
			prompt.c

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
	@ $(CC) $(CFLAGS) -I $(DIR_INCS) -c $< -o $@
	@ printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

all : libft ${NAME}

$(NAME):	$(OBJS)
	@ $(CC) $(CFLAGS) $(OBJS) ${LIBS} -o $@
	@ printf "$(ERASE)$(GREEN)$@ made\n$(END)"

libft/libft.a :
	@ make -C libft

clean:
	@ printf "$(YELLOW)$(DIR_OBJS) removed$(END)\n"
	@ rm -rdf $(DIR_OBJS)
	@ printf "libft : "
	@ make clean -C libft

fclean:		clean
	@ printf "$(YELLOW)$(NAME) removed$(END)\n"
	@ rm -rf $(NAME) bonus
	@ printf "libft : "
	@ make fclean -C libft

re:	fclean all

debug : libft/libft.a
	$(CC) -g3 $(SRCS) -I $(DIR_INCS) $(CFLAGS) ${LIBS} -o $@

.PHONY: all clean fclean re libft
