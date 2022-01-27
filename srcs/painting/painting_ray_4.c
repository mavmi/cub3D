/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_ray_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:09:13 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/27 16:01:33 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

// Create t_vector from two t_points.
// May return NULL
static t_vector	*paint_get_corner_vector_handler(t_point *begin, t_point *end)
{
	t_vector	*vector;

	vector = geom_init_vector(begin, end);
	if (vector)
		return (vector);
	geom_destroy_point(begin);
	geom_destroy_point(end);
	return (NULL);
}

// Get x for corner vector
static int	paint_get_corner_x(double point_x, int quarter)
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

// Get y for corner vector
static int	paint_get_corner_y(double point_y, int quarter)
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

// Create vector from [point] to corner of the current square
// depending on quarter.
// May return NULL
t_vector	*paint_get_corner_vector(t_point *point, int quarter)
{
	t_point		*begin;
	t_point		*end;

	if (!point || quarter < 1 || quarter > 4)
		return (NULL);
	begin = geom_init_point(point->x, point->y);
	end = geom_init_point(paint_get_corner_x(point->x, quarter),
			paint_get_corner_y(point->y, quarter));
	return (paint_get_corner_vector_handler(begin, end));
}

// Vector's printer.
// It draws vector
static void	paint_vector_printer(t_painting *painting,
			t_vector *vector, t_color color)
{
	double	dx;
	double	dy;
	double	x;
	double	y;
	int		pixels;

	if (!painting || !vector)
		return ;
	dx = (int)((vector->end->x - vector->begin->x) * PIXEL_SIZE);
	dy = (int)((vector->end->y - vector->begin->y) * PIXEL_SIZE);
	pixels = sqrt(pow(dx, 2) + pow(dy, 2));
	dx /= pixels;
	dy /= pixels;
	x = vector->begin->x * PIXEL_SIZE;
	y = vector->begin->y * PIXEL_SIZE;
	while (pixels--)
	{
		if ((int)x % PIXEL_SIZE == 0 || (int)y % PIXEL_SIZE == 0)
			paint_put_pixel(painting, x, y, COLOR_GRID);
		else
			paint_put_pixel(painting, x, y, color);
		x += dx;
		y += dy;
	}
}

// Draw vector in canvas
void	paint_draw_vector(t_painting *painting, t_vector *vector)
{
	if (!painting || !vector)
		return ;
	paint_vector_printer(painting, vector, COLOR_RAY);
}

// Delete vector from canvas
void	paint_erase_vector(t_painting *painting, t_vector *vector)
{
	if (!painting || !vector)
		return ;
	paint_vector_printer(painting, vector, COLOR_FIELD);
}
