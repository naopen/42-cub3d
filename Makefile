# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/30 18:04:39 by nkannan           #+#    #+#              #
#    Updated: 2024/12/30 18:10:58 by nkannan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

LIBFT_DIR   = ./libft
LIBFT       = $(LIBFT_DIR)/libft.a

MLX_DIR     = ./minilibx
MLX         = $(MLX_DIR)/libmlx.a

# ソースとオブジェクト
SRCS_DIR    = ./srcs
OBJS_DIR    = ./objs

SRCS        = $(SRCS_DIR)/main.c \
				$(SRCS_DIR)/parse_config.c \
				$(SRCS_DIR)/parse_map.c \
				$(SRCS_DIR)/init.c \
				$(SRCS_DIR)/hooks.c \
				(SRCS_DIR)/raycast.c \
				$(SRCS_DIR)/draw.c \
				$(SRCS_DIR)/utils.c

OBJS        = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

INCLUDES    = -I ./includes -I $(MLX_DIR) -I $(LIBFT_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(MLX) -lm -o $(NAME)
	# macOS なら -framework OpenGL -framework AppKit を追加
	# Linux なら -lXext -lX11 -lm -lz などを追加
	@echo "cub3D has been compiled!"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@make -C $(MLX_DIR)

clean:
	@rm -rf $(OBJS_DIR)
	@make clean -C $(LIBFT_DIR) || true
	@make clean -C $(MLX_DIR) || true
	@echo "Objects cleaned!"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR) || true
	@echo "Full clean done!"

re: fclean all

bonus:
	@echo "Implement bonus if needed..."

.PHONY: all clean fclean re bonus