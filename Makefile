# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arivera <marvin@42quebec.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 13:26:56 by fgeslin           #+#    #+#              #
#    Updated: 2023/08/15 11:50:21 by arivera          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#####	CONFIG		############################################################
MINIRT		:= miniRT
LIBFT		:= lib/libft/libft.a
MLX42		:= lib/MLX42/build/libmlx42.a
CC			:= gcc
AR			:= ar -rcs
RM			:= rm -f
CFLAGS		= -Wall -Wextra -Werror
PARS_DIR	:= src/parsing/

#####	SOURCES		############################################################
SRC			=	src/main.c \
				src/rendering.c \
				src/renderingthread.c \
				src/color.c \
				src/mathplus.c \
				src/primitives.c \
				src/vector3.c \
				src/cleaning.c \
				src/mlxhooks.c \
				$(PARS_DIR)assign_values.c \
				$(PARS_DIR)file_parsing.c \
				$(PARS_DIR)free_parsing.c \
				$(PARS_DIR)input_parsing.c \
				$(PARS_DIR)int_float_parse.c \
				$(PARS_DIR)main_elem_parse.c \
				$(PARS_DIR)mand_objs.c \
				$(PARS_DIR)parsing_error.c \
				$(PARS_DIR)parsing_utils.c \
				$(PARS_DIR)parsing.c \
				$(PARS_DIR)struct3_parse.c \
				$(PARS_DIR)ft_split.c \

OBJ			=	$(SRC:.c=.o)

INC			=	./include
INC_LIBFT	=	./lib/libft/inc
INC_MLX42	=	./lib/MLX42/include/MLX42

#####	Makefile  objs		###################################################
WHITE		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
CYAN 		:= \033[1;36m

.c.o:
	@ echo "$(YELLOW)Compiling: $(WHITE)$<"
	@ ${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I$(INC) -I$(INC_LIBFT) -I$(INC_MLX42)

# ------ #

all: $(LIBFT) $(MLX42) $(MINIRT) $(CLIENT)

$(MINIRT): $(OBJ)
	@ echo "$(GREEN)Compilation ${WHITE}of ${CYAN}$(MINIRT) ${WHITE}..."
	@ $(CC) -o $(MINIRT) $(OBJ) $(MLX42) $(LIBFT) -lglfw -L"/Users/$(USER)/homebrew/opt/glfw/lib/"
	@ echo "$(CYAN)$(MINIRT) $(GREEN)created$(WHITE) ✔️"

# ------ #

$(LIBFT):
	@ echo "$(GREEN)Compilation ${WHITE}of ${CYAN}${LIBFT} ${WHITE}..."
	@ $(MAKE) -C lib/libft/
	@ echo "$(CYAN)$(LIBFT) $(GREEN)created$(WHITE) ✔️"

$(MLX42):
	@ echo "$(GREEN)Compilation ${WHITE}of ${CYAN}${MLX42} ${WHITE}..."
	@ cmake lib/MLX42 -B lib/MLX42/build && make -C lib/MLX42/build -j4
	@ echo "$(CYAN)$(LIBFT) $(GREEN)created$(WHITE) ✔️"

# ------ #

clean:
	@ ${RM} $(OBJ)
	@ $(MAKE) clean -C lib/libft/
	@ echo "$(RED)Deleting $(CYAN)$(MINIRT) $(WHITE)objs ✔️"

fclean: clean
	@ ${RM} $(MINIRT)
	@ $(MAKE) fclean -C lib/libft/
	@ echo "$(RED)Deleting $(CYAN)$(MINIRT) $(WHITE)binary ✔️"

re: fclean all

check_leak:
	@valgrind --show-leak-kinds=all --track-origins=yes --leak-check=full ./miniRT

check_parsing:
	@bash tests/parsing.sh

.PHONY: all clean fclean re
