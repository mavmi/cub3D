# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/07 11:40:06 by pmaryjo           #+#    #+#              #
#    Updated: 2022/03/19 16:04:23 by pmaryjo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					=	cub3D


HDRS_DIR				=	include
SRCS_DIR				=	srcs
GEOM_DIR				=	$(SRCS_DIR)/geometry
GNL_DIR					=	$(SRCS_DIR)/get_next_line

PAINTING_DIR			=	$(SRCS_DIR)/painting
PAINTING_MINIMAP_DIR	=	$(PAINTING_DIR)/painting_minimap
PAINTING_MOVE_DIR		=	$(PAINTING_DIR)/painting_movements
PAINTING_RAY_DIR		=	$(PAINTING_DIR)/painting_ray
PAINTING_ROOM_DIR		=	$(PAINTING_DIR)/painting_room

PARSER_DIR				=	$(SRCS_DIR)/parser
PARSER_MAP_DIR			=	$(PARSER_DIR)/map_parser
PARSER_ARGUMS_DIR		=	$(PARSER_DIR)/argums_parser

UTILS_DIR				=	$(SRCS_DIR)/utils
LIBFT_DIR				=	libft
MLX_DIR					=	minilibx


LIBFT				=	$(LIBFT_DIR)/libft.a
MLX					=	$(MLX_DIR)/libmlx.a


HDRS				=	$(addprefix $(HDRS_DIR)/, geometry.h get_next_line.h painting.h parser.h utils.h)
SRCS				=	$(addprefix $(SRCS_DIR)/, main.c)\
						$(addprefix $(GEOM_DIR)/, geometry_1.c geometry_2.c geometry_3.c)\
						$(addprefix $(GNL_DIR)/, get_next_line.c get_next_line_utils.c)\
						\
						$(addprefix $(PAINTING_DIR)/, painting_freeNexit.c painting_event_handlers.c painting_files.c painting_main.c painting_utils.c)\
						$(addprefix $(PAINTING_MINIMAP_DIR)/, painting_minimap_1.c painting_minimap_2.c)\
						$(addprefix $(PAINTING_MOVE_DIR)/, painting_movements_1.c)\
						$(addprefix $(PAINTING_RAY_DIR)/, painting_ray_1.c painting_ray_2.c painting_ray_3.c\
								painting_ray_4.c painting_ray_5.c painting_ray_6.c painting_ray_7.c painting_ray_8.c)\
						$(addprefix $(PAINTING_ROOM_DIR)/, painting_room_1.c painting_room_2.c)\
						\
						$(addprefix $(PARSER_DIR)/, parsing_start.c parsing_utils.c parsing_errors.c\
								parsing_valid_check.c)\
						$(addprefix $(PARSER_MAP_DIR)/map_, parser_convert_1.c parser_convert_2.c\
								parser_destroyers.c parser_getters.c parser_utils_1.c parser_valid_1.c\
								parser_valid_2.c)\
						$(addprefix $(PARSER_ARGUMS_DIR)/arg_, parser_destroyers.c parser_floor_ceiling.c\
								 parser_getters.c parser_textures.c)\
						\
						$(addprefix $(UTILS_DIR)/, utils_1.c utils_2.c)
OBJS				=	$(SRCS:.c=.o)
DEPEN				=	$(SRCS:.c=.d)


CC				=	gcc
GCC				=	$(CC) -Wall -Wextra -Werror -MMD -g
GCC_MLX			=	$(GCC) -framework OpenGL -framework AppKit


# Norminette colors
BLUE		=	\033[34m
CYAN		=	\033[36m
NC			=	\033[0m


%.o:		%.c $(HDRS)
			$(GCC) -c -o $@ $<

all:		get_libft get_mlx $(NAME)

$(NAME):	$(OBJS)
			$(GCC_MLX) $(LIBFT) $(MLX) $(OBJS) -o $(NAME)

clean:
			rm -f $(OBJS)
			rm -f $(DEPEN)
			$(MAKE) clean -C $(LIBFT_DIR)
			$(MAKE) clean -C $(MLX_DIR)

fclean:		clean
			rm -f $(NAME)
			$(MAKE) fclean -C $(LIBFT_DIR)

re:			fclean all

get_libft:
			$(MAKE) -C $(LIBFT_DIR)

get_mlx:
			$(MAKE) -C $(MLX_DIR)

norm:
			@echo "$(BLUE)\n\t*** HEADERS ***$(NC)"
			@norminette $(HDRS_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

			@echo "$(BLUE)\n\t*** SRCS ***$(NC)"
			@norminette $(SRCS_DIR)/*.c | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

			@echo "$(BLUE)\n\t*** GEOMETRY ***$(NC)"
			@norminette $(GEOM_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

			@echo "$(BLUE)\n\t*** GNL ***$(NC)"
			@norminette $(GNL_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

			@echo "$(BLUE)\n\t*** PAINTING ***$(NC)"
			@norminette $(PAINTING_DIR)/*.c | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

			@echo "$(BLUE)\n\t*** PAINTING MINIMAP ***$(NC)"
			@norminette $(PAINTING_MINIMAP_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

			@echo "$(BLUE)\n\t*** PAINTING MOVEMENTS ***$(NC)"
			@norminette $(PAINTING_MOVE_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

			@echo "$(BLUE)\n\t*** PAINTING RAY ***$(NC)"
			@norminette $(PAINTING_RAY_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

			@echo "$(BLUE)\n\t*** PAINTING ROOM ***$(NC)"
			@norminette $(PAINTING_ROOM_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

			@echo "$(BLUE)\n\t*** PARSER ***$(NC)"
			@norminette $(PARSER_DIR)/*.c | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

			@echo "$(BLUE)\n\t*** PARSER_ARGUMS ***$(NC)"
			@norminette $(PARSER_ARGUMS_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

			@echo "$(BLUE)\n\t*** PARSER_MAP ***$(NC)"
			@norminette $(PARSER_MAP_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

			@echo "$(BLUE)\n\t*** UTILS ***$(NC)"
			@norminette $(UTILS_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

-include $(DEPEN)

.PHONE: all clean fclean re get_libft get_mlx norm
