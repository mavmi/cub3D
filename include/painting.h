/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:13:18 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/03/19 15:02:18 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAINTING_H
# define PAINTING_H

# include <math.h>

# include "../minilibx/mlx.h"
# include "../libft/libft.h"

# include "geometry.h"
# include "parser.h"

# define MOUSE_HIDE 0
# define PL_STEP 0.62
# define ANGLE_DELTA_KEY 5
# define ANGLE_DELTA_MOUSE 7
# define PIXELS_PER_DEGREE 4

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
# define SPACE 49

// 3D
# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000
# define FOV 60.0

// 2D
# define MAP_WIDTH 250
# define MAP_HEIGHT 250
# define MAP_DELTA 75
# define MAP_SQ_SIZE 10
# define MAP_PL_RAD 0.23

typedef enum e_color			t_color;
typedef enum e_orient			t_orient;
typedef enum e_movement			t_movement;

typedef struct s_ray_vars		t_ray_vars;
typedef struct s_ray			t_ray;
typedef struct s_image			t_image;
typedef struct s_drawable		t_drawable;
typedef struct s_painting		t_painting;
typedef struct s_ray_of_view	t_ray_of_view;
typedef struct s_decrease		t_decrease;
typedef struct s_move_vars		t_move_vars;
typedef struct s_room_vars		t_room_vars;

/*
	Just colors for mlx_pixel_put

	paint_get_color(..) function converts it to int
*/
enum e_color
{
	COLOR_WALL,
	COLOR_DOOR,
	COLOR_GIF,
	COLOR_GRID,
	COLOR_PLAYER,
	COLOR_FIELD,
	COLOR_TRANSPARENT
};

/*
	Variables to indicate what kind of
	orienation vector I need

	paint_get_orient_vector(..)
*/
enum e_orient
{
	ORIENT_NORTH,
	ORIENT_EAST,
	ORIENT_SOUTH,
	ORIENT_WEST,
	ORIENT_CL_DOOR,
	ORIENT_OP_DOOR,
	ORIENT_GIF
};

enum e_movement
{
	MOVE_FORWARD,
	MOVE_BACK,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_DOOR
};

/*
	Contain information about player's vector of view.

					N(0°)
	  				 |
				[4]  |  [1]
	 W(270°) --------|-------- E(90°)
				[3]  |  [2]
					 |
				   S(180°)

	(0 <= angle < 90)    ==> (quarter == 1)
	(90 <= angle < 180)  ==> (quarter == 2)
	(180 <= angle < 270) ==> (quarter == 3)
	(270 <= angle < 360) ==> (quarter == 4)

	[quarter_angle] is an angle inside current quarter
	relative to the vertical orientation vector

	Orientation vectors are N, E, S and W

	paint_get_orient_vector(..) creates required
	orientation vector
*/
struct s_ray
{
	int			quarter;
	double		quarter_angle;
	t_vector	*orient_vert;
	t_vector	*orient_hor;
};

struct s_drawable
{
	int		endian;
	int		size_line;
	int		bits_per_pixel;
	void	*img;
	char	*img_addr;
};

/*
	It's for .xpm files
*/
struct s_image
{
	int			w;
	int			h;
	t_drawable	drawable;
};

/*
	Contain all necssary information about
	map, player and mlx stuff
*/
struct s_painting
{
	int			minimap_x;
	int			minimap_y;
	int			floor;
	int			ceil;
	int			cl_door_fl;
	void		*mlx;
	void		*win;
	t_map		*map;
	t_drawable	room;
	t_drawable	minimap;
	t_image		*t_north;
	t_image		*t_east;
	t_image		*t_south;
	t_image		*t_west;
	t_image		*t_door;
	t_image		**t_gif;
};

struct s_ray_of_view
{
	t_vector	*ray;
	t_orient	orient;
};

struct s_decrease
{
	double			*x;
	double			*y;
	double			delta;
	double			tmp_x;
	double			tmp_y;
	t_ray_vars		*vars;
};

struct s_move_vars
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

/*
	I need it to contain variables
	for paint_get_ray_vector(..) function

	[delta] - Y-axis or X-axis shift
	[octet] - like coordinate axis's quarter, but octet
	[corner_angle] - angle between corner vector and
		vertical orientation vector
	[ray_of_view] is what this function creates
*/
struct s_ray_vars
{
	int				octet;
	double			delta;
	double			corner_angle;
	t_ray			*ray_info;
	t_painting		*painting;
	t_ray_of_view	*ray_of_view;
};

struct s_room_vars
{
	int				x;
	int				y;
	int				wall_start;
	int				wall_end;
	int				wall_height;
	double			text_x;
	double			text_y;
	double			ray_len;
	double			angle;
	double			angle_delta;
	t_image			*image;
	t_ray_of_view	*ray_of_view;
};

/******************************
	./
******************************/

// painting_freeNexit.c
void			paint_ray_destroy_ray_of_view(t_ray_of_view *ray_of_view);
void			paint_exit(t_painting *painting);

// painting_event_handlers.c
int				paint_draw_all(t_painting *painting);
int				paint_key_pressed(int key_code, t_painting *painting);
int				paint_mouse_move(int x, int y, t_painting *painting);

// painting_files.c
t_image			*paint_get_image(t_painting *painting, char *file_name);

// painting_main.c
void			paint(t_map *map);

// painting_utils.c
double			paint_get_dist(double x1, double y1, double x2, double y2);
double			paint_get_module(double num);
int				paint_get_color(t_color color);
void			paint_put_color(t_drawable *drawable, int x, int y,
					t_color color);
void			paint_put_pixel(t_drawable *drawable, int x, int y, int pixel);

/******************************
	./painting_movements/
******************************/

// painting_movements_1.c
void			paint_movements_move(t_painting *painting, t_movement movement);

/******************************
	./painting_minimap/
******************************/

// painting_minimap_1.c
void			paint_minimap_draw_sq(t_painting *painting,
					size_t x, size_t y, t_color color);
void			paint_minimap_draw_map(t_painting *painting);
void			paint_minimap_draw(t_painting *painting);

// painting_minimap_2.c
void			paint_minimap_draw_player(t_painting *painting);
void			paint_minimap_erase_player(t_painting *painting);

/******************************
	./painting_ray/
******************************/

// painting_ray_1.c
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
int				paint_ray_append_vector(t_ray_vars *vars);

// painting_ray_6.c
void			paint_ray_decrease_coord(t_ray_vars *vars,
					double *x, double *y);

// painting_ray_7.c
void			paint_ray_set_ray_orient(t_ray_vars *vars);
int				paint_ray_decrease_coord_assignment(t_decrease *decr);
int				paint_ray_get_octet(int quarter, int part);
int				paint_ray_get_delta_angle_octet(t_ray_vars *vars);

// painting_ray_8.c
int				paint_ray_is_wall_or_door(t_ray_vars *vars, double x, double y);

/******************************
	./painting_room/
******************************/

// painting_room_1.c
int				paint_room_draw_room(t_painting *painting);

// painting_room_2.c
double			paint_room_decrease_angle(double angle, double delta);
double			paint_room_increase_angle(double angle, double delta);

#endif
