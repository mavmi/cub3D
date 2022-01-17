/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 18:58:04 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/16 19:50:21 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/geometry.h"

t_vector	*geom_sum_vectors(t_vector *first, t_vector *second)
{
	t_point		*begin_cpy;
	t_point		*end_cpy;
	t_vector	*second_cpy;

	if (!first || !second)
		return (NULL);
	second_cpy = geom_copy_vector(second);
	if (!second)
		return (NULL);
	geom_move_vector(second_cpy, first->end);
	begin_cpy = geom_copy_point(first->begin);
	end_cpy = geom_copy_point(second_cpy->end);
	geom_destroy_vector(second_cpy);
	if (!begin_cpy || !end_cpy)
	{
		geom_destroy_point(begin_cpy);
		geom_destroy_point(end_cpy);
		return (NULL);
	}
	return (geom_init_vector(begin_cpy, end_cpy));
}

double	geom_vector_get_module(t_vector *vector)
{
	if (!vector)
		return (0.0);
	return (
		sqrt(pow(vector->end->x - vector->begin->x, 2)
			+ pow(vector->end->y - vector->begin->y, 2)
			+ pow(vector->end->z - vector->begin->z, 2))
	);
}

void	geom_move_vector(t_vector *vector, t_point *point)
{
	t_point	delta;

	if (!vector || !point)
		return ;
	delta.x = point->x - vector->begin->x;
	delta.y = point->y - vector->begin->y;
	delta.z = point->z - vector->begin->z;
	vector->begin->x = point->x;
	vector->begin->y = point->y;
	vector->begin->z = point->z;
	vector->end->x += delta.x;
	vector->end->y += delta.y;
	vector->end->z += delta.z;
}