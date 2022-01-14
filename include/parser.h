/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:17:24 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/14 15:06:31 by pmaryjo          ###   ########.fr       */
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

# define VOID ' '
# define EMPTY '0'
# define WALL '1'
# define NORTH_OR 'N'
# define SOUTH_OR 'S'
# define EAST_OR 'E'
# define WEST_OR 'W'

typedef struct s_player		t_player;
typedef struct s_square		t_square;
typedef struct s_map_line	t_map_line;
typedef struct s_map		t_map;

struct s_player
{
	t_point	*pos;
	char	orient;
	double	angle;
};

struct s_square
{
	size_t	top_left_x;
	size_t	top_left_y;
	char	type;
};

struct s_map_line
{
	size_t		width;
	t_square	**line;
};

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

// parser_utils.c
int			pars_open_file(char *path);
int			pars_is_char_valid_square(char c);
int			pars_is_char_valid_player(char c);
int			pars_is_char_valid(char c);
int			pars_is_str_valid(char *str);

#endif
