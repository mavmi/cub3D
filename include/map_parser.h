/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:17:24 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/26 20:26:20 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSER_H
# define MAP_PARSER_H

# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>

# include "utils.h"
# include "geometry.h"
# include "get_next_line.h"

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

typedef struct s_player		t_player;
typedef struct s_square		t_square;
typedef struct s_map_line	t_map_line;
typedef struct s_map		t_map;
typedef struct s_param_len	t_param_len;

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
};

struct s_param_len
{
	size_t	arr;
	size_t	str;
	size_t	up;
	size_t	down;
};


// parsing_start.c
t_map		*pars_start(char *path);

//parsing_utils.c

int	error_texture_message(void);
int	error_ud_message(void);
void	*free_return(size_t *freed, char sms_fl);
int	check_other_three_elems(char *str);
size_t	arr_size_before_empty_str(char **arr);


///////////////////////////////////////////////

// map_parser_valid.c

int	map_pars_valid(char **arr);

// map_parser_convert_1.c
t_square	*pars_char_to_square(t_map *map, char c, int x, int y);

// map_parser_convert_2.c
t_map_line	*pars_str_to_map_line(t_map *map, char *str, int y);
t_map		*pars_str_arr_to_map(char **arr);

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
