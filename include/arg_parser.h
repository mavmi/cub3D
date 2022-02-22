/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:15:08 by msalena           #+#    #+#             */
/*   Updated: 2022/02/13 18:53:02 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_PARSER_H
# define ARG_PARSER_H

# include "painting.h"
# include "map_parser.h"

# define SKIP_SPACE ' '

# define NORTH_SIDE_ARG 'N'
# define SOUTH_SIDE_ARG 'S'
# define WEST_SIDE_ARG 'W'
# define EAST_SIDE_ARG 'E'

# define FLOOR_TYPE 'F'
# define CEILING_TYPE 'C'

typedef struct s_txtr_arg	t_txtr_arg;
typedef struct s_textures	t_textures;
typedef struct s_ud_type	t_ud_type;
typedef struct s_up_down	t_up_down;


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

// arg_parser_1.c


// arg_parser_textures.c

int	pars_valid_txtr(char *str, t_textures *arr);

// arg_parser_floor&ceiling.c

int	pars_valid_up_down(char *str, t_up_down *arr);

// arg_parser_getters.c

t_txtr_arg	*pars_get_new_txtr_arg(char side, char *path);
t_textures	*pars_get_empty_textures(void);
t_ud_type	*pars_get_new_ud_type(char type, size_t red,
										size_t green, size_t blue);
t_up_down	*pars_get_empty_up_down(void);

//arg_parser_destroyers.c

void	pars_destroy_txtr_arg(t_txtr_arg *destroyed);
void	pars_destroy_textures(t_textures *destroyed);
void	pars_destroy_ud_type(t_ud_type *destroyed);
void	pars_destroy_up_down(t_up_down *destroyed);




#endif
