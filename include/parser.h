/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:20:56 by msalena           #+#    #+#             */
/*   Updated: 2022/03/08 14:11:14 by msalena          ###   ########.fr       */
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
# include "../libft/libft.h"

# define BAD_SQ_TYPE '-'
# define BAD_SQ_POS -1
# define BAD_PL_ORIENT '+'
# define BAD_PL_POS -1.0
# define BAD_PL_ANGLE -1.0

# define MAP_SQ_VOID ' '
# define MAP_SQ_EMPTY '0'
# define MAP_SQ_WALL '1'
# define MAP_SQ_OP_DOOR 'D'
# define MAP_SQ_CL_DOOR 'd'
# define MAP_OR_NORTH 'N'
# define MAP_OR_SOUTH 'S'
# define MAP_OR_EAST 'E'
# define MAP_OR_WEST 'W'
# define MAP_SQ_GIF 'G'

# define SKIP_SPACE ' '
# define NO_SIDE 'N'
# define SO_SIDE 'S'
# define WE_SIDE 'W'
# define EA_SIDE 'E'

# define FLOOR 'F'
# define CEILING 'C'

typedef enum e_all			t_all;

typedef struct s_player		t_player;
typedef struct s_square		t_square;
typedef struct s_map_line	t_map_line;
typedef struct s_map		t_map;
typedef struct s_param_len	t_param_len;

typedef struct s_txtr_arg	t_txtr_arg;
typedef struct s_textures	t_textures;
typedef struct s_ud_type	t_ud_type;
typedef struct s_up_down	t_up_down;
typedef struct s_argums		t_argums;

enum e_all
{
	ALL,
	TXTR,
	FC,
	MAP
};

/*
	Player's info.

	[pos] - current position
	[orient] - orientation
	[angle] - angle between north vector and
		player's vector of view
*/
struct s_player
{
	char		orient;
	double		angle;
	t_point		*pos;
};

/*
	Elementary element of map.

	[top_left_x] and [top_left_y] are coordinates of
		this square relative to the beginning of map's array of strings
	[type] is about walls, floor, may be smth else, idk
*/
struct s_square
{
	size_t	top_left_x;
	size_t	top_left_y;
	char	type;
};

/*
	Horizontal line of map.
	Contain array of squares and it's size
*/
struct s_map_line
{
	size_t		width;
	t_square	**line;
};

/*
	The whole map.
	Contain array of map lines, it's size
	and player's struct
*/
struct s_map
{
	size_t		height;
	t_player	*player;
	t_map_line	**lines;
	t_argums	*argms;
};

struct s_param_len
{
	size_t	arr;
	size_t	str;
	size_t	up;
	size_t	down;
};

//////////////////////////////////////

struct s_txtr_arg
{
	char	side;
	char	*path;
};

struct s_textures
{
	t_txtr_arg	**arg;
	size_t		arg_count;
};

struct s_ud_type
{
	char	type;
	size_t	red;
	size_t	green;
	size_t	blue;

};

struct s_up_down
{
	t_ud_type	**type;
	size_t		type_count;
};

struct	s_argums
{
	size_t		map_start;
	t_up_down	*ud_arr;
	t_textures	*txtr_arr;
};

/******************************
	./
******************************/

// parsing_start.c
t_map		*pars_start(char *path);

// parsing_valid_check.c
t_argums	*pars_arg_definition(char **arr);

//parsing_utils.c
int			check_other_three_elems(char *str);
size_t		arr_size_before_empty_str(char **arr);
void		*free_return(void *freed, char sms_fl, t_all code);
int			take_memory_for_txtrs(t_textures *txtrs_arr_in);

//parsing_errors.c
int			errors(t_all code);
int			error_destroy(t_argums *args, char error_message);

/******************************
	./argums_parser
******************************/

// arg_parser_textures.c
int			pars_valid_txtr(char *str, t_textures *arr);
int			add_new_side_elem(t_textures *arr, char *path, char side);

// arg_parser_floor&ceiling.c
int			pars_valid_up_down(char *str, t_up_down *arr);

// arg_parser_getters.c
t_txtr_arg	*pars_get_new_txtr_arg(char side, char *path);
t_textures	*pars_get_empty_textures(void);
t_ud_type	*pars_get_new_ud_type(char type, size_t red,
				size_t green, size_t blue);
t_up_down	*pars_get_empty_up_down(void);

//arg_parser_destroyers.c
void		pars_destroy_txtr_arg(t_txtr_arg *destroyed);
void		pars_destroy_textures(t_textures *destroyed);
void		pars_destroy_ud_type(t_ud_type *destroyed);
void		pars_destroy_up_down(t_up_down *destroyed);
void		pars_destroy_argums(t_argums *args);

/******************************
	./map_parser
******************************/

// map_parser_valid_1.c
int			map_pars_valid(char **arr);

// map_parser_valid_2.c
int			map_check_valid_spaces(char **arr, size_t i_arr,
				size_t i_str, t_param_len *lens);
int			map_check_valid_doors(char **arr, size_t i_arr,
				size_t i_str, t_param_len *lens);

// map_parser_convert_1.c
t_square	*pars_char_to_square(t_map *map, char c, int x, int y);

// map_parser_convert_2.c
t_map_line	*pars_str_to_map_line(t_map *map, char *str, int y);
t_map		*pars_str_arr_to_map(char **arr, t_argums *argms);

// map_parser_destroyers.c
void		pars_destroy_player(t_player *player);
void		pars_destroy_square(t_square *square);
void		pars_destroy_map_line(t_map_line *map_line);
void		pars_destroy_map(t_map *map);

// map_parser_getters.c
t_player	*pars_get_empty_player(void);
t_square	*pars_get_empty_square(void);
t_map_line	*pars_get_empty_map_line(void);
t_map		*pars_get_empty_map(void);

// map_parser_utils_1.c
int			pars_open_file(char *path);
int			pars_is_char_valid_square(char c);
int			pars_is_char_valid_player(char c);
int			pars_is_char_valid(char c);
int			pars_is_str_valid(char *str);

#endif
