/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:17:24 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/27 19:16:56 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>

# include "utils.h"
# include "geometry.h"
# include "get_next_line.h"

# define SQ_SIZE 1

# define BAD_SQ_TYPE '-'
# define BAD_SQ_POS -1
# define BAD_PL_ORIENT '+'
# define BAD_PL_POS -1.0
# define BAD_PL_ANGLE -1.0

# define MAP_SQ_VOID ' '
# define MAP_SQ_EMPTY '0'
# define MAP_SQ_WALL '1'
# define MAP_OR_NORTH 'N'
# define MAP_OR_SOUTH 'S'
# define MAP_OR_EAST 'E'
# define MAP_OR_WEST 'W'

typedef struct s_position	t_position;
typedef struct s_player		t_player;
typedef struct s_square		t_square;
typedef struct s_map_line	t_map_line;
typedef struct s_map		t_map;

// Just to save player's position relative to
// the very beginning of map's array of strings
struct s_position
{
	double	x;
	double	y;
};

// Player's info.
// [pos] - current position
// [ray_of_view] - vector which begins in player's poition
// and end in the wall
// [orient] - orientation
// [angle] - angle between north vector and
// player's vector of view
struct s_player
{
	char		orient;
	double		angle;
	t_vector	*ray_of_view;
	t_position	*pos;
};

// Elementary element of map.
// [top_left_x] and [top_left_y] are coordinates of
// this square relative to the beginning of map's array of strings
// [type] is about walls, floor, may be smth else, idk
struct s_square
{
	size_t	top_left_x;
	size_t	top_left_y;
	char	type;
};

// Horizontal line of map.
// Contain array of squares and it's size
struct s_map_line
{
	size_t		width;
	t_square	**line;
};

// The whole map.
// Contain array of map lines, it's size
// and player's struct
struct s_map
{
	size_t		height;
	t_player	*player;
	t_map_line	**lines;
};

// parser_1.c
void		pars_destroy_map(t_map *map);
t_map		*pars_get_map(char *path);

// parser_convert_1.c
t_square	*pars_char_to_square(t_map *map, char c, int x, int y);

// parser_convert_2.c
t_map_line	*pars_str_to_map_line(t_map *map, char *str, int y);
t_map		*pars_str_arr_to_map(char **arr);

// parser_destroyers.c
void		pars_destroy_player(t_player *player);
void		pars_destroy_square(t_square *square);
void		pars_destroy_map_line(t_map_line *map_line);
void		pars_destroy_map(t_map *map);

// parser_getters.c
t_player	*pars_get_empty_player(void);
t_square	*pars_get_empty_square(void);
t_map_line	*pars_get_empty_map_line(void);
t_map		*pars_get_empty_map(void);

// parser_utils_1.c
int			pars_open_file(char *path);
int			pars_is_char_valid_square(char c);
int			pars_is_char_valid_player(char c);
int			pars_is_char_valid(char c);
int			pars_is_str_valid(char *str);

// parser_utils_2.c
t_position	*pars_copy_position(t_position *pos);

#endif
