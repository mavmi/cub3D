/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 15:49:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/08 16:44:23 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/geometry.h"

/*
	Free point
*/
void	geom_destroy_point(t_point *point)
{
	if (!point)
		return ;
	free(point);
}

/*
	Free vector
*/
void	geom_destroy_vector(t_vector *vector)
{
	if (!vector)
		return ;
	geom_destroy_point(vector->begin);
	geom_destroy_point(vector->end);
	free(vector);
}

/*
	Create point with specified values.
	May return NULL
*/
t_point	*geom_init_point(double x, double y)
{
	t_point	*point;

	point = (t_point *)malloc(sizeof(t_point));
	if (!point)
		return (point);
	point->x = x;
	point->y = y;
	return (point);
}

/*
	Create vector with specified points.
	It doesn't copy [begin] and [end],
	just keep these pointers.
	May return NULL
*/
t_vector	*geom_init_vector(t_point *begin, t_point *end)
{
	t_vector	*vector;

	if (!begin || !end)
		return (NULL);
	vector = (t_vector *)malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->begin = begin;
	vector->end = end;
	return (vector);
}
