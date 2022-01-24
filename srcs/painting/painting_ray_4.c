/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_ray_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:09:13 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/24 20:19:50 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

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

static int	paint_get_corner_x(int point_x, int quarter)
{
	if (quarter == 1)
	{
		if (point_x % PIXEL_SIZE != 0)
			return (point_x - point_x % PIXEL_SIZE + PIXEL_SIZE);
		return (point_x + PIXEL_SIZE);
	}
	else if (quarter == 2)
	{
		if (point_x % PIXEL_SIZE != 0)
			return (point_x - point_x % PIXEL_SIZE + PIXEL_SIZE);
		return (point_x + PIXEL_SIZE);
	}
	else if (quarter == 3)
	{
		if (point_x % PIXEL_SIZE != 0)
			return (point_x - point_x % PIXEL_SIZE);
		return (point_x - PIXEL_SIZE);
	}
	else
	{
		if (point_x % PIXEL_SIZE != 0)
			return (point_x - point_x % PIXEL_SIZE);
		return (point_x - PIXEL_SIZE);
	}
}

static int	paint_get_corner_y(int point_y, int quarter)
{
	if (quarter == 1)
	{
		if (point_y % PIXEL_SIZE != 0)
			return (point_y - point_y % PIXEL_SIZE);
		return (point_y - PIXEL_SIZE);
	}
	else if (quarter == 2)
	{
		if (point_y % PIXEL_SIZE != 0)
			return (point_y - point_y % PIXEL_SIZE + PIXEL_SIZE);
		return (point_y + PIXEL_SIZE);
	}
	else if (quarter == 3)
	{
		if (point_y % PIXEL_SIZE != 0)
			return (point_y - point_y % PIXEL_SIZE + PIXEL_SIZE);
		return (point_y + PIXEL_SIZE);
	}
	else
	{
		if (point_y % PIXEL_SIZE != 0)
			return (point_y - point_y % PIXEL_SIZE);
		return (point_y - PIXEL_SIZE);
	}
}

t_vector	*paint_get_corner_vector(t_point *point, int quarter)
{
	t_point		*begin;
	t_point		*end;

	if (!point || quarter < 1 || quarter > 4)
		return (NULL);
	begin = geom_init_point(point->x, point->y, point->z);
	end = geom_init_point(paint_get_corner_x(point->x, quarter),
			paint_get_corner_y(point->y, quarter), 0);
	return (paint_get_corner_vector_handler(begin, end));
}

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
	dx = (vector->end->x - vector->begin->x);
	dy = (vector->end->y - vector->begin->y);
	pixels = sqrt(pow(dx, 2) + pow(dy, 2));
	dx /= pixels;
	dy /= pixels;
	x = vector->begin->x;
	y = vector->begin->y;
	while (pixels--)
	{
		if ((int)x % PIXEL_SIZE != 0 || (int)y % PIXEL_SIZE != 0)
			mlx_pixel_put(painting->mlx, painting->win,
				x, y, paint_get_color(color));
		x += dx;
		y += dy;
	}
}

void	paint_draw_vector(t_painting *painting, t_vector *vector)
{
	if (!painting || !vector)
		return ;
	paint_vector_printer(painting, vector, COLOR_RAY);
}

void	paint_erase_vector(t_painting *painting, t_vector *vector)
{
	if (!painting || !vector)
		return ;
	paint_vector_printer(painting, vector, COLOR_FIELD);
}
