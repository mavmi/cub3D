/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_ray_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:09:13 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/08 17:02:28 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

/*
	Create t_vector from two t_points.

	May return NULL
*/
static t_vector	*paint_ray_get_corner_vector_handler(t_point *begin,
					t_point *end)
{
	t_vector	*vector;

	vector = geom_init_vector(begin, end);
	if (vector)
		return (vector);
	geom_destroy_point(begin);
	geom_destroy_point(end);
	return (NULL);
}

/*
	Get x for corner vector
*/
static int	paint_ray_get_corner_x(double point_x, int quarter)
{
	if (quarter == 1)
	{
		return (utils_round_double_up(point_x));
	}
	else if (quarter == 2)
	{
		return (utils_round_double_up(point_x));
	}
	else if (quarter == 3)
	{
		if (!utils_is_double_integer(point_x))
			return (utils_round_double_down(point_x));
		return (utils_round_double_down(point_x - 0.1));
	}
	else
	{
		if (!utils_is_double_integer(point_x))
			return (utils_round_double_down(point_x));
		return (utils_round_double_down(point_x - 0.1));
	}
}

/*
	Get y for corner vector
*/
static int	paint_ray_get_corner_y(double point_y, int quarter)
{
	if (quarter == 1)
	{
		if (!utils_is_double_integer(point_y))
			return (utils_round_double_down(point_y));
		return (utils_round_double_down(point_y - 0.1));
	}
	else if (quarter == 2)
	{
		return (utils_round_double_up(point_y));
	}
	else if (quarter == 3)
	{
		return (utils_round_double_up(point_y));
	}
	else
	{
		if (!utils_is_double_integer(point_y))
			return (utils_round_double_down(point_y));
		return (utils_round_double_down(point_y - 0.1));
	}
}

/*
	Create vector from [point] to the corner of the current square
	depending on quarter.

	May return NULL
*/
t_vector	*paint_ray_get_corner_vector(t_point *point, int quarter)
{
	t_point		*begin;
	t_point		*end;

	if (!point || quarter < 1 || quarter > 4)
		return (NULL);
	begin = geom_init_point(point->x, point->y);
	end = geom_init_point(paint_ray_get_corner_x(point->x, quarter),
			paint_ray_get_corner_y(point->y, quarter));
	return (paint_ray_get_corner_vector_handler(begin, end));
}
