# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 16:50:15 by mgalvez           #+#    #+#              #
#    Updated: 2025/09/12 10:29:26 by mgalvez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC			= cc
CFLAGS		= -Wall -Werror -Wextra
MAKE		= make

SRCS		= ft_atof.c ft_atoi.c ft_atol.c ft_bzero.c ft_calloc.c \
			  ft_checkrepeatingnbrs.c ft_checksortednmbrs.c ft_cut_tabline.c \
			  ft_freetab.c ft_freentab.c ft_getbiggest.c ft_getmult.c ft_getnextline.c \
			  ft_getsmallest.c ft_indextab.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
			  ft_isdigit.c ft_isint.c ft_isoperator.c ft_isprint.c ft_isspace.c \
			  ft_isspacestr.c ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c \
			  ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c \
			  ft_lstnew.c ft_lstsize.c ft_makerngname.c ft_makernguint.c ft_max.c \
			  ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_min.c \
			  ft_nbrlen.c ft_printf.c ft_print_str_tab.c ft_pull.c ft_push.c \
			  ft_putaddress.c ft_putchar.c ft_putendl.c ft_putlng.c ft_putnbr.c \
			  ft_putstr.c ft_putstr_errnull.c ft_putunsint.c ft_split.c ft_split_free.c \
			  ft_strchr.c ft_strcmp.c ft_strdup.c ft_striteri.c ft_strjoin.c \
			  ft_strjoin_free.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
			  ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strrncmp.c ft_strtrim.c \
			  ft_strtrim_free.c ft_substr.c ft_swap.c ft_tabcpy.c ft_tablen.c \
			  ft_tolower.c ft_toupper.c

OBJS_LST	= ${SRCS:.c=.o}
OBJS_DIR	= .objs
OBJS		= ${addprefix ${OBJS_DIR}/, ${OBJS_LST}}

ERASE		= \033[2K\r
BLUE		= \033[34m
YELLOW		= \033[33m
GREEN		= \033[32m
END			= \033[0m

all: ${NAME}

${NAME}: ${OBJS}
	@ ar -rsc $@ $^
	@ printf "${ERASE}${GREEN}$@ made\n${END}"

${OBJS_DIR}/%.o: %.c
	@ mkdir -p ${OBJS_DIR}
	@ ${CC} ${FLAGS} -c -o $@ $<
	@ printf "${ERASE}${BLUE} > Compilation: ${END}$<"

clean:
	@ rm -rf ${OBJS_DIR}
	@ printf "${YELLOW}${OBJS_DIR} removed\n${END}"

fclean: clean
	@ rm -f ${NAME}
	@ printf "${YELLOW}${NAME} removed\n${END}"

re: fclean
	${MAKE} all

.PHONY: all clean fclean re
