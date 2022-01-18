/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:13:18 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/18 20:27:57 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAINTING_H
# define PAINTING_H

# include <math.h>

# include "../minilibx/mlx.h"

# include "parser.h"
# include "painting.h"
# include "geometry.h"

# define PIXEL_SIZE 50
# define ANGLE_DELTA 10

// PLAYER_RAD and STEP are relative
# define PLAYER_RAD 0.2
# define STEP 0.31

# define EPS 0.2
# define PIXELS_PER_DEGREE 5

# define WIDTH 1000
# define HEIGHT 1000

# define ESC 53
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

typedef enum e_color		t_color;
typedef enum e_orient		t_orient;
typedef struct s_ray		t_ray;
typedef struct s_painting	t_painting;
typedef struct s_movements	t_movements;

enum e_color
{
	COLOR_WALL,
	COLOR_GRID,
	COLOR_PLAYER,
	COLOR_FIELD
};

enum e_orient
{
	ORIENT_NORTH,
	ORIENT_EAST,
	ORIENT_SOUTH,
	ORIENT_WEST
};

struct s_ray
{
	int			quarter;
	int			quarter_angle;
	t_vector	*orient_vert;
	t_vector	*orient_hor;
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
void		paint_init(t_map *map);

// painting_2.c
void		paint_draw_pixel(t_painting *painting,
				size_t x, size_t y, t_color color);
void		paint_draw_player(t_painting *painting, t_color color);
void		paint_draw_map(t_painting *painting);

// painting_movements_1.c
void		paint_move_left(t_painting *painting);
void		paint_move_right(t_painting *painting);
void		paint_move_up(t_painting *painting);
void		paint_move_down(t_painting *painting);

// painting_movements_2.c
int			paint_is_move_left(t_painting *painting);
int			paint_is_move_right(t_painting *painting);
int			paint_is_move_up(t_painting *painting);
int			paint_is_move_down(t_painting *painting);

// painting_ray_1.c
t_ray		*paint_get_ray_info(t_painting *painting);
void		paint_destroy_ray_info(t_ray *ray);

// painting_ray_2.c
int			paint_get_quarter(int angle);
int			paint_get_quarter_angle(int quarter, int abs_angle);
t_vector	*paint_get_orient_vector(t_orient orient);

// painting_ray_3.c
void		paint_print_ray(t_painting *painting);

// painting_utils.c
double		paint_get_dist(double x1, double y1, double x2, double y2);
double		paint_get_module(double num);
int			paint_get_color(t_color color);

#endif
