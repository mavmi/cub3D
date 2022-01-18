/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_ray_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:01:38 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/18 21:31:58 by pmaryjo          ###   ########.fr       */
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

static t_vector	*paint_get_corner_vector(t_position *pl_pos, int quarter)
{
	t_point		*begin;
	t_point		*end;

	if (!pl_pos || quarter < 1 || quarter > 4)
		return (NULL);
	begin = geom_init_point(pl_pos->x * PIXEL_SIZE,
			pl_pos->y * PIXEL_SIZE, 0);
	if (quarter == 1)
		end = geom_init_point(((int)pl_pos->x + 1) * PIXEL_SIZE,
				(int)pl_pos->y * PIXEL_SIZE, 0);
	else if (quarter == 2)
		end = geom_init_point(((int)pl_pos->x + 1) * PIXEL_SIZE,
				((int)pl_pos->y + 1) * PIXEL_SIZE, 0);
	else if (quarter == 3)
		end = geom_init_point((int)pl_pos->x * PIXEL_SIZE,
				((int)pl_pos->y + 1) * PIXEL_SIZE, 0);
	else
		end = geom_init_point((int)pl_pos->x * PIXEL_SIZE,
				(int)pl_pos->y * PIXEL_SIZE, 0);
	return (paint_get_corner_vector_handler(begin, end));
}

static void	paint_print_ray_handler(t_painting *painting, t_ray *ray)
{
	t_vector	*corner_vector;

	if (!painting || !ray)
		return ;
	corner_vector = paint_get_corner_vector(painting->map->player->pos,
			ray->quarter);
	if (!corner_vector)
		return ;
	// check angles and smth
}

void	paint_print_ray(t_painting *painting)
{
	t_ray	*ray;

	if (!painting)
		return ;
	ray = paint_get_ray_info(painting);
	if (!ray)
		return ;
	paint_print_ray_handler(painting, ray);
	paint_destroy_ray_info(ray);
}
