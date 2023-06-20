# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgeslin42 <fgeslin42@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 13:25:46 by fgeslin           #+#    #+#              #
#    Updated: 2023/01/29 15:22:38 by fgeslin42        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= libft.a
CC			:= gcc
RM			:= rm -f
CFLAGS		= -Wall -Wextra -Werror

#####	SOURCES		############################################################
SRC			=	char/ft_isalnum.c \
				char/ft_isalpha.c \
				char/ft_isascii.c \
				char/ft_isdigit.c \
				char/ft_isprint.c \
				char/ft_tolower.c \
				char/ft_toupper.c \
				io/get_next_line.c \
				mem/ft_bzero.c \
				mem/ft_calloc.c \
				mem/ft_memchr.c \
				mem/ft_memcmp.c \
				mem/ft_memcpy.c \
				mem/ft_memmove.c \
				mem/ft_memset.c \
				print/ft_putchar_fd.c \
				print/ft_putendl_fd.c \
				print/ft_putnbr_fd.c \
				print/ft_putstr_fd.c \
				str/ft_atoi.c \
				str/ft_itoa.c \
				str/ft_split.c \
				str/ft_strchr.c \
				str/ft_strdup.c \
				str/ft_striteri.c \
				str/ft_strjoin.c \
				str/ft_strlcat.c \
				str/ft_strlcpy.c \
				str/ft_strlen.c \
				str/ft_strmapi.c \
				str/ft_strncmp.c \
				str/ft_strnjoin.c \
				str/ft_strnstr.c \
				str/ft_strrchr.c \
				str/ft_strtrim.c \
				str/ft_substr.c \
				lst/ft_lstadd_back.c \
				lst/ft_lstadd_front.c \
				lst/ft_lstclear.c \
				lst/ft_lstdelone.c \
				lst/ft_lstiter.c \
				lst/ft_lstlast.c \
				lst/ft_lstmap.c \
				lst/ft_lstnew.c \
				lst/ft_lstsize.c \
				ft_printf/ft_chrdup.c \
				ft_printf/ft_flagafter.c \
				ft_printf/ft_flagarg.c \
				ft_printf/ft_flagbefore.c \
				ft_printf/ft_flagcmp.c \
				ft_printf/ft_flagstr.c \
				ft_printf/ft_itoa_base.c \
				ft_printf/ft_itoa_ptr.c \
				ft_printf/ft_printf.c \
				ft_printf/ft_printfun.c \
				ft_printf/ft_putarg.c
OBJ			= $(SRC:.c=.o)

#####	Makefile  objs		###################################################
WHITE		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
PINK		:= \033[1;35m
CYAN 		:= \033[1;36m

.c.o:
	@ echo "$(YELLOW)Compiling: $(WHITE)$<"
	@ ${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	@ echo "$(GREEN)Compilation ${WHITE}of ${CYAN}$(NAME) ${WHITE}..."
	@ ar rcs $(NAME) $(OBJ)
	@ echo "$(CYAN)$(NAME) $(GREEN)created$(WHITE) ✔️"

clean:
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(WHITE) objs ✔️"
	@ ${RM} $(OBJ) $(OBJ_BONUS)

fclean: clean
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(WHITE) binary ✔️"
	@ ${RM} $(NAME)

re: fclean all

.PHONY:		all clean fclean re

