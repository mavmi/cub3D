/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:13:18 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/04 16:36:15 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAINTING_H
# define PAINTING_H

# include <math.h>

# include "../minilibx/mlx.h"

# include "parser.h"
# include "painting.h"
# include "geometry.h"

// Just utils
# define EPS 0.2
# define FOV 60.0
# define CAMERA_DIST 1.0
# define PIXEL_SIZE 30
# define ANGLE_DELTA_KEY 5
# define ANGLE_DELTA_MOUSE 4
# define PIXELS_PER_DEGREE 3

// PLAYER_RAD and STEP are relative
# define PL_RAD 0.17
# define PL_STEP 0.69

# define WIDTH 1000
# define HEIGHT 1000
# define RECT_HEIGHT 300

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

typedef enum e_color			t_color;
typedef enum e_orient			t_orient;
typedef enum e_movement			t_movement;

typedef struct s_ray_getter		t_ray_getter;
typedef struct s_ray			t_ray;
typedef struct s_painting		t_painting;
typedef struct s_ray_of_view	t_ray_of_view;	
typedef struct s_decrease		t_decrease;
typedef struct s_movements		t_movements;
typedef struct s_room_data		t_room_data;

// Just colors for mlx_pixel_put
//
// paint_get_color(..) function converts it to int
enum e_color
{
	COLOR_WALL,
	COLOR_GRID,
	COLOR_PLAYER,
	COLOR_FIELD,
	COLOR_RAY,
	COLOR_BLACK,
	COLOR_YELLOW,
	COLOR_GREEN,
	COLOR_NORTH,
	COLOR_EAST,
	COLOR_SOUTH,
	COLOR_WEST
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

enum e_movement
{
	MOVE_FORWARD,
	MOVE_BACK,
	MOVE_LEFT,
	MOVE_RIGHT
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
	double		quarter_angle;
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

struct s_ray_of_view
{
	t_vector	*ray;
	t_orient	orient;
};

// Just vars for paint_decrease_coord(..) function
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
	double			x;
	double			y;
	double			len;
	double			cos_;
	double			sin_;
	double			angle;
	t_vector		*vector;
	t_ray_of_view	*ray_of_view;
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
	int				octet;
	double			delta;
	double			corner_angle;
	t_ray			*ray_info;
	t_ray_of_view	*ray_of_view;
	t_painting		*painting;
};

struct s_room_data
{
	int				x;
	int				y;
	int				wall_start;
	int				wall_end;
	int				wall_height;
	double			ray_len;
	double			angle;
	double			angle_delta;
	t_ray_of_view	*ray_of_view;
};

/******************************
	./
******************************/

// painting_3d.c
void			paint_3d(t_map *map);

// painting_utils.c
double			paint_get_dist(double x1, double y1, double x2, double y2);
double			paint_get_module(double num);
int				paint_get_color(t_color color);
void			paint_put_pixel(t_painting *painting, int x, int y,
					t_color color);

/******************************
	./painting_movements/
******************************/

// painting_movements_1.c
void			paint_movements_move(t_painting *painting, t_movement movement);

/******************************
	./painting_minimap/
******************************/

// painting_minimap_1.c
void			paint_minimap_draw_pixel(t_painting *painting,
					size_t x, size_t y, t_color color);
void			paint_minimap_draw_map(t_painting *painting);

// painting_minimap_2.c
void			paint_minimap_draw_player(t_painting *painting);
void			paint_minimap_erase_player(t_painting *painting);

// painting_minimap_3.c
void			paint_minimap_draw_vector(t_painting *painting,
					t_vector *vector);
void			paint_minimap_erase_vector(t_painting *painting,
					t_vector *vector);

/******************************
	./painting_ray/
******************************/

// painting_ray_1.c
void			paint_ray_destroy_ray_of_view(t_ray_of_view *ray_of_view);
t_ray_of_view	*paint_ray_get_ray_of_view(t_painting *painting, double angle);

// painting_ray_2.c
t_ray			*paint_ray_get_ray_info(double angle);
void			paint_ray_destroy_ray_info(t_ray *ray);

// painting_ray_3.c
int				paint_ray_get_quarter(double angle);
double			paint_ray_get_quarter_angle(int quarter, double abs_angle);
t_vector		*paint_ray_get_orient_vector(t_orient orient);

// painting_ray_4.c
t_vector		*paint_ray_get_corner_vector(t_point *point, int quarter);
void			paint_minimap_draw_vector(t_painting *painting,
					t_vector *vector);
void			paint_minimap_erase_vector(t_painting *painting,
					t_vector *vector);

// painting_ray_5.c
int				paint_ray_append_vector(t_ray_getter *vars);

// painting_ray_6.c
void			paint_ray_decrease_coord(t_ray_getter *vars,
					double *x, double *y);

// painting_ray_7.c
void			paint_ray_set_ray_orient(t_ray_getter *vars);
int				paint_ray_decrease_coord_assignment(t_decrease *decr);
int				paint_ray_get_octet(int quarter, int part);
int				paint_ray_is_wall(t_ray_getter *vars, double x, double y);
int				paint_ray_get_delta_angle_octet(t_ray_getter *vars);

/******************************
	./painting_room/
******************************/

// painting_room_1.c
int				paint_room_draw_room(t_painting *painting);

// painting_room_2.c
double			paint_room_decrease_angle(double angle, double delta);
double			paint_room_increase_angle(double angle, double delta);
t_color			paint_room_orient_to_color(t_orient orient);

#endif
