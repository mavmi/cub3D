/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:17:49 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/02 16:37:20 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# include "utils.h"

typedef struct s_point		t_point;
typedef struct s_vector		t_vector;

struct s_point
{
	double	x;
	double	y;
};

struct s_vector
{
	t_point	*begin;
	t_point	*end;
};

// geometry_1.c
void		geom_destroy_point(t_point *point);
void		geom_destroy_vector(t_vector *vector);
t_point		*geom_init_point(double x, double y);
t_vector	*geom_init_vector(t_point *begin, t_point *end);

// geometry_2.c
int			geom_cmp_points(t_point *first, t_point *second);
int			geom_cmp_vectors(t_vector *first, t_vector *second);
t_point		*geom_copy_point(t_point *point);
t_vector	*geom_copy_vector(t_vector *vector);

// geometry_3.c
t_vector	*geom_sum_vectors(t_vector *first, t_vector *second);
double		geom_vector_get_module(t_vector *vector);
void		geom_move_vector(t_vector *vector, t_point *point);
double		geom_get_angle(t_vector *vector_1, t_vector *vector_2);

#endif
