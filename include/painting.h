/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:13:18 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/14 20:07:43 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAINTING_H
# define PAINTING_H

# include <math.h>

# include "../minilibx/mlx.h"

# include "parser.h"
# include "painting.h"

# define PIXEL_SIZE 50

// PLAYER_RAD and STEP are relative
# define PLAYER_RAD 0.2
# define STEP 0.31
# define EPS 0.2

# define WIDTH 2000
# define HEIGHT 1000

# define ESC 53
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

typedef enum e_color		t_color;
typedef struct s_painting	t_painting;
typedef struct s_movements	t_movements;

enum	e_color{
	WHITE,
	RED,
	BLACK
};

struct s_painting
{
	t_map	*map;
	void	*mlx;
	void	*win;
};

struct s_movements
{
	int		sq_x;
	int		sq_y;
	double	pl_x;
	double	pl_y;
};

// painting_1.c
void	paint_init(t_map *map);

// painting_2.c
void	paint_draw_pixel(t_painting *painting,
			size_t x, size_t y, t_color color);
void	paint_draw_player(t_painting *painting, t_color color);
void	paint_draw_map(t_painting *painting);

// painting_utils.c
double	paint_get_dist(double x1, double y1, double x2, double y2);

// painting_movements_1.c
void	paint_move_left(t_painting *painting);
void	paint_move_right(t_painting *painting);
void	paint_move_up(t_painting *painting);
void	paint_move_down(t_painting *painting);

// painting_movements_2.c
int		paint_is_move_left(t_painting *painting);
int		paint_is_move_right(t_painting *painting);
int		paint_is_move_up(t_painting *painting);
int		paint_is_move_down(t_painting *painting);

#endif
