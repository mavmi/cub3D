/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:28:07 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/08 16:39:06 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/geometry.h"

/*
	Compare two geom points.
	Return 1 if they are equal, 0 othwewise
*/
int	geom_cmp_points(t_point *first, t_point *second)
{
	if (!first || !second)
		return (0);
	if (
		utils_are_doubles_equal(first->x, second->x)
		&& utils_are_doubles_equal(first->y, second->y)
	)
	{
		return (1);
	}
	return (0);
}

/*
	Compare two vectors.
	Return 1 if they are equal, 0 othwewise
*/
int	geom_cmp_vectors(t_vector *first, t_vector *second)
{
	if (!first || !second)
		return (0);
	if (
		geom_cmp_points(first->begin, second->begin)
		&& geom_cmp_points(first->end, second->end)
	)
	{
		return (1);
	}
	return (0);
}

/*
	Copy point.
	
	May return NULL
*/
t_point	*geom_copy_point(t_point *point)
{
	if (!point)
		return (NULL);
	return (geom_init_point(point->x, point->y));
}

/*
	Copy vector.

	May return NULL
*/
t_vector	*geom_copy_vector(t_vector *vector)
{
	t_point		*begin_cpy;
	t_point		*end_cpy;
	t_vector	*vector_cpy;

	if (!vector)
		return (NULL);
	begin_cpy = geom_copy_point(vector->begin);
	end_cpy = geom_copy_point(vector->end);
	if (!begin_cpy || !end_cpy)
	{
		geom_destroy_point(begin_cpy);
		geom_destroy_point(end_cpy);
		return (NULL);
	}
	vector_cpy = geom_init_vector(begin_cpy, end_cpy);
	if (vector_cpy)
		return (vector_cpy);
	geom_destroy_point(begin_cpy);
	geom_destroy_point(end_cpy);
	return (NULL);
}
