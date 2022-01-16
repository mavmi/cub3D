/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 15:49:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/16 19:49:59 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/geometry.h"

void	geom_destroy_point(t_point *point)
{
	if (!point)
		return ;
	free(point);
}

void	geom_destroy_vector(t_vector *vector)
{
	if (!vector)
		return ;
	free(vector->begin);
	free(vector->end);
	free(vector);
}

t_point	*geom_init_point(int x, int y, int z)
{
	t_point	*point;

	point = (t_point *)malloc(sizeof(t_point));
	if (!point)
		return (point);
	point->x = x;
	point->y = y;
	point->z = z;
	return (point);
}

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
