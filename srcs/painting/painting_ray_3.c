/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_ray_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:01:38 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/27 19:08:54 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

// Get quarter from absolute angle of player's view
int	paint_get_quarter(double angle)
{
	if (utils_are_doubles_equal(angle, 360)
		|| (utils_is_greater_or_eq(angle, 0) && angle < 90))
		return (1);
	if (utils_is_greater_or_eq(angle, 90) && angle < 180)
		return (2);
	if (utils_is_greater_or_eq(angle, 180) && angle < 270)
		return (3);
	if (utils_is_greater_or_eq(angle, 270) && angle < 360)
		return (4);
	return (0);
}

// Convert absolute angle of player's view to an angle inside current quarter
int	paint_get_quarter_angle(int quarter, double abs_angle)
{
	if (quarter == 1)
	{
		if (utils_are_doubles_equal(abs_angle, 360))
			return (0);
		return (abs_angle);
	}
	if (quarter == 2)
		return (90 - (abs_angle - 90));
	if (quarter == 3)
		return (abs_angle - 180);
	if (quarter == 4)
		return (90 - (abs_angle - 270));
	return (-1);
}

// Create [end] point of orientation vector depending on t_orient.
// May return NULL
static t_point	*paint_get_orient_vector_handler(t_orient orient)
{
	if (orient == ORIENT_NORTH)
		return (geom_init_point(0, 1));
	else if (orient == ORIENT_EAST)
		return (geom_init_point(1, 0));
	else if (orient == ORIENT_SOUTH)
		return (geom_init_point(0, -1));
	else if (orient == ORIENT_WEST)
		return (geom_init_point(-1, 0));
	return (NULL);
}

// Create N, E, S or W orientation vector.
// May return NULL
t_vector	*paint_get_orient_vector(t_orient orient)
{
	t_point		*begin;
	t_point		*end;
	t_vector	*orient_vector;

	if (orient != ORIENT_NORTH && orient != ORIENT_EAST
		&& orient != ORIENT_SOUTH && orient != ORIENT_WEST)
		return (NULL);
	begin = geom_init_point(0, 0);
	end = paint_get_orient_vector_handler(orient);
	if (!begin || !end)
	{
		geom_destroy_point(begin);
		geom_destroy_point(end);
		return (NULL);
	}
	orient_vector = geom_init_vector(begin, end);
	if (orient_vector)
		return (orient_vector);
	geom_destroy_point(begin);
	geom_destroy_point(end);
	return (NULL);
}
