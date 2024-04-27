# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/29 11:50:28 by arcanava          #+#    #+#              #
#    Updated: 2024/04/27 17:01:24 by arcanava         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# TODO: Check Cflags!

NAME = so_long
DEBUG_NAME = so_long_debug

#----COLORS----#
DEF_COLOR = \033[1;39m
WHITE_BOLD = \033[1m
BLACK = \033[1;30m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
PINK = \033[1;35m
CIAN = \033[1;36m

#----COMPILER----#
CC = cc
CCFLAGS = -Wall -Werror -Wextra -g -O3 #-fsanitize=thread #-fsanitize=address

#----DIRS----#
BIN_DIR = bin/
INC_DIR = inc/
SRCS_DIR = src/
INCLUDES = -I$(INC_DIR) 

#----LIBFT----#
LIBFT_DIR = lib/libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a
INCLUDES += -I$(LIBFT_DIR) 

#----MLX----#
MLX_DIR = lib/mlx/
MLX_LIB_ALONE = libmlx.a
MLX_LIB = $(MLX_DIR)$(MLX_LIB_ALONE)
INCLUDES += -I$(MLX_DIR) 

#----MANDATORY----#
SRCS =	so_long.c \
		utils.c \
		map.c \
		map_utils.c \
		safe_utils.c \
		map_parser.c \
		actuator.c \
		player.c \
		position_stack.c \
		loader.c \
		window.c
OBJS = $(SRCS:%.c=$(BIN_DIR)%.o)
DEPS = $(OBJS:%.o=%.d)

#----BONUS----#
BSRCS = pipex_bonus.c \
		utils_bonus.c \
		safe_utils_bonus.c \
		initiators_bonus.c
BOBJS = $(BSRCS:%.c=$(BIN_DIR)%.o)
BDEPS = $(BOBJS:%.o=%.d)

#----DEBUG----#
ifdef DEBUG
	OBJS = $(SRCS:%.c=$(BIN_DIR)%_debug.o)
	BOBJS = $(BSRCS:%.c=$(BIN_DIR)%_debug.o)
	NAME = $(DEBUG_NAME)
endif

#----EXEC----#
EXEC_PROGRAM = ./$(NAME) input date cat cat ls output

#----OS COMPATIBILITY----#
ifneq ($(OS),Windows_NT)
	UNAME_S = $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		DARWIN_FLAGS = -framework OpenGL -framework AppKit
	else
		DARWIN_FLAGS = -lXext -lX11
	endif
else
	UNAME_S = Windows
endif

#----MACROS----#
export GNL_BUFFER_SIZE := 50000
ifeq ($(UNAME_S),Darwin)
	WINDOW_MAX_WIDTH := $(shell system_profiler -json SPDisplaysDataType 2>/dev/null | grep _spdisplays_resolution | awk '{print substr($$3, 2, length($$3)) - 70}')
	WINDOW_MAX_HEIGHT := $(shell system_profiler -json SPDisplaysDataType 2>/dev/null | grep _spdisplays_resolution | awk '{print $$5 - 70}')
	CCFLAGS += -D WINDOW_MAX_HEIGHT=$(WINDOW_MAX_HEIGHT) -D WINDOW_MAX_WIDTH=$(WINDOW_MAX_WIDTH)
endif

#----RULES----#
all:
	@$(MAKE) --no-print-directory make_mlx
	@$(MAKE) --no-print-directory make_libft
	@$(MAKE) --no-print-directory $(NAME)

ifndef BONUS
$(NAME): $(MLX_LIB) $(LIBFT_LIB) $(OBJS)
	@printf "$(BLUE)Linking objects and creating program...$(DEF_COLOR)\n"
	@$(CC) $(CCFLAGS) $(OBJS) $(LIBFT_LIB) -L$(MLX_DIR) -lmlx $(DARWIN_FLAGS) -o $(NAME)
	@echo "$(GREEN)[✓] $(PINK)$(NAME)$(GREEN) created!!!$(DEF_COLOR)"
else
$(NAME): $(MLX_LIB) $(LIBFT_LIB) $(BOBJS)
	@echo "$(BLUE)\nLinking objects and creating binary program...$(DEF_COLOR)"
	@$(CC) $(CCFLAGS) $(BOBJS) $(LIBFT_LIB) -L$(MLX_DIR) -lmlx $(DARWIN_FLAGS) -o $(NAME)
	@echo "$(GREEN)[✓] $(PINK)$(NAME) Bonus$(GREEN) created!!!$(DEF_COLOR)"
endif

ifndef DEBUG
$(BIN_DIR)%.o: $(SRCS_DIR)%.c Makefile
	@printf "$(CIAN)Compiling: $(PINK)$(notdir $<)...$(DEF_COLOR)\n"
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CCFLAGS) $(INCLUDES) -MMD -c $< -o $@
else
$(BIN_DIR)%_debug.o: $(SRCS_DIR)%.c Makefile
	@printf "$(CIAN)Compiling: $(PINK)$(notdir $<)...$(DEF_COLOR)\n"
	@mkdir -p $(BIN_DIR)
	@$(CC) -g $(CCFLAGS) $(INCLUDES) -MMD -c $< -o $@
endif

clean: libft_clean
	@rm -rf $(BIN_DIR)
	@echo "$(RED)bin/ deleted$(DEF_COLOR)"
	@-$(MAKE) mlx_clean --no-print-directory 

fclean: libft_fclean clean mainclean
	@rm -rf $(NAME) $(DEBUG_NAME) $(MLX_DIR)
	@echo "$(RED)Executable deleted$(DEF_COLOR)\n"

re: fclean all

bonus: 
	@$(MAKE) --no-print-directory BONUS=1

b: bonus

bonusre: fclean bonus

make_libft:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) bonus
	@echo ""

make_mlx: $(MLX_DIR)
	@$(MAKE) --no-print-directory -C $(MLX_DIR)
	@echo ""

mlx_clean:
	@$(MAKE) --no-print-directory -C $(MLX_DIR) clean
	@echo ""

libft_clean:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

libft_fclean:
	@echo "$(RED)Cleaning $(PINK)Libft$(RED)...$(DEF_COLOR)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

norme:
	@echo "$(YELLOW)\n------------------------\nChecking norme errors...\n------------------------\n$(DEF_COLOR)"
	@-norminette $(INC_DIR) $(SRCS_DIR)
	@echo ""

compmain: all
	@echo "\n$(GREEN)COMPILING MAIN FOR TESTING..."

main: compmain
	@echo "$(GREEN)\n------------\nMain result:\n------------\n$(DEF_COLOR)"
	@echo "see ./output\n"
	$(EXEC_PROGRAM)

m: main

n: norme

nm: norme main

mn: nm

leaks: compmain
	@echo "$(YELLOW)\n------------------------\nChecking leaks atExit...\n------------------------\n$(DEF_COLOR)"
	@-leaks -quiet -fullContent -atExit -- $(EXEC_PROGRAM)

mainclean:
	@rm -f main

test: norme leaks

t: test

debug:
	@$(MAKE) --no-print-directory all DEBUG=1

debug_bonus:
	@$(MAKE) --no-print-directory bonus DEBUG=1

$(MLX_DIR):
ifeq ($(OS),Windows_NT)
	@printf "$(RED)Not supported on windows. Sorry not sorry :)$(DEF_COLOR)"
else ifeq ($(UNAME_S),Darwin)
	@curl -O https://cdn.intra.42.fr/document/document/22167/minilibx_opengl.tgz
	@mv minilibx_opengl.tgz lib
	@rm -rf $(MLX_DIR)
	@mkdir -p $(MLX_DIR)
	@tar -xpf lib/minilibx_opengl.tgz -C $(MLX_DIR) --strip-components 1
	@rm -rf lib/minilibx_opengl.tgz
else
	@-sudo apt-get install gcc make xorg libxext-dev libbsd-dev curl clang
	@curl -O https://cdn.intra.42.fr/document/document/22166/minilibx-linux.tgz
	@mv minilibx-linux.tgz lib
	@rm -rf $(MLX_DIR)
	@mkdir -p $(MLX_DIR)
	@tar -xpf lib/minilibx-linux.tgz -C $(MLX_DIR) --strip-components 1
	@rm -rf lib/minilibx-linux.tgz
endif

install: $(MLX_DIR)
	@printf "$(GREEN)mlx downloaded and functional!\n$(DEF_COLOR)"

.PHONY: all \
		clean \
		fclean \
		re \
		bonus \
		bonusre \
		make_libft \
		libft_clean \
		libft_fclean \
		norme \
		main \
		m \
		n \
		nm \
		mn \
		leaks \
		compmain \
		mainclean \
		test \
		t \
		debug \
		b \
		install

-include $(DEPS)
-include $(BDEPS)
.SILENT:
