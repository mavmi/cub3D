# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: username <username@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/07 11:40:06 by pmaryjo           #+#    #+#              #
#    Updated: 2022/01/17 20:04:46 by username         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cub3D


HDRS_DIR		=	include
SRCS_DIR		=	srcs
GEOM_DIR		=	$(SRCS_DIR)/geometry
GNL_DIR			=	$(SRCS_DIR)/get_next_line
PAINTING_DIR	=	$(SRCS_DIR)/painting
PARSER_DIR		=	$(SRCS_DIR)/parser
UTILS_DIR		=	$(SRCS_DIR)/utils
LIBFT_DIR		=	libft
MLX_DIR			=	minilibx
MLX_LIN_DIR		=	minilibx_linux


LIBFT			=	$(LIBFT_DIR)/libft.a
MLX				=	$(MLX_DIR)/libmlx.a
MLX_LIN			=	$(MLX_LIN_DIR)/libmlx.a


HDRS			=	$(addprefix $(HDRS_DIR)/, geometry.h get_next_line.h painting.h parser.h utils.h)
SRCS			=	$(addprefix $(SRCS_DIR)/, main.c)\
					$(addprefix $(GEOM_DIR)/, geometry_1.c geometry_2.c geometry_3.c)\
					$(addprefix $(GNL_DIR)/, get_next_line.c get_next_line_utils.c)\
					$(addprefix $(PAINTING_DIR)/, painting_1.c painting_2.c  painting_movements_1.c\
							painting_movements_2.c painting_ray.c painting_utils.c)\
					$(addprefix $(PARSER_DIR)/, parser_1.c parser_convert_1.c parser_convert_2.c\
							parser_destroyers.c parser_getters.c parser_utils.c)\
					$(addprefix $(UTILS_DIR)/, utils_1.c)
OBJS			=	$(SRCS:.c=.o)
DEPEN			=	$(SRCS:.c=.d)


CC				=	gcc
GCC				=	$(CC) -Wall -Wextra -Werror -MMD -g
GCC_MLX			=	$(GCC) -framework OpenGL -framework AppKit
GCC_MLX_FL_LIN	=	-lXext -lX11 -lm -lz


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

#			@echo "$(BLUE)\n\t*** SRCS ***$(NC)"
#			@norminette $(SRCS_DIR)/*.c | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

			@echo "$(BLUE)\n\t*** GEOMETRY ***$(NC)"
			@norminette $(GEOM_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'
			
			@echo "$(BLUE)\n\t*** GNL ***$(NC)"
			@norminette $(GNL_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

			@echo "$(BLUE)\n\t*** PAINTING ***$(NC)"
			@norminette $(PAINTING_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

			@echo "$(BLUE)\n\t*** PARSER ***$(NC)"
			@norminette $(PARSER_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'

			@echo "$(BLUE)\n\t*** UTILS ***$(NC)"
			@norminette $(UTILS_DIR) | awk '{printf "$(CYAN)%s\n$(NC)", $$0 }'


###############################################


linux:			get_libft linux_get_mlx $(OBJS)
				$(GCC) $(OBJS) -L$(MLX_LIN_DIR) -lmlx_Linux -L/usr/lib -I$(MLX_LIN_DIR) $(GCC_MLX_FL_LIN) $(LIBFT) -o $(NAME)

linux_get_mlx:
				$(MAKE) -C $(MLX_LIN_DIR)

linux_clean:
				rm -f $(OBJS)
				rm -f $(DEPEN)
				$(MAKE) clean -C $(LIBFT_DIR)
				$(MAKE) clean -C $(MLX_LIN_DIR)

linux_fclean:	linux_clean
				rm -f $(NAME)
				$(MAKE) fclean -C $(LIBFT_DIR)

linux_re:		linux_fclean linux

-include $(DEPEN)

.PHONE: all clean fclean re get_libft get_mlx norm linux get_mlx_linux linux_clean linux_fclean linux_re
