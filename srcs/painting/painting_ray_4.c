/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_ray_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:09:13 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/19 21:08:07 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

static void	test_print_point(t_point *point)
{
	printf("{x = %d, y = %d, z = %d}\n", point->x, point->y, point->z);
}

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

t_vector	*paint_get_corner_vector(t_point *point, int quarter)
{
	int			corner_x;
	int			corner_y;
	t_point		*begin;
	t_point		*end;

	if (!point || quarter < 1 || quarter > 4)
		return (NULL);
	begin = geom_init_point(point->x, point->y, point->z);
	printf("begin: ");
	test_print_point(begin);
	if (quarter == 1)
	{
		if (point->x % PIXEL_SIZE != 0)
			corner_x = point->x - point->x % PIXEL_SIZE + PIXEL_SIZE;
		else
			corner_x = point->x;
			
		if (point->y % PIXEL_SIZE != 0)
			corner_y = point->y - point->y % PIXEL_SIZE;
		else
			corner_y = point->y - PIXEL_SIZE;
	}
	else if (quarter == 2)
	{
		corner_x = point->x - point->x % PIXEL_SIZE + PIXEL_SIZE;
		corner_y = point->y - point->y % PIXEL_SIZE + PIXEL_SIZE;
	}
	else if (quarter == 3)
	{
		corner_x = point->x - point->x % PIXEL_SIZE;
		corner_y = point->y - point->y % PIXEL_SIZE + PIXEL_SIZE;
	}
	else
	{
		corner_x = point->x - point->x % PIXEL_SIZE;
		corner_y = point->y - point->y % PIXEL_SIZE;
	}
	end = geom_init_point(
		corner_x, corner_y, 0);
	printf("corner: ");
	test_print_point(end);
	return (paint_get_corner_vector_handler(begin, end));

	/*
	if (quarter == 1)
		end = geom_init_point(point->x - point->x % PIXEL_SIZE + PIXEL_SIZE,
				point->y - point->y % PIXEL_SIZE, 0);
	else if (quarter == 2)
		end = geom_init_point(point->x - point->x % PIXEL_SIZE + PIXEL_SIZE,
				point->y - point->y % PIXEL_SIZE + PIXEL_SIZE, 0);
	else if (quarter == 3)
		end = geom_init_point(point->x - point->x % PIXEL_SIZE,
				point->y - point->y % PIXEL_SIZE + PIXEL_SIZE, 0);
	else
		end = geom_init_point(point->x - point->x % PIXEL_SIZE,
				point->y - point->y % PIXEL_SIZE, 0);
	*/
}

//static double min_double(double first, double second)
//{
//	if (first < second)
//		return first;
//	return second;
//}

//static double max_double(double first, double second)
//{
//	if (first > second)
//		return first;
//	return second;
//}

void	paint_draw_vector(t_painting *painting, t_vector *vector, t_color color)
{
	double	dx;
	double	dy;
	double	x;
	double	y;
	int		pixels;
	
	if (!painting || !vector)
		return ;
	dx = vector->end->x - vector->begin->x;
	dy = vector->end->y - vector->begin->y;
	pixels = sqrt(pow(dx, 2) + pow(dy, 2));
	dx /= pixels;
	dy /= pixels;
	x = vector->begin->x;
	y = vector->begin->y;
	while (pixels)
	{
		if ((int)x % PIXEL_SIZE != 0 || (int)y % PIXEL_SIZE != 0)
			mlx_pixel_put(painting->mlx, painting->win, x, y, paint_get_color(color));
		else
			mlx_pixel_put(painting->mlx, painting->win, x, y, paint_get_color(COLOR_GRID));
		x += dx;
		y += dy;
		--pixels;
	}
}
