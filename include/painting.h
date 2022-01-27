/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:13:18 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/27 18:57:30 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAINTING_H
# define PAINTING_H

# include <math.h>

# include "../minilibx/mlx.h"

# include "parser.h"
# include "painting.h"
# include "geometry.h"

# define PIXEL_SIZE 30
# define ANGLE_DELTA 1

// PLAYER_RAD and STEP are relative
# define PLAYER_RAD 0.2
# define STEP 0.19

# define EPS 0.2
# define PIXELS_PER_DEGREE 1

# define WIDTH 1200
# define HEIGHT 600

# define ESC 53
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
// It's pro gamer stuff
# define W 13
# define A 0
# define S 1
# define D 2

typedef enum e_color		t_color;
typedef enum e_orient		t_orient;
typedef struct s_ray_getter	t_ray_getter;
typedef struct s_ray		t_ray;
typedef struct s_painting	t_painting;
typedef struct s_decrease	t_decrease;
typedef struct s_movements	t_movements;

// Just colors for mlx_pixel_put
//
// paint_get_color(..) function converts it to int
enum e_color
{
	COLOR_WALL,
	COLOR_GRID,
	COLOR_PLAYER,
	COLOR_FIELD,
	COLOR_RAY
};

// Variables to indicate what kind of
// orienation vector I need
//
// paint_get_orient_vector(..)
enum e_orient
{
	ORIENT_NORTH,
	ORIENT_EAST,
	ORIENT_SOUTH,
	ORIENT_WEST
};

// Contain information about player's vector of view.
//
//                 N(0°)
//                  |
//             [4]  |  [1]
//  W(270°) --------|-------- E(90°)
//             [3]  |  [2]
//                  |
//                S(180°)
//
// (0 <= angle < 90)    ==> (quarter == 1)
// (90 <= angle < 180)  ==> (quarter == 2)
// (180 <= angle < 270) ==> (quarter == 3)
// (270 <= angle < 360) ==> (quarter == 4)
// 
// [quarter_angle] is an angle inside current quarter
// relative to the vertical orientation vector
//
// Orientation vectors are N, E, S and W
//
// paint_get_orient_vector(..) creates required 
// orientation vector
struct s_ray
{
	int			quarter;
	int			quarter_angle;
	t_vector	*orient_vert;
	t_vector	*orient_hor;
};

// Contain all necssary information about
// map, player and mlx stuff
struct s_painting
{
	t_map	*map;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	void	*mlx;
	void	*win;
	void	*img;
	char	*data_addr;
};

struct s_decrease
{
	double			*x;
	double			*y;
	double			delta;
	double			tmp_x;
	double			tmp_y;
	t_ray_getter	*vars;
};

// These values are NOT about pixels or smth.
// They are about position inside map's array of strings
//
// All of them are coordinates of player square's corners
//
// paint_is_move_[somewhere](..) ==> paint_get_vars(..)
struct s_movements
{	
	double	tl_x;
	double	tl_y;
	double	bl_x;
	double	bl_y;
	double	tr_x;
	double	tr_y;
	double	br_x;
	double	br_y;
};

// I need it to contain variables
// for paint_get_ray_vector(..) function
//
// [delta] - Y-axis or X-axis shift
// [octet] - like coordinate axis's quarter, but octet
// [corner_angle] - angle between corner vector and
// vertical orientation vector
// [ray_vector] is what this function creates
struct s_ray_getter
{
	int			octet;
	double		delta;
	double		corner_angle;
	t_ray		*ray_info;
	t_vector	*ray_vector;
	t_painting	*painting;
};

// painting_1.c
void		paint_init(t_map *map);

// painting_2.c
void		paint_draw_pixel(t_painting *painting,
				size_t x, size_t y, t_color color);
void		paint_draw_player(t_painting *painting);
void		paint_erase_player(t_painting *painting);
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
t_vector	*paint_get_ray_of_view(t_painting *painting);

// painting_ray_2.c
t_ray		*paint_get_ray_info(int angle);
void		paint_destroy_ray_info(t_ray *ray);

// painting_ray_3.c
int			paint_get_quarter(int angle);
int			paint_get_quarter_angle(int quarter, int abs_angle);
t_vector	*paint_get_orient_vector(t_orient orient);

// painting_ray_4.c
t_vector	*paint_get_corner_vector(t_point *point, int quarter);
void		paint_draw_vector(t_painting *painting, t_vector *vector);
void		paint_erase_vector(t_painting *painting, t_vector *vector);

// painting_utils.c
double		paint_get_dist(double x1, double y1, double x2, double y2);
double		paint_get_module(double num);
int			paint_get_color(t_color color);
void		paint_put_pixel(t_painting *painting, int x, int y, t_color color);

#endif
